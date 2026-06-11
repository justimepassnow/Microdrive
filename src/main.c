#include "mm32_device.h"
#include <stdint.h>
#include <stdio.h>

#define BUF_SIZE 32
#define ANGLE_MIN 0
#define ANGLE_MAX 180
#define PID_INTERVAL_MS 1
#define INTEGRAL_LIMIT_Q8 25600000 // ~100 degree-seconds max windup limit in Q8
#define DEADBAND_Q8 256    // 1 degree deadband in Q8

// Default to 48MHz, since SystemInit configures it to 48MHz.
uint32_t SystemCoreClock = 48000000U;

// Logging Configuration (Set to 0 for silent multi-servo production daisy-chaining)
#define DEBUG_LOG 1

// Protocol packet parsing states
typedef enum {
    RX_STATE_HEADER1 = 0,
    RX_STATE_HEADER2,
    RX_STATE_ID,
    RX_STATE_LENGTH,
    RX_STATE_INSTRUCTION,
    RX_STATE_PARAMETERS,
    RX_STATE_CHECKSUM
} RxState;

// Configuration structure matching implementation specification (26 bytes)
typedef struct __attribute__((packed)) {
    uint8_t  servo_id;        // 0-253, default: 0
    uint8_t  direction_invert;// 0 = normal, 1 = inverted motor direction
    uint16_t min_angle;       // minimum angle, e.g., 45
    uint16_t max_angle;       // maximum angle, e.g., 280
    uint16_t max_velocity;    // degrees per second, default e.g. 180
    uint16_t current_limit;   // raw current ADC threshold (or mA threshold), default e.g. 1000
    int32_t  kp_q16;          // PID proportional gain
    int32_t  ki_q16;          // PID integral gain
    int32_t  kd_q16;          // PID derivative gain
    int16_t  zero_adc;        // raw ADC value at exactly 0 degrees
    int16_t  adc_per_360;     // number of ADC ticks for 360 degree rotation (signed)
    uint32_t magic;           // 0xDEADBEEF Magic Word
} ServoConfig;

// Global variables
ServoConfig config;

// PID active fixed-point gains (pre-calculated for 1ms time-step)
volatile int32_t Kp_q16;
volatile int32_t Ki_q16;
volatile int32_t Ki_scaled_q16;
volatile int32_t Kd_q16;
volatile int32_t adc_to_angle_mult_q16;

// PID state variables (pure integer, Q8 fixed-point format)
int32_t pid_error = 0;
int32_t pid_integral = 0;
int32_t prev_error = 0;

volatile uint8_t pending_reply_cmd = 0;
volatile uint32_t reply_trigger_time_ms = 0;
int32_t pid_derivative = 0;

// Motion target, trajectory profiling (Ghost Target) and feedback
volatile int32_t target_angle = 150;      // default target (degrees)
volatile int32_t ghost_angle_q8 = 150*256; // Ghost Target in Q8
volatile int32_t current_angle = 0;       // Current physical angle
volatile int32_t current_angle_q8 = 0;    // Current physical angle in Q8
volatile uint16_t active_velocity = 180;  // Active velocity in deg/s
volatile uint16_t active_current_limit = 1000; // Active admittance force limit (mA)
volatile uint8_t yield_active = 0;        // Flag for admittance yielding
volatile int32_t pwm_clamp = 2399;        // Dynamic PWM clamp for holding force
volatile uint8_t status_reporting_enabled = 0;

#define HARD_OCP_LIMIT_MA 2000            // Absolute safety hard-fault limit

// Safety and Fault Management flags
volatile uint8_t overcurrent_fault = 0;
volatile uint32_t overcurrent_ms = 0;
volatile uint8_t motor_armed = 0; // Arm on first valid CONTROL packet
volatile int32_t zero_current_offset_adc = 0; // Startup auto-zero calibration offset



void print_status(void);
void send_config_reply(void);

// Flash Erase/Write Helper Functions
void flash_erase_page(uint32_t address) {
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK)) {
        WRITE_REG(FLASH->KEYR, 0x45670123);
        WRITE_REG(FLASH->KEYR, 0xCDEF89AB);
    }
    WRITE_REG(FLASH->SR, FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR);
    SET_BIT(FLASH->CR, FLASH_CR_PER);
    WRITE_REG(FLASH->AR, address);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY));
    CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
    WRITE_REG(FLASH->SR, FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR);
}

void flash_write_halfword(uint32_t address, uint16_t data) {
    SET_BIT(FLASH->CR, FLASH_CR_PG);
    *(volatile uint16_t *)address = data;
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY));
    CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
    WRITE_REG(FLASH->SR, FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR);
}

