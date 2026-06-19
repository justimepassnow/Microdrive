# 💻 Firmware Documentation

The μDrive firmware is a bare-metal C application running on the MindMotion MM32G0001 (ARM Cortex-M0). It implements closed-loop position control with velocity trajectory profiling, overcurrent protection, and a binary packet communication protocol — all in 16 KB of Flash and 2 KB of RAM.

---

## 🏗️ Architecture Overview

| Parameter | Value |
|---|---|
| **Language** | C (bare-metal, no RTOS) |
| **MCU** | MM32G0001 — ARM Cortex-M0, TSSOP-20 |
| **System Clock** | 48 MHz (HSI, configured in `SystemInit()`) |
| **Flash** | 16 KB (0x08000000 – 0x08003FFF) |
| **RAM** | 2 KB (0x20000000 – 0x200007FF) |
| **Stack** | 512 bytes |
| **PID Loop Rate** | 1 ms (via SysTick interrupt) |
| **Motor PWM** | 20 kHz (TIM1, no prescaler) |
| **Arithmetic** | Q8 and Q16 fixed-point (no FPU on Cortex-M0) |

### Boot Sequence

1. `Reset_Handler` — Copies `.data` from Flash to RAM, zeroes `.bss`
2. `SystemInit()` — Configures HSI to 48 MHz, sets flash latency
3. `main()` — Initializes UART, loads flash config, configures TIM1 PWM, initializes ADC, calibrates current sensor, enables SysTick

### Source Files

| File | Purpose |
|---|---|
| `src/main.c` | Application logic: UART, protocol parser, PID controller, ADC, flash storage |
| `src/startup.c` | Vector table, `Reset_Handler`, weak IRQ symbol definitions |
| `src/hal_adc.c` | MindMotion HAL — ADC driver |
| `src/hal_gpio.c` | MindMotion HAL — GPIO driver |
| `src/hal_misc.c` | MindMotion HAL — NVIC utilities |
| `src/hal_rcc.c` | MindMotion HAL — Clock configuration |
| `src/hal_tim.c` | MindMotion HAL — Timer driver |
| `src/hal_usart.c` | MindMotion HAL — USART driver |
| `custom.ld` | Custom linker script (2 KB RAM, 16 KB Flash) |

---

## 📡 Communication Protocol

μDrive uses a **half-duplex single-wire UART** bus on **PA12** (open-drain) at **250000 baud, 8N1**. Multiple servos can share the same bus using unique IDs.

### Packet Format

All communication uses a binary packet format:

```text
┌──────┬──────┬──────┬────────┬─────────────┬──────────┬──────────┐
│ 0xFF │ 0xFF │  ID  │ Length │ Instruction │ Params…  │ Checksum │
└──────┴──────┴──────┴────────┴─────────────┴──────────┴──────────┘
```

| Field | Size | Description |
|---|---|---|
| Header | 2 bytes | Always `0xFF 0xFF` |
| ID | 1 byte | Target servo ID (`0`–`127`), or `0xFE` for broadcast |
| Length | 1 byte | Number of bytes following: `Instruction + Params + Checksum` |
| Instruction | 1 byte | Command opcode (see below) |
| Params | 0–N bytes | Instruction-specific payload |
| Checksum | 1 byte | `~(ID + Length + Instruction + Params) & 0xFF` |

> [!NOTE]
> Broadcast ID `0xFE` sends a command to all servos on the bus. No reply is generated for broadcast packets.

### Instructions

| Opcode | Name | Direction | Description |
|---|---|---|---|
| `0x01` | CONTROL | Master → Servo | Move to target angle with optional velocity and current limit |
| `0x02` | CONFIG | Master → Servo | Update configuration fields (with bitmask for partial updates) |
| `0x03` | POLL | Master → Servo | Request current status |
| `0x04` | CLEAR_ERROR | Master → Servo | Clear overcurrent faults and reset PID state |
| `0x05` | READ_CONFIG | Master → Servo | Read current flash configuration |

---

### 0x01 — CONTROL

Moves the servo to a target angle with optional velocity and current limit overrides.

