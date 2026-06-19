# 🔧 Hardware Documentation

μDrive is an open-source servo controller that turns any standard DC brushed motor into a closed-loop microdrive. This document covers the hardware design, board variants, components, and PCB files.

---

## 📋 Board Variants

Microdrive ships as **two PCB variants**. Both share the same MCU, voltage regulator, current sensor, firmware, and communication protocol. The only difference is the **motor driver IC** and the resulting form factor.

| | Generic Servo Board | MG996 Drop-in Board |
|---|---|---|
| **Motor Driver** | CP2119 | BDR6121H |
| **Form Factor** | Generic — attach to any DC brushed motor | Drop-in replacement for MG996R servo |
| **Operating Voltage** | Up to 18V max | Up to 7.5V max |
| **Current Rating** | 5A continuous | 1.5A continuous / 3A peak |
| **Schematic** | `servo_pcb.kicad_sch` | `servo_pcb_mg99x.kicad_sch` |
| **PCB Layout** | `servo_pcb.kicad_pcb` | `servo_pcb_mg99x.kicad_pcb` |

> [!TIP]
> Both boards run identical firmware. Choose the variant that fits your mechanical design — or use the Generic board as a universal motor controller.

---

## ⚙️ Common Specifications

| Parameter | Value |
|---|---|
| **MCU** | MindMotion MM32G0001 (32-bit ARM Cortex-M0, 48 MHz) |
| **Flash / RAM** | 16 KB / 2 KB |
| **Voltage Regulator** | SL7533-3 (3.3V LDO, input up to 24V) |
| **Current Sensor** | INA180A2 (current sense amplifier) with 0.01Ω shunt (R1, 2512 package) |
| **Motor PWM** | TIM1 CH2 (PA8) / CH3 (PA6), 20 kHz, H-bridge control |
| **Communication** | Half-duplex single-wire UART on PA12 (open-drain), 250000 baud, 8N1 |
| **Programming** | SWD via SWCLK and SWDIO test pads (use Picoprobe / CMSIS-DAP) |

### Feedback Options

μDrive supports two mutually exclusive feedback mechanisms:

| Feedback Type | Details |
|---|---|
| **Analog Potentiometer** | Connected to PA7 (ADC Channel 7). Shared with the SDA pin on the I2C header. |
| **I2C Magnetic Encoder** | AS5600 footprint with 4-pad header: 3.3V, SCL, SDA, GND. *(Hardware ready, software planned.)* |

> [!NOTE]
> The potentiometer input and the SDA pin share the same physical trace on the PCB. You can use one or the other — not both simultaneously.

---

## 🗺️ Pin Mapping (MM32G0001 — TSSOP-20)

| Pin | Function | Notes |
|---|---|---|
| PA12 | UART TX/RX | Half-duplex single-wire bus (open-drain, AF1) |
| PA6 | TIM1 CH3 (PWM) | H-bridge output A (AF4). Also heartbeat LED in debug. |
| PA8 | TIM1 CH2 (PWM) | H-bridge output B (AF1) |
| PA7 | ADC Channel 7 | Potentiometer feedback (analog input) |
| PA5 | I2C SCL | Clock line for optional AS5600 encoder / SCL test pad (AF1) |
| PA4 | I2C SDA | Tied to PA7 on PCB — digital buffer disabled for noise reduction (SDA) |
| PA2 | ADC Channel 5 | Current sense amplifier output (INA180A2) |
| PA0 | GPIO Input (Pull-Up) | Software reset button |
| SWCLK | SWD Clock | Programming/debug pad |
| SWDIO | SWD Data | Programming/debug pad |

---

## 📦 Bill of Materials

| Designator | Package | Value | Component |
|---|---|---|---|
| U1 | TSSOP-20 | MM32G0001 | MCU |
| U2 | SOT-23 | SL7533-3 | 3.3V LDO Regulator |
| U3 | SOIC-8 | BDR6121H *(MG996)* / CP2119 *(Generic)* | Motor Driver |
| U4 | SOT-23-5 | INA180A2 | Current Sense Amplifier |
| U5 | SOIC-8 | AS5600 | I2C Magnetic Encoder *(optional)* |
| R1 | 2512 | 0.01Ω | Current Sense Shunt Resistor |
| R2, R3, R4 | 0805 | 10KΩ | Pull-up / Pull-down Resistors |
| C1, C4 | 0805 | 10μF | Decoupling Capacitors |
| C2, C3, C5 | 0805 | 100nF | Bypass Capacitors |
| J1 | Pin Header 1×03, P2.54mm | Power In | Power Connector |

### Test Pads

The PCB exposes the following test pads for probing and programming:

| Pad | Description |
|---|---|
| 3.3V | Regulated logic supply |
| GND | Ground |
| SDA | I2C data / Potentiometer analog signal |
| SCL | I2C clock |
| SWCLK | SWD clock (labeled **C** on the board) |
| SWDIO | SWD data (labeled **D** on the board) |
| +VE | Motor positive terminal |
| -VE | Motor negative terminal |


## 📁 PCB Files

All hardware design files are located in the [`PCB/`](../PCB/) directory of the repository. The project uses **KiCad** as the EDA tool.

### File Listing

| File | Description |
|---|---|
| `servo_pcb.kicad_sch` | Generic board schematic |
| `servo_pcb.kicad_pcb` | Generic board PCB layout |
| `servo_pcb.kicad_pro` | Generic board KiCad project |
| `servo_pcb-mg99x.kicad_sch` | MG996 drop-in board schematic |
| `servo_pcb_mg99x.kicad_pcb` | MG996 drop-in board PCB layout |
| `servo_pcb_mg99x.kicad_pro` | MG996 drop-in board KiCad project |

### Custom Symbol Libraries

| File | Component |
|---|---|
| `mm32g0001a1t.kicad_sym` | MM32G0001 MCU |
| `BDR6121H.kicad_sym` | BDR6121H motor driver |
| `CP2119L.kicad_sym` | CP2119 motor driver |
| `AS5600.kicad_sym` | AS5600 magnetic encoder |
| `sl7533-3.kicad_sym` | SL7533-3 voltage regulator |



## ⚖️ Licensing

| Component | License |
|---|---|
| Hardware (PCBs / Schematics) | [CERN-OHL-P v2](../LICENSE-HARDWARE.txt) |
| Software / Firmware | [MIT License](../LICENSE) |