void flash_write_config(ServoConfig *cfg) {
    // 1. Temporarily force motor compare registers to 0 for safety
    TIM_SetCompare3(TIM1, 0);
    TIM_SetCompare2(TIM1, 0);

    // 2. Erase flash page 15 (last 1KB of 16KB FLASH, starting at 0x08003C00)
    flash_erase_page(0x08003C00);

    // 3. Write config struct (rounded up to write final odd byte safely if struct size changes, pure compile-time integer math)
    uint16_t *src = (uint16_t *)cfg;
    for (size_t i = 0; i < (sizeof(ServoConfig) + 1) / 2; i++) {
        flash_write_halfword(0x08003C00 + i * 2, src[i]);
    }

    // 4. Re-lock Flash Memory
    SET_BIT(FLASH->CR, FLASH_CR_LOCK);
}

void flash_load_config(ServoConfig *cfg) {
    ServoConfig *flash_cfg = (ServoConfig *)0x08003C00;
    if (flash_cfg->magic == 0xDEADBEEF) {
        *cfg = *flash_cfg;
    } else {
        // Load default parameters
        cfg->servo_id = 0; // Default ID is 0 as explicitly requested!
        cfg->direction_invert = 0; // Default direction: normal (0)
        cfg->min_angle = ANGLE_MIN;
        cfg->max_angle = ANGLE_MAX;
        cfg->max_velocity = 180; // default 180 degrees/sec
        cfg->current_limit = 1000; // raw threshold/mA limit
        cfg->kp_q16 = 6553600;     // Kp = 100.0 * 65536
        cfg->ki_q16 = 3276;        // Ki = 0.05 * 65536 (unscaled)
        cfg->kd_q16 = 524288;      // Kd = 8.0 * 65536 (unscaled)
        cfg->zero_adc = 0;         // Default 0
        cfg->adc_per_360 = 6600;   // Default 6600
        cfg->magic = 0xDEADBEEF;

        // Persist default config to flash
        flash_write_config(cfg);
    }
    
    if (cfg->adc_per_360 == 0) cfg->adc_per_360 = 1;
    adc_to_angle_mult_q16 = (360 << 16) / cfg->adc_per_360;

    // Keep unscaled Q16 gains for high-precision dynamic scaling in PID loop
    Kp_q16 = cfg->kp_q16;
    Ki_q16 = cfg->ki_q16;
    Ki_scaled_q16 = (cfg->ki_q16 * 16777) >> 24;
    Kd_q16 = cfg->kd_q16;
}

// System Init
void SystemInit(void) {
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));
    
    FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
    FLASH->ACR |= FLASH_ACR_LATENCY_1;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    
    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
    RCC->CFGR |= (0x00U << RCC_CFGR_HPRE_Pos);
    
    RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
    RCC->CFGR |= (0x00U << RCC_CFGR_PPRE1_Pos);
    
    RCC->CFGR &= ~RCC_CFGR_SW_Msk;
    RCC->CFGR |= (0x02U << RCC_CFGR_SW_Pos);
    
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != (0x02U << RCC_CFGR_SWS_Pos)) {
        __ASM("nop");
    }
    
    SystemCoreClock = 48000000U;
}

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 6000; i++) {
        __ASM("nop");
    }
}

// UART Half-Duplex Single-Wire Helper Functions
void uart_enable_tx(void) {
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    USART_RxCmd(USART1, DISABLE);
    USART_TxCmd(USART1, ENABLE);
}

void uart_enable_rx(void) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    USART_TxCmd(USART1, DISABLE);
    USART_RxCmd(USART1, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void uart_init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART1, ENABLE);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_High;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_OD; // Open-Drain for single-wire Shared Bus
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_1);

    USART_StructInit(&USART_InitStruct);
    USART_InitStruct.USART_BaudRate   = 250000;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits   = USART_StopBits_1;
    USART_InitStruct.USART_Parity     = USART_Parity_No;
    USART_InitStruct.USART_Mode       = USART_Mode_Rx; // Start listening initially
    USART_Init(USART1, &USART_InitStruct);

    // Enable USART1 RX Interrupt
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    // Configure NVIC for USART1
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    USART_HalfDuplexCmd(USART1, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

void uart_putchar_raw(char c) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, (uint16_t)c);
}

void uart_print(const char *str) {
    uart_enable_tx();
    while (*str) {
        if (*str == '\n') {
            uart_putchar_raw('\r');
        }
        uart_putchar_raw(*str++);
    }
    uart_enable_rx();
}

void uart_print_int(uint32_t val) {
    char buf[12];
    int i = 10;
    buf[11] = '\0';
    if (val == 0) {
        uart_print("0");
        return;
    }
    while (val > 0 && i >= 0) {
        buf[i--] = (val % 10) + '0';
        val /= 10;
    }
    uart_print(&buf[i + 1]);
}

// 1ms SysTick interrupts
volatile uint32_t ms_ticks = 0;
uint32_t active_timer_period = 2399;
static inline void one_ms_task(uint32_t arr_period);

void SysTick_Handler(void) {
    ms_ticks++;
    // Guarantee that the PID loop runs exactly every 1ms, 
    // even if the main loop is blocked sending UART replies!
    one_ms_task(active_timer_period);
}

