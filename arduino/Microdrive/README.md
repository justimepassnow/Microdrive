# Microdrive Arduino Library

Arduino/ESP32 driver for **Microdrive** smart servos (MM32 firmware). Communicates over a half-duplex single-wire UART bus at 250000 baud — protocol-identical to the MicroPython `microdrive.py` driver.

## Features

- **Full protocol support** — CONTROL, CONFIG, POLL, CLEAR_ERROR, READ_CONFIG
- **Daisy-chain** — address up to 128 servos on a single bus
- **Bus scanning** — discover connected servos automatically
- **Configuration** — PID tuning, angle limits, velocity, current limits, calibration
- **RAM-only mode** — tune PID gains without wearing flash
- **No firmware changes** — drop-in compatible with existing MM32 firmware
- **Cross-platform** — Arduino AVR, ESP32, RP2040, STM32, and more

## Quick Start

### Wiring (ESP32)

| ESP32 Pin | Microdrive Bus |
|-----------|----------------|
| GPIO 16   | Data (TX)      |
| GPIO 17   | Data (RX)      |
| 5V        | VCC            |
| GND       | GND            |

For single-wire mode, connect both TX and RX to the same data line.

### Code

```cpp
#include <Microdrive.h>

HardwareSerial servoSerial(1);
ServoBus bus(servoSerial);

void setup() {
    servoSerial.begin(250000, SERIAL_8N1, 17, 16);

    Servo servo = bus.servo(0);
    servo.move(180, 200);     // Move to 180° at 200 deg/s
}

void loop() { }
```

## Installation

### Arduino IDE (Manual)
1. Copy the `Microdrive/` folder into your Arduino `libraries/` directory
2. Restart the Arduino IDE
3. Go to **Sketch → Include Library → Microdrive**

### PlatformIO
Add to your `platformio.ini`:
```ini
lib_deps =
    Microdrive
```
Or symlink/copy the library into your project's `lib/` folder.

## API Reference

### ServoBus

```cpp
ServoBus(Stream& serial, int8_t dirPin = -1, uint8_t replyTimeoutMs = 8);
```

| Method | Description |
|--------|-------------|
| `servo(id)` | Create a `Servo` handle for the given bus address |
| `broadcastMove(angle, velocity, current)` | Move all servos simultaneously |
| `broadcastClearError()` | Clear faults on all servos |
| `broadcastDisarm()` | Disarm all servos (shafts spin free) |
| `scan(results, maxResults, startId, endId)` | Scan for connected servos, returns count |

### Servo

```cpp
Servo servo = bus.servo(0);  // Lightweight handle, no heap allocation
```

**Motion Control:**

| Method | Description |
|--------|-------------|
| `move(angle, velocity, current)` | Fire-and-forget move command |
| `poll(status)` | Read current status (angle, current, flags) |
| `clearError()` | Clear fault, reset PID, lock to current position |
| `disarm()` | Turn off motor so shaft spins freely |
| `isMoving()` | Poll and return true if still moving |
| `waitUntilDone(timeout, interval)` | Block until motion complete |
| `moveAndWait(angle, velocity, timeout)` | Move and block |

**Configuration:**

| Method | Description |
|--------|-------------|
| `readConfig(config)` | Read full flash configuration |
| `setId(newId, dirInvert)` | Change bus address / motor direction |
| `setAngleLimits(min, max)` | Set software angle limits |
| `setVelocity(maxVel)` | Set default velocity (deg/s) |
| `setCurrentLimit(limit)` | Set overcurrent threshold (mA) |
| `setPid(kp, ki, kd, ramOnly)` | Set PID gains (float → Q16 internally) |
| `setCalibration(zeroAdc, adcPer360)` | Set physical ADC calibration |
| `configure(...)` | Update multiple fields in one packet |

### ServoStatus

| Field | Type | Description |
|-------|------|-------------|
| `servo_id` | `uint8_t` | Bus address |
| `angle` | `int16_t` | Current angle in degrees |
| `current_ma` | `uint16_t` | Current draw in mA |
| `is_moving` | `bool` | Actively moving toward target |
| `overcurrent` | `bool` | Overcurrent fault active |
| `is_holding` | `bool` | In admittance/yield mode |
| `hasFault()` | `bool` | True if any fault is active |

### ServoConfigData

| Field | Type | Description |
|-------|------|-------------|
| `servo_id` | `uint8_t` | Bus address (0-127) |
| `direction_invert` | `bool` | Motor direction inverted |
| `min_angle` / `max_angle` | `uint16_t` | Angle limits (degrees) |
| `max_velocity` | `uint16_t` | Default velocity (deg/s) |
| `current_limit` | `uint16_t` | Overcurrent threshold (mA) |
| `kp` / `ki` / `kd` | `float` | PID gains |
| `zero_adc` | `int16_t` | ADC value at 0° |
| `adc_per_360` | `int16_t` | ADC ticks per 360° |
| `magic` | `uint32_t` | Flash magic (0xDEADBEEF) |

## Examples

- **[BasicMove](examples/BasicMove/BasicMove.ino)** — Move a servo back and forth with polling
- **[ScanBus](examples/ScanBus/ScanBus.ino)** — Discover all connected servos
- **[ConfigServo](examples/ConfigServo/ConfigServo.ino)** — Read/write servo configuration

## Half-Duplex Wiring Notes

The Microdrive bus uses a **single-wire half-duplex UART** at 250000 baud. There are two wiring approaches:

1. **Single-wire (no direction pin):** Connect the servo data line to both TX and RX of your UART. The driver automatically drains TX echo bytes before reading replies. Set `dirPin = -1`.

2. **Direction pin (RS-485 style):** Use a separate GPIO to control an external transceiver's direction. The pin goes HIGH during transmit and LOW during receive.

## Protocol Compatibility

This driver uses the exact same binary protocol as the MicroPython `microdrive.py` driver:
- `0xFF 0xFF` packet header
- Inverted-sum checksum
- Little-endian parameter encoding
- Q16 fixed-point PID gains
- CONFIG bitmask for selective field updates

**No MM32 firmware changes are required.**

## License

See the project [LICENSE](../../LICENSE) file.