**Parameters (4 or 6 bytes):**

| Byte | Field | Type | Description |
|---|---|---|---|
| 0–1 | `angle` | uint16 LE | Target angle in degrees |
| 2–3 | `velocity` | uint16 LE | Velocity in deg/s (`0` = use config default) |
| 4–5 | `current` | uint16 LE | Current limit in mA (`0` = use config default). *Optional.* |

**Behavior:**
- Angle is clamped to `[min_angle, max_angle]` from the config
- Arms the motor on the first valid CONTROL packet
- Ignored if an overcurrent fault is active
- No status reply is sent (for maximum control loop throughput)

---

### 0x02 — CONFIG

Updates one or more configuration fields. A **bitmask** in the first parameter byte selects which fields to write. Unselected fields remain unchanged.

**Parameters (up to 26 bytes):**

| Byte | Field | Bitmask Bit | Description |
|---|---|---|---|
| 0 | `update_mask` | — | Bitmask selecting which fields to update |
| 1 | `id_and_dir` | Bit 0 | Lower 7 bits = `servo_id`, MSB = `direction_invert` |
| 2–3 | `min_angle` | Bit 1 | Minimum angle limit (uint16 LE) |
| 4–5 | `max_angle` | Bit 1 | Maximum angle limit (uint16 LE) |
| 6–7 | `max_velocity` | Bit 2 | Default velocity, deg/s (uint16 LE) |
| 8–9 | `current_limit` | Bit 3 | Overcurrent threshold, mA (uint16 LE) |
| 10–13 | `kp_q16` | Bit 4 | Proportional gain, Q16 (int32 LE) |
| 14–17 | `ki_q16` | Bit 4 | Integral gain, Q16 (int32 LE) |
| 18–21 | `kd_q16` | Bit 4 | Derivative gain, Q16 (int32 LE) |
| 22–23 | `zero_adc` | Bit 5 | ADC value at 0° (int16 LE) |
| 24–25 | `adc_per_360` | Bit 5 | ADC ticks per 360° rotation (int16 LE) |

**Special flag — Bit 6 (Volatile):**
- If Bit 6 of `update_mask` is **set**, the config update is **RAM-only** (not persisted to flash).
- If Bit 6 is **clear**, the config is written to flash.

**Reply:** Status packet (11 bytes) echoing instruction `0x02`.

---

### 0x03 — POLL

Requests the servo's current status. No parameters.

**Reply:** Status packet (11 bytes).

---

### 0x04 — CLEAR_ERROR

Clears an overcurrent fault and resets the PID state.

**Parameters (1 byte):**

| Byte | Value | Description |
|---|---|---|
| 0 | `1` | Clear error flag, reset PID, disarm motor |

**Behavior:**
- Clears `overcurrent_fault` and `overcurrent_ms`
- Resets PID integral and derivative state
- Disarms motor (allows manual shaft positioning)
- Sets the target and ghost angles to the current physical angle

---

### 0x05 — READ_CONFIG

Reads the full configuration from the servo.

**Reply:** Config packet (36 bytes) — header + full `ServoConfig` struct as parameters.

---

### Status Reply Packet (11 bytes)

Sent in response to POLL or CONFIG commands:

```text
┌──────┬──────┬──────┬──────┬─────────────┬───────────────────────────────────┬──────────┐
│ 0xFF │ 0xFF │  ID  │ 0x07 │ Instruction │  angle(2) current(2) flags(1)    │ Checksum │
└──────┴──────┴──────┴──────┴─────────────┴───────────────────────────────────┴──────────┘
```

| Param Bytes | Field | Type | Description |
|---|---|---|---|
| 0–1 | `current_angle` | uint16 LE | Current servo angle in degrees |
| 2–3 | `current_ma` | uint16 LE | Current motor draw in milliamps |
| 4 | `flags` | uint8 | Status flags (see below) |

**Status Flags:**

| Bit | Name | Description |
|---|---|---|
| 0 | `MOVING` | Servo is actively tracking a target |
| 1 | `OVERCURRENT` | Overcurrent fault is active |
| 2 | `HOLDING` | Admittance yield mode is active (compliant holding) |