uint32_t millis(void) {
    return ms_ticks;
}

// ADC Helper Functions
void adc_init(void) {
    ADC_InitTypeDef  ADC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // 1. Enable ADC1 peripheral clock
    RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_ADC1, ENABLE);

    // 2. Initialize ADC1
    ADC_StructInit(&ADC_InitStruct);
    ADC_InitStruct.ADC_Resolution       = ADC_Resolution_12b;
    ADC_InitStruct.ADC_Prescaler        = ADC_Prescaler_3; // 16MHz ADC clock @ 48MHz PCLK
    ADC_InitStruct.ADC_Mode             = ADC_Mode_Imm;
    ADC_InitStruct.ADC_DataAlign        = ADC_DataAlign_Right;
    ADC_Init(ADC1, &ADC_InitStruct);

    // 3. Configure sampling time for fast and safe settling (14.5 + 12.5 = 27 cycles @ 8MHz = 3.3us)
    ADC_SampleTimeConfig(ADC1, ADC_SampleTime_14_5);

    // 4. Configure PA7, PA4, and PA2 as Analog Inputs (AIN)
    // Note: PA4 is tied to PA7 on the PCB. We set PA4 to AIN to safely disable its digital buffer.
    RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOA, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7 | GPIO_Pin_4 | GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_High;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 5. Enable ADC1
    ADC_Cmd(ADC1, ENABLE);
}

