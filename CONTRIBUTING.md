# Contributing to μDrive

Thanks for your interest in contributing to μDrive! This project spans hardware, firmware, software, and documentation — there's room for everyone.

## 📋 Before You Start

1. **[Check existing issues](https://github.com/justimepassnow/Microdrive/issues)** — Someone may already be working on what you have in mind.
2. **Open an issue first** for any non-trivial change so we can discuss the approach before you invest time.
3. **Read the [docs](docs/)** — Familiarize yourself with the hardware and firmware architecture.

## 🔧 Project Structure

```
Microdrive/
├── src/              # Firmware (C, bare-metal on MM32G0001)
├── include/          # Firmware headers
├── micropython/      # MicroPython driver library & utilities
├── gui/              # Svelte WebGUI (Web Serial dashboard)
├── PCB/              # KiCad PCB designs (both board variants)
├── docs/             # Documentation
├── platformio.ini    # PlatformIO build config
└── custom.ld         # Linker script for MM32G0001
```

## 🚀 Getting Set Up

### Firmware
1. Install [VS Code](https://code.visualstudio.com/) + [PlatformIO](https://platformio.org/) extension.
2. Install [pyocd](https://pyocd.io/): `pip install pyocd`
3. Open the root `Microdrive/` folder in VS Code.
4. See the [Getting Started](docs/getting-started.md) guide for flashing instructions.

### MicroPython Driver
1. Flash a Raspberry Pi Pico with [MicroPython](https://micropython.org/download/RPI_PICO/).
2. Copy required scripts from `micropython/` onto the Pico.

### WebGUI
1. `cd gui`
2. `npm install`
3. `npm run dev`

### Hardware (PCBs)
- PCB files are in [KiCad](https://www.kicad.org/) format under `PCB/`.

## 📝 How to Contribute

### Reporting Bugs
- Use the **Bug Report** issue template.
- Include steps to reproduce, expected vs actual behavior, and your setup details (board variant, power supply, motor, etc.).

### Suggesting Features
- Use the **Feature Request** issue template.
- Describe the problem you're trying to solve, not just the solution.

### Submitting Code Changes

1. **Fork** the repository.
2. **Create a branch** from `main`: `git checkout -b your-branch-name`
3. **Make your changes** — keep commits focused and atomic.
4. **Test your changes:**
   - Firmware: Verify on actual hardware if possible.
   - MicroPython: Test with a real servo board + motor.
   - WebGUI: Test in Chrome/Edge (Web Serial API required).
5. **Push** and open a **Pull Request** against `main`.

### Hardware Contributions
- For PCB changes, include screenshots of the schematic/layout diff.
- Note any BOM changes.
- If possible, test with a fabricated board before submitting.

## 🎨 Style Guidelines

### Firmware (C)
- Use descriptive variable/function names.
- Comment non-obvious logic, especially register-level operations.
- Keep the MM32G0001's constraints in mind: 16KB Flash, 2KB RAM.

### MicroPython
- Follow standard Python conventions (PEP 8 where practical).
- Keep the driver API simple and high-level.

### WebGUI (Svelte)
- Keep components focused and reusable.
- Test with the Web Serial API in a Chromium-based browser.

## ⚖️ Licensing

By contributing, you agree that your contributions will be licensed under:
- **MIT License** for software/firmware contributions.
- **CERN-OHL-P v2** for hardware contributions.

## 💬 Questions?

Open an issue — there are no dumb questions. We'd rather help you contribute than have you give up!