### Config Reply Packet (36 bytes)

Sent in response to READ_CONFIG:

```text
┌──────┬──────┬──────┬──────┬──────┬──────────────────────────────┬──────────┐
│ 0xFF │ 0xFF │  ID  │  32  │ 0x05 │  ServoConfig struct (30 B)   │ Checksum │
└──────┴──────┴──────┴──────┴──────┴──────────────────────────────┴──────────┘
```

---

## 🎯 PID Control System

### Control Loop Architecture

μDrive uses a **position PID controller with velocity trajectory profiling** (ghost target). The entire control loop runs inside the `SysTick_Handler` at a fixed 1 ms interval, guaranteeing deterministic timing even if the main loop is busy sending UART replies.

```text
                    ┌─────────────┐
  target_angle ───► │  Trajectory │ ───► ghost_angle_q8
                    │   Ramping   │        │
                    └─────────────┘        │
                                           ▼
                                    ┌──────────────┐
       current_angle_q8 ──────────►│  PID          │───► PWM duty
       (from ADC + filter)         │  Controller   │     (TIM1 CH2/CH3)
                                    └──────────────┘
                                           │
                                    ┌──────▼───────┐
                                    │  Overcurrent │
                                    │  Protection  │
                                    └──────────────┘
```

### Ghost Target (Velocity Profiling)

The **ghost target** (`ghost_angle_q8`) is an intermediate angle that ramps toward the final `target_angle` at the configured velocity. The PID controller tracks the ghost target — not the final target — producing smooth acceleration and deceleration.

```
Step per ms = (active_velocity × 256) / 1000    (Q8 format)
```

If `active_velocity` is `0`, the ghost target snaps instantly to the final target.

### PID Computation

All PID math uses **Q8 fixed-point** for angles and **Q16 fixed-point** for gains, combined through **Q24 intermediate precision** using 64-bit multiply:

```c
p_term = Kp_q16 × error_q8              // Q24
i_term = Ki_scaled_q16 × integral_q8     // Q24
d_term = Kd_q16 × derivative_q8 × 1000  // Q24 (scaled for 1ms timestep)

pid_output = (p_term + i_term + d_term) >> 24
```

### Key Parameters

| Parameter | Value | Description |
|---|---|---|
| Loop interval | 1 ms | SysTick-driven, deterministic |
| Deadband | 1° (256 in Q8) | Error below this → motor brakes / coasts |
| Integral windup limit | 25,600,000 (Q8) | ≈ 100 degree-seconds |
| ADC filter alpha | 0.10 (26/256) | EMA low-pass on potentiometer reading |
| Current filter alpha | 0.15 (38/256) | EMA low-pass on current measurement |

### Overcurrent Protection

μDrive implements a two-tier current protection system:

| Tier | Threshold | Behavior |
|---|---|---|
| **Soft limit** (admittance yield) | `current_limit` (configurable, default 1000 mA) | Dynamically clamps PWM duty cycle. Allows the motor to yield compliantly. |
| **Hard fault** | 2000 mA sustained for ≥ 50 ms | Latching fault — motor is disabled. Must be cleared with `CLEAR_ERROR` command. |

#### Soft Current Limiting (Admittance Yield Loop)

To prevent motor/driver overheating and enable compliant backdriving (force limiting), the controller implements a dynamic current-clamping algorithm in the 1 ms control loop:

1. **Dynamic PWM Clamping**:
   - Every 1 ms, if the filtered current `current_ma` exceeds `active_current_limit`, the allowable PWM duty cycle limit (`pwm_clamp`) is decremented:
     $$\text{pwm\_clamp} \leftarrow \max(0, \text{pwm\_clamp} - 20)$$
     This triggers the `yield_active` compliance flag.
   - If the current is below the threshold, the clamp slowly recovers toward the full timer period (`arr_period`):
     $$\text{pwm\_clamp} \leftarrow \min(\text{arr\_period}, \text{pwm\_clamp} + 5)$$
     Once `pwm_clamp` reaches `arr_period`, `yield_active` is cleared.
   - The PID output is then clamped to $[-\text{pwm\_clamp}, \text{pwm\_clamp}]$.