static inline uint16_t adc_read(uint8_t channel) {
    static uint8_t last_channel = 0xFF;
    
    ADC_AnyChannelNumCfg(ADC1, 0);
    ADC_AnyChannelSelect(ADC1, ADC_AnyChannel_0, channel);
    ADC_AnyChannelCmd(ADC1, ENABLE);

    // 1. Perform dummy conversion ONLY if we switched channels to let the S&H capacitor settle
    if (channel != last_channel) {
        last_channel = channel;
        
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        while (RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {
            __ASM("nop");
        }
        ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
        (void)ADC_GetConversionValue(ADC1);
    }

    // 2. Perform actual high-precision conversion
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {
        __ASM("nop");
    }

    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    uint16_t value = ADC_GetConversionValue(ADC1);

    ADC_AnyChannelCmd(ADC1, DISABLE);

    return value;
}

volatile int32_t latest_current_ma = 0;

static inline int32_t update_current_ma(void) {
    static int32_t filtered_current_q8 = -1;
    
    // --- PWM SYNC FOR TRUE MOTOR PHASE CURRENT ---
    // SysTick and TIM1 are perfectly phase-locked, which causes the ADC 
    // to blindly sample the exact same spot in the PWM cycle every time.
    // If it samples the "off" time, it falsely reports 0mA (aliasing).
    // We must wait for the exact midpoint of the active PWM pulse to read the true phase current!
    uint32_t arr = TIM1->ARR;
    uint32_t ccr2 = TIM1->CCR2;
    uint32_t ccr3 = TIM1->CCR3;
    
    uint32_t sample_target = 0;
    uint32_t pulse_width = 0;

    if (ccr3 == arr || ccr2 == arr) {
        // Slow Decay (Brake Mode) - Pulse happens at the VERY END of the cycle
        pulse_width = arr - (ccr3 == arr ? ccr2 : ccr3);
        sample_target = arr - (pulse_width / 2);
    } else {
        // Fast Decay (Coast Mode) - Pulse happens at the VERY BEGINNING of the cycle
        pulse_width = (ccr3 == 0 ? ccr2 : ccr3);
        sample_target = pulse_width / 2;
    }
    
    // Only synchronize if the pulse is wide enough for the ADC to capture (~2us)
    if (pulse_width > 100 && arr > 0) {
        // We trigger slightly before target (20 ticks = ~0.4us) to account for ADC S&H time
        uint32_t trigger_point = (sample_target >= 20) ? (sample_target - 20) : 0;
        
        uint32_t timeout = 4000; // Hard timeout to prevent infinite loops (covers >1 full cycle)
        while (timeout > 0) {
            uint32_t cnt = TIM1->CNT;
            uint32_t dist = (trigger_point >= cnt) ? (trigger_point - cnt) : (arr - cnt + trigger_point);
            if (dist < 40) {
                break; // We are in the golden window! Shoot the ADC!
            }
            timeout--;
        }
    }
    // ---------------------------------------------

    // Perform fast non-blocking analog conversion (filtered by EMA)
    uint16_t raw_adc = adc_read(ADC_Channel_5); // PA2 maps to ADC1_VIN[5]
    
    // Apply baseline offset calibration, with a piecewise smooth transition
    // to preserve a clean 0mA reading at zero-current baseline while keeping
    // the +17 hardware offset derived from the 4-point CC bench supply calibration.
    int32_t corrected_raw = (int32_t)raw_adc - zero_current_offset_adc;
    if (corrected_raw < 0) {
        corrected_raw = 0;
    } else if (corrected_raw <= 17) {
        corrected_raw = 2 * corrected_raw; // Smoothly ramp up from 0 to 34
    } else {
        corrected_raw = corrected_raw + 17; // Apply the +17 offset for active currents
    }
    
    // Scale standard integer calculation directly to Q8 format
    // Multiplier (384041 >> 10) derived from physical dummy-load calibration (Slope = 1.465 mA/count)
    // Use unsigned 32-bit multiply to avoid signed overflow, then cast back.
    int32_t current_ma_q8 = (int32_t)(((uint32_t)corrected_raw * 384041U) >> 10);
    
    if (filtered_current_q8 < 0) {
        filtered_current_q8 = current_ma_q8;
    } else {
        // Apply EMA filter: alpha = 0.15 -> Q8 weight is 38/256
        filtered_current_q8 = (38 * current_ma_q8 + 218 * filtered_current_q8) >> 8;
    }
    
    latest_current_ma = (filtered_current_q8 >> 8);
    return latest_current_ma; // convert back to standard integer milliamps
}

static inline int32_t get_current_ma(void) {
    return latest_current_ma;
}

// Transmit immediate status packet reply (echoing instruction)
void send_status_reply(uint8_t echoed_instruction) {
    
    uint8_t packet[11];
    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = config.servo_id;
    packet[3] = 0x07; // Length: Instruction (1) + 5 Params + Checksum (1)
    packet[4] = echoed_instruction;
    
    // Param 0,1: Current Angle (LSB/MSB)
    packet[5] = (uint8_t)(current_angle & 0xFF);
    packet[6] = (uint8_t)((current_angle >> 8) & 0xFF);
    
    // Param 2,3: Current Draw (LSB/MSB)
    int32_t current_ma = get_current_ma();
    packet[7] = (uint8_t)(current_ma & 0xFF);
    packet[8] = (uint8_t)((current_ma >> 8) & 0xFF);
    
    // Param 4: Status Flags (Bit 0: Moving, Bit 1: Over_Current, Bit 2: Holding)
    uint8_t flags = 0;
    if (status_reporting_enabled) {
        flags |= (1 << 0);
    }
    if (overcurrent_fault) {
        flags |= 0x02;
    }
    if (yield_active) {
        flags |= 0x04;
    }
    packet[9] = flags;
    
    // Checksum: lower 8 bits of bitwise NOT of sum of ID to last parameter
    uint8_t sum = packet[2] + packet[3] + packet[4] + packet[5] + packet[6] + packet[7] + packet[8] + packet[9];
    packet[10] = ~sum;
    
    // Transmit over shared single-wire bus
    uart_enable_tx();
    for (int i = 0; i < 11; i++) {
        uart_putchar_raw((char)packet[i]);
    }
    uart_enable_rx();
}

void send_config_reply(void) {
    
    uint8_t packet[36];
    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = config.servo_id;
    packet[3] = 32; // Length: Instruction (1) + 30 Params + Checksum (1)
    packet[4] = 0x05; // Echoed Instruction
    
    // Copy the entire 30-byte config struct as parameters
    uint8_t *config_bytes = (uint8_t *)&config;
    for (int i = 0; i < 30; i++) {
        packet[5 + i] = config_bytes[i];
    }
    
    // Checksum: lower 8 bits of bitwise NOT of sum of ID to last parameter
    uint8_t sum = packet[2] + packet[3] + packet[4];
    for (int i = 0; i < 30; i++) {
        sum += packet[5 + i];
    }
    packet[35] = ~sum;
    
    // Transmit over shared single-wire bus
    uart_enable_tx();
    for (int i = 0; i < 36; i++) {
        uart_putchar_raw((char)packet[i]);
    }
    uart_enable_rx();
}

// Non-blocking binary packet parser (Now driven by Hardware Interrupt!)
void USART1_IRQHandler(void) {
    // Clear UART Error flags (Overrun, Noise, Framing) by reading SR then DR
    if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET ||
        USART_GetFlagStatus(USART1, USART_FLAG_NF)  != RESET ||
        USART_GetFlagStatus(USART1, USART_FLAG_FE)  != RESET) {
        volatile uint16_t dummy = USART_ReceiveData(USART1);
        (void)dummy;
    }

    static RxState rx_state = RX_STATE_HEADER1;
    static uint8_t rx_id = 0;
    static uint8_t rx_length = 0;
    static uint8_t rx_instruction = 0;
    static uint8_t rx_params[64];
    static uint8_t rx_param_count = 0;
    static uint8_t target_param_count = 0;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        uint8_t c = (uint8_t)USART_ReceiveData(USART1);

        switch (rx_state) {
            case RX_STATE_HEADER1:
                if (c == 0xFF) {
                    rx_state = RX_STATE_HEADER2;
                }
                break;
            case RX_STATE_HEADER2:
                if (c == 0xFF) {
                    rx_state = RX_STATE_ID;
                } else {
                    rx_state = RX_STATE_HEADER1;
                }
                break;
            case RX_STATE_ID:
                if (c == config.servo_id || c == 0xFE) { // Explicit ID or Broadcast ID
                    rx_id = c;
                    rx_state = RX_STATE_LENGTH;
                } else if (c == 0xFF) {
                    rx_state = RX_STATE_ID; // Shifted header: could be 3rd 0xFF in a row
                } else {
                    rx_state = RX_STATE_HEADER1;
                }
                break;
            case RX_STATE_LENGTH:
                if (c >= 2 && c <= 64) {
                    rx_length = c;
                    rx_state = RX_STATE_INSTRUCTION;
                } else {
                    rx_state = RX_STATE_HEADER1;
                }
                break;
            case RX_STATE_INSTRUCTION:
                rx_instruction = c;
                rx_param_count = 0;
                target_param_count = rx_length - 2;
                if (target_param_count > 0) {
                    rx_state = RX_STATE_PARAMETERS;
                } else {
                    rx_state = RX_STATE_CHECKSUM;
                }
                break;
            case RX_STATE_PARAMETERS:
                rx_params[rx_param_count++] = c;
                if (rx_param_count >= target_param_count) {
                    rx_state = RX_STATE_CHECKSUM;
                }
                break;
            case RX_STATE_CHECKSUM:
                {
                    uint8_t rx_checksum = c;
                    uint8_t sum = rx_id + rx_length + rx_instruction;
                    for (uint8_t i = 0; i < target_param_count; i++) {
                        sum += rx_params[i];
                    }
                    uint8_t calculated_checksum = ~sum;

                    if (calculated_checksum == rx_checksum) {
                        // 1. CONTROL Command
                        if (rx_instruction == 0x01) {
                            // Ignore move command if currently faulted
                            if (!overcurrent_fault) {
                                uint16_t cmd_angle = rx_params[0] | (rx_params[1] << 8);
                                uint16_t cmd_velocity = rx_params[2] | (rx_params[3] << 8);
                                uint16_t cmd_current = 0;
                                
                                // Support new 6-byte packet with current, or fallback to older 4-byte packet
                                if (target_param_count >= 6) {
                                    cmd_current = rx_params[4] | (rx_params[5] << 8);
                                }
                                
                                if (cmd_angle < config.min_angle) cmd_angle = config.min_angle;
                                if (cmd_angle > config.max_angle) cmd_angle = config.max_angle;
                                
                                target_angle = cmd_angle;
                                active_velocity = (cmd_velocity == 0) ? config.max_velocity : cmd_velocity;
                                active_current_limit = (cmd_current == 0) ? config.current_limit : cmd_current;
                                status_reporting_enabled = 1;
                                motor_armed = 1; // Arm motor upon first valid CONTROL command!
                            }
                            // Reply removed to speed up control loop
                            // if (rx_id != 0xFE) {
                            //     pending_reply_cmd = 0x01;
                            //     reply_trigger_time_ms = millis() + 2;
                            // }
                        } 
                        // 2. CONFIG Command
                        else if (rx_instruction == 0x02) {
                            uint8_t update_mask = rx_params[0];
                            ServoConfig new_cfg = config;
                            
                            if (update_mask & (1 << 0)) {
                                new_cfg.servo_id = rx_params[1] & 0x7F; // Extract 7-bit ID
                                new_cfg.direction_invert = (rx_params[1] >> 7) & 0x01; // Extract MSB as direction invert flag
                            }
                            if (update_mask & (1 << 1)) {
                                new_cfg.min_angle = rx_params[2] | (rx_params[3] << 8);
                                new_cfg.max_angle = rx_params[4] | (rx_params[5] << 8);
                            }
                            if (update_mask & (1 << 2)) {
                                new_cfg.max_velocity = rx_params[6] | (rx_params[7] << 8);
                            }
                            if (update_mask & (1 << 3)) {
                                new_cfg.current_limit = rx_params[8] | (rx_params[9] << 8);
                            }
                            if (update_mask & (1 << 4)) {
                                new_cfg.kp_q16 = rx_params[10] | (rx_params[11] << 8) | (rx_params[12] << 16) | (rx_params[13] << 24);
                                new_cfg.ki_q16 = rx_params[14] | (rx_params[15] << 8) | (rx_params[16] << 16) | (rx_params[17] << 24);
                                new_cfg.kd_q16 = rx_params[18] | (rx_params[19] << 8) | (rx_params[20] << 16) | (rx_params[21] << 24);
                            }
                            if (update_mask & (1 << 5)) {
                                new_cfg.zero_adc = rx_params[22] | (rx_params[23] << 8);
                                new_cfg.adc_per_360 = rx_params[24] | (rx_params[25] << 8);
                            }
                            
                            // Bit 6: Volatile (RAM-only) update flag
                            if (!(update_mask & (1 << 6))) {
                                flash_write_config(&new_cfg);
                            }
                            config = new_cfg;
                            Kp_q16 = config.kp_q16;
                            Ki_q16 = config.ki_q16;
                            Ki_scaled_q16 = (config.ki_q16 * 16777) >> 24;
                            Kd_q16 = config.kd_q16;
                            
                            if (config.adc_per_360 == 0) config.adc_per_360 = 1;
                            adc_to_angle_mult_q16 = (360 << 16) / config.adc_per_360;
                            
                            if (rx_id != 0xFE) {
                                pending_reply_cmd = 0x02;
                                reply_trigger_time_ms = millis() + 2;
                            }
                        } 
                        // 3. POLL_STATUS Command
                        else if (rx_instruction == 0x03) {
                            if (rx_id != 0xFE) {
                                pending_reply_cmd = 0x03;
                                reply_trigger_time_ms = millis() + 2;
                            }
                        } 
                        // 4. CLEAR_ERROR Command
                        else if (rx_instruction == 0x04) {
                            if (rx_params[0] == 1) { // 1 = Clear Error
                                overcurrent_fault = 0;
                                overcurrent_ms = 0;
                                pid_integral = 0;
                                prev_error = 0;
                                motor_armed = 0; // Disarm motor to allow manual shaft positioning!
                                target_angle = current_angle;
                                ghost_angle_q8 = current_angle << 8;
                                
                                // Reply removed to speed up control loop
                                // if (rx_id != 0xFE) {
                                //     pending_reply_cmd = 0x04;
                                //     reply_trigger_time_ms = millis() + 2;
                                // }
                            }
                        }
                        // 5. READ_CONFIG Command
                        else if (rx_instruction == 0x05) {
                            if (rx_id != 0xFE) {
                                pending_reply_cmd = 0x05;
                                reply_trigger_time_ms = millis() + 2;
                            }
                        }

                    }
                    rx_state = RX_STATE_HEADER1;
                }
                break;
        }
    } else {
        // Clear any stray error flags (ORE, NE, FE, PE) that could cause an infinite IRQ loop
        (void)USART_ReceiveData(USART1);
    }
}

