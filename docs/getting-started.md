# 🚀 Getting Started with μDrive (Microdrive)

A step-by-step guide to flashing the servo board, wiring up a master controller, and commanding your first microdrive.

---

## 📋 Prerequisites

### Hardware

| Item | Notes |
|---|---|
| **Raspberry Pi Pico** | Used first as a programmer, then re-flashed as the master MCU |
| **μDrive board** | The MM32G0001-based servo controller PCB |
| **DC motor with potentiometer** | Any brushed DC motor within the driver limits (e.g., ≤ 7.5V / 1.5A for the MG996 board, or ≤ 18V / 5A for the Generic board) |
| **External power supply** | Suitable voltage for your motor and board (do **not** power the motor from the microcontroller's 3V3/5V pin) |
| **Jumper wires** | At least 4 for SWD programming + 3 for the servo bus |
| **Pull-up resistor** | 1 kΩ – 10 kΩ (4.7 kΩ recommended) for the single-wire data bus |
| **USB cable** | Micro-USB or USB-C depending on your Pico variant |

### Software

| Tool | Install |
|---|---|
| **VS Code** | [code.visualstudio.com](https://code.visualstudio.com/) |
| **PlatformIO extension** | Install from the VS Code Extensions marketplace |
| **Python 3.x** | [python.org](https://python.org/) |
| **pyocd** | `pip install pyocd` |
| **Node.js + npm** | Required only for the WebGUI (optional) |

---

## Step 1 — Flash the Servo Board

The μDrive board runs an MM32G0001 microcontroller. Since dedicated programmers for this chip are expensive and hard to find, we use a **$4 Raspberry Pi Pico** as a CMSIS-DAP debug probe instead.

> [!TIP]
> Once the servo board is flashed, you can wipe the Pico and reuse it as the master MicroPython controller — so you only need one Pico for the whole project.

### 1.1 Turn the Pico into a Programmer

1. Download `debugprobe_on_pico.uf2` from the [Raspberry Pi Debug Probe releases](https://github.com/raspberrypi/debugprobe/releases).
2. Hold the **BOOTSEL** button on the Pico while plugging it into USB.
3. Drag-and-drop the `.uf2` file onto the `RPI-RP2` drive that appears.
4. The Pico reboots as a **Picoprobe (CMSIS-DAP)** debugger.

### 1.2 Wire the Pico to the μDrive Board

Connect these **4 wires** from the Pico to the SWD programming header on the μDrive board:

| Pico Pin | μDrive Pin | Function |
|---|---|---|
| **3V3** | **3.3V** | Power to the target |
| **GND** | **GND** | Common ground |
| **GP2** | **SWCLK** (labeled **C**) | Serial Wire Clock |
| **GP3** | **SWDIO** (labeled **D**) | Serial Wire Data |

```
Raspberry Pi Pico (Picoprobe)            μDrive Board
┌───────────────────┐                    ┌──────────┐
│  3V3 (pin 36)     ├────────────────────┤ 3.3V     │
│  GND (pin 38)     ├────────────────────┤ GND      │
│  GP2 (pin 4)      ├────────────────────┤ C (SWCLK)│
│  GP3 (pin 5)      ├────────────────────┤ D (SWDIO)│
└───────────────────┘                    └──────────┘
```

### 1.3 Install the Flashing Tools

```bash
pip install pyocd
```

> [!WARNING]
> **Windows users:** If `pyocd` cannot detect your probe, Windows likely assigned the wrong default driver. Download the free [Zadig tool](https://zadig.akeo.ie/), select **"Picoprobe CMSIS-DAP"** from the dropdown, and replace the driver with **WinUSB**.

### 1.4 Open the Project and Flash

1. Clone the Microdrive repository (or open the project folder).
2. Open the `Microdrive` folder in **VS Code**.
3. PlatformIO will automatically detect the project (see `platformio.ini`).
4. Click the **Upload** button (the `→` arrow in the PlatformIO toolbar at the bottom of the screen).

PlatformIO compiles the firmware and invokes `pyocd` to flash the MM32G0001 automatically:

```
pyocd flash --pack "MindMotion.MM32G0001_DFP.1.0.1.pack" --target mm32g0001a1tc <firmware.bin>
```

> [!NOTE]
> The project uses a custom linker script (`custom.ld`) that sets RAM to 2 KB and Flash to 16 KB — the actual limits of the MM32G0001. The default STM32F030R8 board definition in PlatformIO assumes 8 KB of RAM, which would cause a Hard Fault on boot.

---

## Step 2 — Set Up the Master MCU

Once the servo board is flashed, it listens for commands over a half-duplex UART bus. You need a **master microcontroller** to send those commands.

### 2.1 Flash MicroPython onto the Pico

1. Download the latest MicroPython `.uf2` firmware for the Pico from [micropython.org](https://micropython.org/download/RPI_PICO/).
2. Hold **BOOTSEL**, plug in the Pico, and drag-and-drop the `.uf2` file.
3. The Pico reboots as a MicroPython device.

### 2.2 Copy the Driver

Copy `micropython/microdrive.py` from this repository onto the Pico's filesystem (using Thonny, `mpremote`, or `ampy`).

### 2.3 Wire the Servo Bus

The servo firmware uses **half-duplex single-wire UART** on PA12 (open-drain) at **250,000 baud, 8N1**.

#### Minimal Single-Wire Wiring

On boards that do not natively support open-drain half-duplex UART on a single pin (like the Raspberry Pi Pico / RP2040), connect the RX pin directly to the servo data line, and connect the TX pin to the RX pin/bus through a **1kΩ isolation resistor**. No external pull-up is needed since the μDrive PCB already has an onboard 10kΩ pull-up on the data bus.

```
MicroPython MCU (Pico)                 μDrive Servo Board
┌──────────────────────┐               ┌──────────────────┐
│  GP4 (TX) ──[1kΩ]────┐               │                  │
│                      │               │                  │
│  GP5 (RX) ───────────┴───────────────┤ Data Bus (PA12)  │
│  GND  ───────────────────────────────┤ GND              │
└──────────────────────┘               └──────────────────┘
                                        External PSU V+ ──→ Servo V+
                                        External PSU GND ──→ Servo GND (tied to Pico GND)
```

> [!IMPORTANT]
> - A **1kΩ isolation resistor** is required between the TX pin (GP4) and the RX/Data Line.
> - The μDrive PCB already has an onboard **10kΩ pull-up resistor** on the Data Bus, so no external pull-up is required.
> - Ensure a **common ground** exists between the external power supply, the Pico, and the μDrive board.


### 2.4 Basic Usage Example

```python
from machine import UART, Pin
from microdrive import ServoBus

# Initialize UART at 250000 baud
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus  = ServoBus(uart)

# Get a handle to the servo at ID 0 (factory default)
servo = bus.servo(0)

# Move to 90 degrees
servo.move(90)

# Check status
status = servo.poll()
if status:
    print(f"Angle: {status.angle}°")
    print(f"Current: {status.current_ma} mA")
    print(f"Moving: {status.is_moving}")
```

### 2.5 Scan the Bus

Discover all connected servos:

```python
found = bus.scan(id_range=range(0, 128))
for sid, status in found:
    print(f"Servo {sid}: {status.angle}°, {status.current_ma} mA")
```

> [!NOTE]
> Scanning is slow — each non-responding ID waits for the full reply timeout (default 5 ms). Narrow the `id_range` if you know which IDs to expect.

---

## Step 3 — Launch the WebGUI (Optional)

The project includes a **Svelte-based web dashboard** that connects to your servo network through the browser's Web Serial API.


```

### 3.1 Run the Serial Proxy

The master Pico must run the serial bridge script that translates JSON commands from the browser into servo bus packets:

1. Copy both `microdrive.py` **and** `serial_proxy.py` onto the Pico.
2. The proxy starts automatically on boot (or run it from the REPL).
3. Connect the Pico to your PC via USB.

### 3.2 Start the Web Dev Server

```bash
cd gui/
npm install
npm run dev
```

### 3.3 Connect from the Browser

1. Open the provided `localhost` link in **Chrome** or **Edge** (must support Web Serial API).
2. Click the connect button and select the Pico's serial port.
3. You can now scan, move, tune PID, and configure servos directly from the dashboard.

> [!WARNING]
> The Web Serial API is **not** supported in Firefox or Safari. Use Chrome or Edge.

---

## ⚡ Important Notes

| Topic | Detail |
|---|---|
| **Baud rate** | The servo bus runs at **250,000 baud**, 8N1 |
| **Default servo ID** | Factory-fresh servos start at **ID 0** |
| **Safety feature** | The motor does **not** start moving until the first `CONTROL` command is received — the H-bridge stays off until then |
| **Bus wire mode** | The UART uses **PA12 in open-drain mode** for bus sharing; a pull-up resistor is mandatory |
| **Motor power** | Always use an **external power supply** for the motor — never power it from the microcontroller's USB rail |
| **Reply timeout** | Default is **5 ms** — the servo firmware replies in ~2.7 ms on average |

---

## 🔗 Next Steps

- Read the [API Reference](api-reference.md) for the full MicroPython driver documentation.
- Run `micropython/calibrate_pid.py` to auto-tune PID gains for your motor.
- Run `micropython/hard_angle_set.py` to calibrate the potentiometer's physical limits.
- Check the [Troubleshooting Log](../docs/troubleshoot.md) if the chip won't flash or respond.