2. **Decay Mode Transition (Coast vs. Brake)**:
   - **Stiff Mode (`yield_active` is false)**: The driver operates in **slow decay (brake mode)**, where inactive outputs are held high. This provides maximum holding stiffness and positioning precision.
   - **Yield/Compliance Mode (`yield_active` is true)**: The driver switches to **fast decay (coast mode)**, pulsing only one phase while leaving the other at 0. This reduces braking torque and allows the shaft to yield/backdrive smoothly under external load.

### Motor Arming

The motor is **disarmed at boot**. It will not drive the motor until the first valid `CONTROL` packet is received. This prevents unexpected motion on power-up.

### Auto-Zero Calibration

At startup, the firmware reads 16 samples from the current sense ADC (with the motor off) and averages them to establish a zero-current baseline offset. This compensates for component tolerances in the INA180A2 and shunt resistor.

---

## 💾 Flash Configuration

Configuration is stored in **Flash page 15** (the last 1 KB page of the 16 KB flash), starting at address `0x08003C00`. A magic word (`0xDEADBEEF`) validates stored data.

### ServoConfig Structure (30 bytes, packed)

| Offset | Field | Type | Default | Description |
|---|---|---|---|---|
| 0 | `servo_id` | uint8 | `0` | Bus address (0–127) |
| 1 | `direction_invert` | uint8 | `0` | Motor direction (0 = normal, 1 = inverted) |
| 2 | `min_angle` | uint16 | `0` | Minimum angle limit (degrees) |
| 4 | `max_angle` | uint16 | `180` | Maximum angle limit (degrees) |
| 6 | `max_velocity` | uint16 | `180` | Default velocity (deg/s) |
| 8 | `current_limit` | uint16 | `1000` | Overcurrent threshold (mA) |
| 10 | `kp_q16` | int32 | `6553600` (= 100.0) | Proportional gain (Q16 fixed-point) |
| 14 | `ki_q16` | int32 | `3276` (= 0.05) | Integral gain (Q16 fixed-point) |
| 18 | `kd_q16` | int32 | `524288` (= 8.0) | Derivative gain (Q16 fixed-point) |
| 22 | `zero_adc` | int16 | `0` | Raw ADC value at 0° |
| 24 | `adc_per_360` | int16 | `6600` | ADC ticks per full 360° rotation |
| 26 | `magic` | uint32 | `0xDEADBEEF` | Validity marker |

> [!TIP]
> **Q16 conversion:** To convert a floating-point gain to Q16, multiply by 65536. For example, `Kp = 100.0` → `100.0 × 65536 = 6553600`.

### Flash Write Process

1. Motor PWM outputs are forced to 0 for safety
2. Flash page 15 is erased
3. Config struct is written as half-words (16-bit aligned)
4. Flash is re-locked

> [!CAUTION]
> Flash writes temporarily disable motor output. Avoid sending CONFIG commands during motion-critical operations unless using the volatile (Bit 6) flag.

---

## 🔨 Build & Flash

### Toolchain

| Tool | Purpose |
|---|---|
| **PlatformIO** | Build system (VS Code extension) |
| **GCC ARM** | Compiler (`arm-none-eabi-gcc`, via PlatformIO) |
| **pyocd** | Flash programmer |
| **Picoprobe / CMSIS-DAP** | SWD debug probe (Raspberry Pi Pico) |

### PlatformIO Configuration

The project repurposes the `ststm32` platform with the `disco_f030r8` board definition, overriding the memory layout to match the MM32G0001:

```ini
[env:disco_f030r8]
platform = ststm32
board = disco_f030r8
board_build.cpu = cortex-m0

upload_protocol = custom
upload_command = pyocd flash --pack "MindMotion.MM32G0001_DFP.1.0.1.pack" --target mm32g0001a1tc $SOURCE

board_upload.maximum_size = 16384
board_upload.maximum_ram_size = 2048
board_build.ldscript = custom.ld

build_flags =
  -D USE_STDPERIPH_DRIVER
```