// PID Controller Loop
static inline void pid_update(uint32_t arr_period) {
    if (overcurrent_fault) {
        TIM_SetCompare3(TIM1, 0);
        TIM_SetCompare2(TIM1, 0);
        return;
    }

    if (!motor_armed) {
        TIM_SetCompare3(TIM1, 0);
        TIM_SetCompare2(TIM1, 0);
        return;
    }

    // 3. Compute error relative to the Ghost Target
    pid_error = ghost_angle_q8 - current_angle_q8;

    // 4. Check Deadband (only when Ghost Target has fully caught up to final target)
    if (ghost_angle_q8 == (target_angle << 8)) {
        int32_t abs_error = (pid_error >= 0) ? pid_error : -pid_error;
        if (abs_error < DEADBAND_Q8) {
            pid_integral = 0;
            prev_error = 0;
            if (status_reporting_enabled) {
                status_reporting_enabled = 0;
#if DEBUG_LOG
                print_status();
                uart_print("[STATUS] Target reached! Motor is now idle.\r\n");
#endif
            }
            
            // Idle state: If forced, coast. Otherwise, hard brake.
            if (yield_active) {
                TIM_SetCompare3(TIM1, 0);
                TIM_SetCompare2(TIM1, 0);
            } else {
                TIM_SetCompare3(TIM1, arr_period);
                TIM_SetCompare2(TIM1, arr_period);
            }
            return;
        } else {
            // Actively tracking outside the deadband, so we are still moving
            status_reporting_enabled = 1;
        }
    }

    // 5. Calculate P, I, D outputs using Q24 scaling
    int64_t p_term = (int64_t)Kp_q16 * (int64_t)pid_error;

    if (!yield_active) {
        pid_integral += pid_error;
        if (pid_integral > INTEGRAL_LIMIT_Q8) pid_integral = INTEGRAL_LIMIT_Q8;
        else if (pid_integral < -INTEGRAL_LIMIT_Q8) pid_integral = -INTEGRAL_LIMIT_Q8;
    } else {
        // Anti-windup: when yielding, gently decay the integral term to prevent snapping 
        // when the obstacle is removed.
        pid_integral = (pid_integral * 250) / 256;
    }
    
    int64_t i_term = (int64_t)Ki_scaled_q16 * (int64_t)pid_integral;

    pid_derivative = pid_error - prev_error;
    prev_error = pid_error;
    
    int64_t d_term = (int64_t)Kd_q16 * (int64_t)pid_derivative * 1000;

    int64_t pid_out_q24 = p_term + i_term + d_term;
    int32_t pid_out = (int32_t)(pid_out_q24 >> 24);

    // 6. Direct PWM generation
    int32_t pulse = (pid_out >= 0) ? pid_out : -pid_out;
    
    if (pulse > pwm_clamp) {
        pulse = pwm_clamp;
    } else if (pulse > (int32_t)arr_period) {
        pulse = (int32_t)arr_period;
    }

    int8_t drive_direction = (pid_out >= 0) ? 1 : -1;
    if (config.direction_invert) {
        drive_direction = -drive_direction; // Swap effective direction
    }

    if (drive_direction > 0) {
        if (yield_active) {
            // Fast decay (coast mode) -> Soft, yielding backdrive
            TIM_SetCompare3(TIM1, pulse);
            TIM_SetCompare2(TIM1, 0);
        } else {
            // Slow decay (brake mode) -> Stiff, precise holding
            TIM_SetCompare3(TIM1, arr_period);
            TIM_SetCompare2(TIM1, arr_period - pulse);
        }
    } else {
        if (yield_active) {
            TIM_SetCompare3(TIM1, 0);
            TIM_SetCompare2(TIM1, pulse);
        } else {
            TIM_SetCompare3(TIM1, arr_period - pulse);
            TIM_SetCompare2(TIM1, arr_period);
        }
    }
}



