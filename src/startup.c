#include <stdint.h>

extern uint32_t _sidata; /* Start of data in FLASH */
extern uint32_t _sdata;  /* Start of data in RAM */
extern uint32_t _edata;  /* End of data in RAM */
extern uint32_t _sbss;   /* Start of bss in RAM */
extern uint32_t _ebss;   /* End of bss in RAM */
extern uint32_t _estack; /* Top of Stack */

extern int main(void);
extern void SystemInit(void);

void Reset_Handler(void) {
    // 1. Copy initialized data segment from FLASH to RAM
    uint32_t *pSource = &_sidata;
    uint32_t *pDest = &_sdata;
    while (pDest < &_edata) {
        *pDest++ = *pSource++;
    }

    // 2. Zero-fill the uninitialized bss segment
    pDest = &_sbss;
    while (pDest < &_ebss) {
        *pDest++ = 0;
    }

    // 3. Call the system clock initialization
    SystemInit();

    // 4. Jump to the main function
    main();

    // 5. Catch-all loop
    while (1) {
    }
}

void Default_Handler(void) {
    while (1) {
    }
}

// Weak symbol mapping for interrupts
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

// Peripheral Interrupts
void IWDG_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void ADC1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void TIM14_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));

// Vector Table (aligned and placed in .isr_vector section)
__attribute__((section(".isr_vector"), used))
void (* const g_pFnVectors[])(void) = {
    (void (*)(void))&_estack,  // Initial Stack Pointer
    Reset_Handler,             // Reset Handler
    NMI_Handler,               // NMI Handler
    HardFault_Handler,         // Hard Fault Handler
    0, 0, 0, 0, 0, 0, 0,       // Reserved
    SVC_Handler,               // SVCall Handler
    0, 0,                      // Reserved
    PendSV_Handler,            // PendSV Handler
    SysTick_Handler,           // SysTick Handler

    // External Interrupts (IRQs)
    IWDG_IRQHandler,           // IRQ0: IWDG
    PVD_IRQHandler,            // IRQ1: PVD
    0,                         // IRQ2: Reserved
    FLASH_IRQHandler,          // IRQ3: FLASH
    RCC_IRQHandler,            // IRQ4: RCC
    EXTI0_1_IRQHandler,        // IRQ5: EXTI Line 0 and 1
    EXTI2_3_IRQHandler,        // IRQ6: EXTI Line 2 and 3
    EXTI4_15_IRQHandler,       // IRQ7: EXTI Line 4 to 15
    0, 0, 0, 0,                // IRQ8 - 11: Reserved
    ADC1_IRQHandler,           // IRQ12: ADC1
    TIM1_BRK_UP_TRG_COM_IRQHandler, // IRQ13: TIM1 Break, Update, Trigger and Commutation
    TIM1_CC_IRQHandler,        // IRQ14: TIM1 Capture Compare
    0,                         // IRQ15: Reserved
    TIM3_IRQHandler,           // IRQ16: TIM3
    0, 0,                      // IRQ17, 18: Reserved
    TIM14_IRQHandler,          // IRQ19: TIM14
    0, 0, 0,                   // IRQ20 - 22: Reserved
    I2C1_IRQHandler,           // IRQ23: I2C1
    0,                         // IRQ24: Reserved
    SPI1_IRQHandler,           // IRQ25: SPI1
    0,                         // IRQ26: Reserved
    USART1_IRQHandler,         // IRQ27: USART1
    USART2_IRQHandler,         // IRQ28: USART2
    0, 0, 0                    // IRQ29 - 31: Reserved
};