### Build

```bash
# Using PlatformIO CLI
pio run

# Or use the PlatformIO "Build" button (checkmark icon) in VS Code
```

### Flash

Connect a Picoprobe (Raspberry Pi Pico with debugprobe firmware) via SWD:

| Pico Pin | μDrive Pad |
|---|---|
| 3V3 | 3.3V |
| GND | GND |
| GP2 | SWCLK (**C**) |
| GP3 | SWDIO (**D**) |

Then flash:

```bash
# Using PlatformIO (recommended)
pio run --target upload

# Or manually with pyocd
pyocd flash --pack "MindMotion.MM32G0001_DFP.1.0.1.pack" --target mm32g0001a1tc firmware.bin
```

> [!IMPORTANT]
> **Windows users:** If pyocd fails to detect the Picoprobe, use [Zadig](https://zadig.akeo.ie/) to replace the default driver with **WinUSB** for the "Picoprobe CMSIS-DAP" device.

The MindMotion DFP pack file (`MindMotion.MM32G0001_DFP.1.0.1.pack`) is included in the repository root.

### Custom Linker Script

The `custom.ld` file defines the memory layout for the MM32G0001:

```
MEMORY
{
  RAM    (xrw) : ORIGIN = 0x20000000, LENGTH = 2K
  FLASH  (rx)  : ORIGIN = 0x08000000, LENGTH = 16K
}
```

Stack size: 512 bytes. No heap is allocated.

---

## 📚 HAL Drivers

The project uses MindMotion's Standard Peripheral Library (HAL) for hardware abstraction. The following HAL modules are compiled into the firmware:

| Module | File | Functionality |
|---|---|---|
| ADC | `hal_adc.c` / `hal_adc.h` | 12-bit ADC for potentiometer and current sensing |
| GPIO | `hal_gpio.c` / `hal_gpio.h` | Pin configuration, alternate functions |
| MISC | `hal_misc.c` / `hal_misc.h` | NVIC interrupt priority and enable |
| RCC | `hal_rcc.c` / `hal_rcc.h` | Peripheral clock gating |
| TIM | `hal_tim.c` / `hal_tim.h` | TIM1 PWM output for H-bridge motor control |
| USART | `hal_usart.c` / `hal_usart.h` | Half-duplex single-wire UART |

---

## 🔄 Interrupt Map

| IRQ | Handler | Priority | Purpose |
|---|---|---|---|
| SysTick | `SysTick_Handler` | 0 | 1 ms PID loop, trajectory ramping, overcurrent protection |
| USART1 | `USART1_IRQHandler` | 1 | RX interrupt-driven binary packet parser |
| TIM1_CC | `TIM1_CC_IRQHandler` | 2 | Midpoint-synchronized current sample acquisition |

The PID loop runs entirely within the SysTick ISR (highest priority), ensuring deterministic 1 ms timing regardless of main-loop activity. The UART packet parser is fully interrupt-driven using a state machine, and the motor current is sampled asynchronously at the PWM midpoint using `TIM1` Channel 1 (CC1) to eliminate CPU busy-waiting.

---

## 📐 Fixed-Point Arithmetic Reference

Since the Cortex-M0 has no floating-point unit, all math uses integer fixed-point formats:

| Format | Fractional Bits | Resolution | Usage |
|---|---|---|---|
| **Q8** | 8 | 1/256 ≈ 0.004 | Angles, PID error, integral, derivative |
| **Q16** | 16 | 1/65536 ≈ 0.000015 | PID gains (`Kp`, `Ki`, `Kd`) |
| **Q24** | 24 | — | Intermediate PID computation (64-bit) |

**Conversion formulas:**
```
float → Q16:  value_q16 = (int32_t)(float_value × 65536)
Q16 → float:  float_value = value_q16 / 65536.0
float → Q8:   value_q8  = (int32_t)(float_value × 256)
Q8 → float:   float_value = value_q8 / 256.0
```