// 1ms Critical Task Loop (Trajectory Ramping, Protection Checks & State Machine)
static inline void one_ms_task(uint32_t arr_period) {
    // 1. Read potentiometer raw ADC and apply low pass filter (updates current_angle_q8 and current_angle)
    static int32_t filtered_adc_q8 = -1;
    uint16_t raw_adc = adc_read(ADC_Channel_7);
    int32_t raw_adc_q8 = ((int32_t)raw_adc) << 8;
    if (filtered_adc_q8 < 0) {
        filtered_adc_q8 = raw_adc_q8;
    } else {
        // alpha = 0.10 -> Q8 equivalent is 26/256 for smooth PID control
        filtered_adc_q8 = (26 * raw_adc_q8 + 230 * filtered_adc_q8) >> 8;
    }

    int32_t active_adc_q8 = filtered_adc_q8 - (config.zero_adc << 8);
    current_angle_q8 = (int32_t)(((int64_t)active_adc_q8 * adc_to_angle_mult_q16) >> 16);
    current_angle = (current_angle_q8 + 128) >> 8;

    // 2. Over-Current Protection (HARD FAULT ONLY)
    int32_t current_ma = update_current_ma();
    if (current_ma > HARD_OCP_LIMIT_MA) {
        overcurrent_ms++;
        if (overcurrent_ms >= 50) {
            overcurrent_fault = 1;
            TIM_SetCompare3(TIM1, 0);
            TIM_SetCompare2(TIM1, 0);
            return;
        }
    } else {
        overcurrent_ms = 0;
    }

    // 0. Safety Check
    if (overcurrent_fault) {
        TIM_SetCompare3(TIM1, 0);
        TIM_SetCompare2(TIM1, 0);
        return;
    }

    // 3. Dynamic PWM Clamping (Force Control) & Trajectory Ramping
    int32_t true_target_q8 = target_angle << 8;
    
    if (current_ma > (int32_t)active_current_limit) {
        // Yield: force is too high. Rapidly reduce the allowed PWM to drop torque.
        pwm_clamp -= 50; 
        if (pwm_clamp < 0) pwm_clamp = 0;
        yield_active = 1;
    } else {
        // Force is safe. Slowly recover the allowed PWM to prevent oscillation.
        pwm_clamp += 5;
        if (pwm_clamp > (int32_t)arr_period) pwm_clamp = arr_period;
        if (pwm_clamp == (int32_t)arr_period) yield_active = 0;
    }
        
    // Normal trajectory ramping (always advances; the PWM clamp handles the force limit)
    if (active_velocity == 0) {
        ghost_angle_q8 = true_target_q8;
    } else {
        // Calculate max allowed step per millisecond based on active_velocity (Q8 format)
        int32_t max_step_q8 = ((uint32_t)active_velocity * 256) / 1000;
        
        if (ghost_angle_q8 < true_target_q8) {
            ghost_angle_q8 += max_step_q8;
            if (ghost_angle_q8 > true_target_q8) ghost_angle_q8 = true_target_q8;
        } else if (ghost_angle_q8 > true_target_q8) {
            ghost_angle_q8 -= max_step_q8;
            if (ghost_angle_q8 < true_target_q8) ghost_angle_q8 = true_target_q8;
        }
    }
    
    pid_update(arr_period);
}

