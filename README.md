# μDrive (MicroDrive)

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Hardware License](https://img.shields.io/badge/Hardware_License-CERN--OHL--P--V2-blue)

**μDrive** is an open-source hardware and software project designed to convert any standard "dumb" DC motor into a smart, closed-loop servo motor. By retrofitting a standard DC motor with an analog potentiometer or an I2C magnetic encoder, μDrive grants you precise control over position, velocity, and current.

---

## ✨ Features

* **Universal DC Motor Support:** Works with standard DC brushed motors (within the limits of the onboard motor driver).
* **Closed-Loop Control:** PID-based control over Motor Position, Velocity, and Current.
* **Single-Wire Communication:** Network multiple servos together using a half-duplex, single-wire UART interface.
* **Web-Based Dashboard:** Includes a Svelte-based WebGUI utilizing the Web Serial API. Connect a master microcontroller to your PC via USB, and monitor/tune your servo network directly from your browser.
* **High-Level API:** Control motors using high-level commands without worrying about register-level or bit-level operations.

---

## 🛠️ Hardware Specifications

* **Microcontroller:** MindMotion MM32G0001 (32-bit Cortex-M0)
* **Motor Driver:** BDR6121H (Up to 7.5V operating voltage, 1.55A continuous / 3A peak)
* **Power:** The onboard 3.3V logic regulator can handle inputs up to 24V. *(Note: Always verify your specific motor driver's voltage limits before applying main motor power).*
* **Feedback Inputs:**
  * **Analog:** Standard potentiometer support (shared with the SDA pin).
  * **Digital (I2C):** 4-pad footprint (3.3v, SCL, SDA, GND) for external I2C magnetic encoders like the AS5600 *(Hardware ready, software implementation planned).*

---

## 💻 Software & APIs

The project uses a Master/Slave architecture over a half-duplex UART bus. You simply import the driver library onto your master microcontroller and send high-level commands.

* **MicroPython:** A fully functioning driver library is currently available.
* **Arduino/C++:** *Coming soon!*

### WebGUI Architecture
```text
[ Web Browser (Svelte WebGUI) ] 
       | (Web Serial API)
       v
[ Master Microcontroller (Running Python script) ]
       | (Single-Wire UART)
       v
[ μDrive Servo Board ] -> [ DC Motor + Encoder ]
```

---

## 🚀 Getting Started

### 1. Flashing the Servo Board (via Picoprobe)

> *Why use a Raspberry Pi Pico?*
> Programming obscure chips like the MM32G0001 usually requires buying dedicated, expensive hardware programmers (like mm32link or ST-Link). By using a $4 Raspberry Pi Pico instead, we keep the project incredibly cheap and accessible. Even better: once you've flashed the servo board, you can wipe the Pico and reuse it as the master MicroPython controller for your entire servo network!

**Step 1: Turn the Pico into a Programmer**
Flash your Raspberry Pi Pico with the **Picoprobe** (Debug Probe) firmware to turn it into a CMSIS-DAP debugger. You can download the latest `debugprobe_on_pico.uf2` file directly from the [official Raspberry Pi GitHub Releases page](https://github.com/raspberrypi/debugprobe/releases). Just hold the BOOTSEL button, plug in the Pico, and drag-and-drop the file!

**Step 2: Wire the Pico to the μDrive Board**
Connect these 4 wires from the Pico to the programming header on the μDrive board:
* **Pico 3V3**  -->  **μDrive 3.3V**
* **Pico GND**  -->  **μDrive GND**
* **Pico GP2**  -->  **μDrive SWCLK** (Labeled **C** on the board)
* **Pico GP3**  -->  **μDrive SWDIO** (Labeled **D** on the board)

**Step 3: Install the Software Tools**
1. Install **VS Code** and add the **PlatformIO** extension.
2. Install **Python** on your PC.
3. Open a terminal and install the flashing tool by running: `pip install pyocd`

**Step 4: Open and Flash!**
1. Clone this repository and open the `MicroDrive` folder in VS Code.
2. Click the PlatformIO **Upload** button (the small `→` arrow at the bottom of the screen). PlatformIO will automatically compile the code and trigger `pyocd` to flash it onto the MM32G0001!

### 2. Setting Up the Master MCU (Drivers)
Once the servo board is flashed, it listens for commands over a half-duplex UART line. You will need a "Master" microcontroller to send these commands.
* Currently, a **MicroPython** driver is provided. You can flash a standard Raspberry Pi Pico with MicroPython, import the provided driver library, and use simple high-level functions to command the servo.
* *(Arduino/C++ library support is coming soon!)*

### 3. Launching the Web GUI
To easily tune and monitor your servo network from your computer, you can run the provided Svelte WebGUI:
1. Ensure your Master MCU is connected to your PC via USB and running the serial bridge python script.
2. Open a terminal and navigate to the `gui` folder inside this repository.
3. Run `npm install` to download the web dependencies.
4. Run `npm run dev` to start the local server.
5. Open the provided `localhost` link in a browser that supports the Web Serial API (like Chrome or Edge) to connect to your Master MCU and start tuning!

---

## 🚧 Known Issues & Roadmap

MicroDrive is actively under development. Current focus areas include:

* **🐛 EMI Stability:** The board occasionally stops responding to commands during massive current spikes. This is likely due to electromagnetic interference (EMI) crashing the MCU or bus. Hardware/software filtering improvements are being investigated.
* **🚀 Better I2C Encoder Support:** Writing the software drivers to fully utilize the AS5600 footprint.
* **⚙️ Control Optimization:** Improving the efficiency of the communication protocol and fine-tuning the torque and velocity control loops.

---

## ⚖️ License

This project is fully open-source:
* The **Software/Firmware** is licensed under the [MIT License](LICENSE).
* The **Hardware (PCBs/Schematics)** is licensed under the [CERN-OHL-P v2](LICENSE-HARDWARE.txt).

You are free to build, modify, and integrate μDrive into your own projects (commercial or hobbyist).
