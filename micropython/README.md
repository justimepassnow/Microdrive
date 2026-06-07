# Smart Servo — MicroPython Driver

A lightweight MicroPython library for controlling Smart Servos running the MM32 firmware over a half-duplex single-wire UART bus.

## Features

- **Full protocol coverage** — CONTROL, CONFIG, POLL_STATUS, CLEAR_ERROR
- **Half-duplex aware** — built-in TX/RX direction switching with optional GPIO pin
- **Daisy-chain ready** — address servos individually or broadcast to all at once
- **Blocking helpers** — `move_and_wait()` blocks until the servo reaches its target
- **Bus scanner** — discover connected servo IDs
- **Granular or bulk config** — update a single setting or many in one packet
- **Zero dependencies** — only `machine`, `struct`, and `time` (standard MicroPython)

## Wiring

The servo firmware uses **half-duplex single-wire UART** on PA12 (open-drain) at **250000 baud, 8N1**.

### Minimal (Single-Wire, No Transceiver)

```
MicroPython MCU                    Smart Servo
┌──────────┐                       ┌──────────┐
│       TX ├───────────────────────┤ Data Bus │
│          │        1k–10kΩ        │          │
│      3V3 ├───────┤ PULL-UP ├─────┤          │
│      GND ├───────────────────────┤ GND      │
└──────────┘                       └──────────┘
```

> **Tip:** Configure the UART TX pin as **open-drain** if your MCU supports it (e.g., ESP32's `UART(1, tx=Pin(4), ... )` with an external pull-up).

### With RS-485 Transceiver

```
MCU TX  → DI
MCU RX  → RO
MCU GPx → DE+RE  (dir_pin — HIGH to transmit, LOW to receive)
```

## Quick Start

```python
from machine import UART, Pin
from smart_servo import ServoBus

# Create bus (adjust pins for your board)
uart = UART(1, baudrate=250000, tx=Pin(4))
bus  = ServoBus(uart)

# Get a handle to servo at ID 0 (factory default)
servo = bus.servo(0)

# Move to 180 degrees
status = servo.move(180)
print(status)  # <ServoStatus angle=180° current=42mA>

# Poll current state
status = servo.poll()
print(status.angle, status.current_ma, status.is_moving)
```

## API Reference

### `ServoBus(uart, dir_pin=None, reply_timeout_ms=50)`

Manages the shared UART bus.

| Method | Description |
|---|---|
| `servo(id)` | Returns a `Servo` handle for the given ID |
| `broadcast_move(angle, velocity=0)` | Move all servos (no reply) |
| `broadcast_clear_error()` | Clear faults on all servos (no reply) |
| `scan(id_range=range(0,254))` | Scan for connected servos, returns list of `(id, ServoStatus)` |

### `Servo` (returned by `bus.servo(id)`)

#### Movement

| Method | Description |
|---|---|
| `move(angle, velocity=0)` | Send move command. `velocity=0` uses flash default. Returns `ServoStatus` |
| `move_and_wait(angle, velocity=0, timeout_ms=10000)` | Blocking move — returns final `ServoStatus` or `None` on timeout |
| `wait_until_done(timeout_ms=10000, poll_interval_ms=50)` | Block until servo reports idle |
| `is_moving()` | Returns `True` if the servo is currently in motion |

#### Status & Error

| Method | Description |
|---|---|
| `poll()` | Request current status. Returns `ServoStatus` |
| `clear_error()` | Clear overcurrent/stall faults and reset PID state |

#### Configuration (Individual)

| Method | Description |
|---|---|
| `set_id(new_id, direction_invert=False)` | Change bus address (0–127) and motor direction |
| `set_angle_limits(min_angle, max_angle)` | Set software angle limits |
| `set_velocity(max_velocity)` | Set flash-default velocity (deg/s) |
| `set_current_limit(current_limit)` | Set over-current threshold (mA) |
| `set_pid(kp, ki, kd)` | Set PID gains (float → Q16 conversion handled automatically) |
| `set_hard_calibration(hard_min=0, hard_max=300)` | Set potentiometer-to-angle mapping |

#### Configuration (Bulk)

```python
servo.configure(
    servo_id=5,
    direction_invert=False,
    min_angle=45,
    max_angle=280,
    max_velocity=180,
    current_limit=1000,
    kp=100.0, ki=0.05, kd=8.0,
    hard_min=0, hard_max=300,
)
```

Only non-`None` fields are written; others are left untouched on the servo.

### `ServoStatus`

Returned by `move()`, `poll()`, `clear_error()`, and `configure()`.

| Property | Type | Description |
|---|---|---|
| `angle` | int | Current physical angle (degrees) |
| `current_ma` | int | Motor current draw (milliamps) |
| `is_moving` | bool | Servo is actively tracking a target |
| `overcurrent` | bool | Over-current fault flag |
| `stall` | bool | Stall detection fault flag |
| `has_fault` | bool | `True` if any fault is active |
| `servo_id` | int | ID of the servo that replied |
| `instruction` | int | Echoed instruction byte |

## Protocol Reference

See [`../byteorder.md`](../byteorder.md) for the full byte-level packet specification.

## Tested Boards

The library uses only standard MicroPython APIs and should work on any board with a UART peripheral:

- ESP32 / ESP32-S3
- Raspberry Pi Pico (RP2040)
- STM32 (Pyboard)
- ESP8266

## License

Same license as the parent project.