// Telemetry output logger
void print_status(void) {
    uart_print("[STATUS] Target: ");
    uart_print_int(target_angle);
    uart_print(" deg | Current: ");
    uart_print_int(current_angle);
    uart_print(" deg | Error: ");
    
    int32_t err = target_angle - current_angle;
    if (err < 0) {
        uart_print("-");
        uart_print_int(-err);
    } else {
        uart_print_int(err);
    }
    
    uart_print(" deg | Current Draw: ");
    uart_print_int(get_current_ma());
    uart_print(" mA | Duty: ");
    
    uint32_t pulse3 = TIM1->CCR3;
    uint32_t pulse2 = TIM1->CCR2;
    uint32_t arr = TIM1->ARR;
    if (arr == 0) arr = 1;
    
    if (pulse3 > 0) {
        uart_print_int((pulse3 * 100) / arr);
        uart_print("% (PA6 Forward)\r\n");
    } else if (pulse2 > 0) {
        uart_print_int((pulse2 * 100) / arr);
        uart_print("% (PA8 Backward)\r\n");
    } else {
        uart_print("0% (Idle/Deadband)\r\n");
    }
}

void calibrate_current_sensor(void) {
    int32_t sum = 0;
    // Take 16 quick sequential readings to calculate a clean average offset
    for (int i = 0; i < 16; i++) {
        sum += adc_read(ADC_Channel_5); // PA2 maps to ADC1_VIN[5]
        delay_ms(1);
    }
    zero_current_offset_adc = sum / 16;
    
#if DEBUG_LOG
    uart_print("Current Sensor Baseline Calibrated. Zero-Offset: ");
    uart_print_int(zero_current_offset_adc);
    uart_print(" raw ADC counts.\r\n");
#endif
}

int main(void) {
    // Synchronize the SystemCoreClock variable with the actual hardware PLL speed
    // The C-runtime initialization overwrites the value set in SystemInit(), so we restore it here.
    SystemCoreClock = 48000000U;

    GPIO_InitTypeDef        GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_OCInitTypeDef       TIM_OCInitStruct;

    // (SysTick will be enabled at the end of initialization to prevent interrupt race conditions)

    // 2. Initialize Single-Wire Half-Duplex USART1 at 250000 Baud
    uart_init();
#if DEBUG_LOG
    uart_print("\n--- Microdrive Firmware Init ---\n");
#endif

    // 3. Load or initialize Flash Persistent Parameters
    flash_load_config(&config);
#if DEBUG_LOG
    uart_print("Flash Loaded Configuration ID: ");
    uart_print_int(config.servo_id);
    uart_print("\r\n");
#endif

    // 4. Initialize TIM1 and GPIOA
    RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TIM1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOA, ENABLE);

    // 5. Configure TIM1 base for 20kHz motor PWM
    uint32_t TimerClock = TIM_GetTIMxClock(TIM1);
    uint32_t TargetFrequency = 20000;
    uint32_t TimerPeriod = (TimerClock / TargetFrequency) - 1;
    active_timer_period = TimerPeriod;

    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
    TIM_TimeBaseStruct.TIM_Prescaler         = 0;
    TIM_TimeBaseStruct.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_Period            = TimerPeriod;
    TIM_TimeBaseStruct.TIM_ClockDivision     = TIM_CKD_Div1;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    // 6. Initialize TIM1 CH3 and CH2 output channels
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse        = 0;
    TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Set;
    TIM_OC3Init(TIM1, &TIM_OCInitStruct); // Channel 3 (PA6)
    TIM_OC2Init(TIM1, &TIM_OCInitStruct); // Channel 2 (PA8)

    // 7. Configure pin AF multiplexing
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_1);

    // 8. Configure Alternate Function push-pull pins for PWM channels
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_High;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 9. Configure Software Reset button on PA0
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_High;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU; // Input Pull-Up
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 10. Initialize ADC on PA7 and PA2
    adc_init();

    // Calibrate current sensor baseline offset (Auto-Zeroing)
    calibrate_current_sensor();

    // 11. Enable TIM1 Main Outputs
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    // 12. Soft Start: read current position to lock initial target securely
    uint16_t init_raw_adc = adc_read(ADC_Channel_7);
    int32_t init_active_adc_q8 = ((int32_t)init_raw_adc - config.zero_adc) << 8;
    int32_t init_angle_q8 = (int32_t)(((int64_t)init_active_adc_q8 * adc_to_angle_mult_q16) >> 16);
    
    current_angle_q8 = init_angle_q8;
    current_angle = (init_angle_q8 + 128) >> 8;
    target_angle = current_angle;
    ghost_angle_q8 = init_angle_q8;
    active_velocity = config.max_velocity;

#if DEBUG_LOG
    uart_print("Soft-Start Complete. Locked Initial Angle: ");
    uart_print_int(current_angle);
    uart_print(" deg.\r\n");
#endif

    // 13. Enable 1ms SysTick timekeeping interrupt and PID Loop
    SysTick_Config(SystemCoreClock / 1000);

    while (1) {
        // A. Software System Reset Trigger (Debounced reset button on PA0)
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET) {
#if DEBUG_LOG
            uart_print("\r\n[RESET] Triggering Software Reset via PA0...\r\n");
#endif
            delay_ms(50);
            NVIC_SystemReset();
        }
        
        // C. Send asynchronous TX replies safely without blocking the CPU
        if (pending_reply_cmd != 0 && millis() >= reply_trigger_time_ms) {
            if (pending_reply_cmd == 0x05) {
                send_config_reply();
            } else {
                send_status_reply(pending_reply_cmd);
            }
            pending_reply_cmd = 0;
        }

        // D. (PID loop is now handled purely in the background by SysTick_Handler!)
    }
}
