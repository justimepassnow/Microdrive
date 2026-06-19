# 🛠️ Troubleshooting Guide

Common problems and their fixes when working with μDrive.

---

## 1. Flashing & Programming

### pyocd can't find the probe

```
No USB probes found
```

**Fix (Windows):** Windows assigns the wrong driver by default. Use [Zadig](https://zadig.akeo.ie/):

1. Options → List All Devices
2. Select **Picoprobe CMSIS-DAP**
3. Replace driver with **WinUSB**
4. Re-run `pyocd list` — the probe should now appear

If the probe still doesn't show, re-flash Picoprobe firmware: hold `BOOTSEL`, plug in the Pico, drag-and-drop `debugprobe_on_pico.uf2`.

---

### pyocd finds probe but can't connect to MM32G0001

```
Target connection failed: CMSIS-DAP transfer timed out
```

**Check wiring** — the two SWD wires get swapped constantly:

| Pico Pin | μDrive Pad | Function |
|---|---|---|
| GP2 | **C** | SWCLK |
| GP3 | **D** | SWDIO |
| GND | GND | Ground |
| 3V3 | 3.3V | Power |

Also:
- Measure the **3.3V** test pad on the μDrive board. Should read `3.15V – 3.45V`. If it's 0V, the LDO may be dead or no power is reaching the board.
- Keep SWD wires **short** (under 15 cm). Long dupont wires cause signal integrity issues. If you must use long wires, slow down the clock:
  ```
  pyocd flash -f 500000 --pack "MindMotion.MM32G0001_DFP.1.0.1.pack" --target mm32g0001a1tc firmware.bin
  ```

---

## 2. Chip Boots but Nothing Happens

### Firmware flashes fine but MCU is completely dead

This is almost always the **linker script** problem. The project borrows PlatformIO's `disco_f030r8` board definition (STM32F030R8), which assumes **8 KB RAM**. The MM32G0001 only has **2 KB**.

What happens: the startup code sets the initial stack pointer to `0x20002000` (top of 8K). The MM32's physical RAM ends at `0x20000800`. First stack write hits non-existent memory → instant Hard Fault before `main()` even runs.

**Fix:** Make sure `platformio.ini` points to the custom linker script:

```ini
board_build.ldscript = custom.ld
```

Verify `custom.ld` has the correct memory sizes:

```ld
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 16K
  RAM (xrw)   : ORIGIN = 0x20000000, LENGTH = 2K
}
```

You can double-check the compiled binary:

```bash
arm-none-eabi-readelf -s .pio/build/disco_f030r8/firmware.elf | grep _estack
```

`_estack` must be `0x20000800`, **not** `0x20002000`.

---

## 3. UART / Serial Communication

### Getting garbage bytes or continuous 0x00 (NUL) on serial monitor

Two common causes:

**1. Wrong pin.** On the TSSOP-20 package, USART1 TX/RX is on **PA12 = Pin 17**. It's easy to accidentally wire to the wrong physical pin. Double-check against the [pinout diagram](../mm32g0001ait_pinout.png).

**2. Baud rate divisor miscalculation.** The USART BRR register expects the divisor to include the 16× oversampling factor:

```
USARTDIV = SystemClock / (BaudRate × 16)
```

If you forget to divide by 16, the actual baud rate will be 16× slower than expected. At 9600 target, you'd actually get ~600 baud — the receiver sees nothing but framing errors and NUL bytes.

For the production firmware (48 MHz clock, 250000 baud), the HAL handles this automatically via `USART_Init()`. If you're doing manual register config, the divisor is:

```
48000000 / (250000 × 16) = 12
```

---

### Master sends commands but gets no replies

**Check the isolation resistor.** The bus is half-duplex on a single wire. The Master's TX pin needs a **1 kΩ resistor** in series before joining the shared data line, otherwise TX drives the bus and blocks the servo's replies.

```
Pico GP4 (TX) ──[1kΩ]──┐
                        ├──── μDrive PA12 (Data Bus)
Pico GP5 (RX) ──────────┘
```

**Check common ground.** The MCU GND and the μDrive board GND must be directly connected. Floating ground = the receiver can't distinguish high from low.

**Check servo ID.** Factory default ID is `0`. If your code is sending to ID `1`, the servo silently ignores it. Test with a broadcast:

```python
servo = bus.servo(0)   # make sure this matches actual ID
status = servo.poll()  # should return a ServoStatus object
```

If you're unsure what ID is stored in flash, use READ_CONFIG (`0x05`) with broadcast ID `0xFE` — but note that broadcast packets don't generate replies. You'll need to address at least one known ID, or re-flash the firmware to reset config to defaults.

**Check baud rate.** The firmware runs at **250000** baud, not 9600 or 115200. Make sure your master UART matches:

```python
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
```

---

### Reply timeout (5ms default) is too aggressive

The `_REPLY_TIMEOUT_MS` in `microdrive.py` is set to 5 ms. The servo firmware deliberately delays its reply by 2 ms (`reply_trigger_time_ms = millis() + 2`) to avoid bus collisions. On slower master MCUs or with bus capacitance, 5 ms may be tight.

If you're getting intermittent `None` returns from `poll()`, try increasing the timeout:

```python
bus = ServoBus(uart, dir_pin=Pin(4, Pin.OUT), timeout_ms=10)
```

---

## 4. Motor Control

### Motor spins full speed in one direction and won't stop (runaway)

This is **positive feedback** — the PID loop is pushing the motor the wrong way, which increases the error, which pushes harder. The motor will spin until overcurrent protection trips (2000 mA sustained for 50 ms).

**Fix — toggle direction:** Either swap the two motor wires physically, or set the `direction_invert` flag in software:

```python
servo.configure(direction_invert=True)
```

If the motor doesn't have a potentiometer connected (or it's disconnected), the ADC reads a floating/random value and the PID has no valid feedback — same runaway symptom. Verify the pot wiper is connected to the **SDA** test pad.

---

### Motor vibrates/oscillates instead of holding position

The PID gains are too aggressive for your motor and gearbox combination.

**Quick fix — conservative gains:**

```python
servo.configure(kp=1.0, ki=0.0, kd=0.0)
```

Then tune up:
1. Increase `kp` until the motor just barely starts to oscillate on a step input
2. Add `kd` to damp the oscillation
3. Only add `ki` if there's persistent steady-state error (motor stops a few degrees short of target). Keep it very small — large `ki` causes integral windup

The firmware defaults are `kp=100.0`, `ki=0.05`, `kd=8.0` — these were tuned for a specific MG996R motor and may be wildly wrong for your setup.

---

### Motor doesn't move at all after sending CONTROL packets

The motor is **not armed** until the first valid CONTROL packet arrives. But if there's an active overcurrent fault, CONTROL packets are silently ignored.

Check for faults:

```python
status = servo.poll()
print(status)  # look for OVERCURRENT flag
```

If overcurrent is active, clear it first:

```python
servo.clear_error()
servo.move(90)  # now this will work
```

The overcurrent fault triggers when current exceeds **2000 mA** for **50 consecutive milliseconds**. This is a hard safety limit defined by `HARD_OCP_LIMIT_MA` in the firmware. Common triggers: stalled motor, mechanical binding, or a short in the motor wiring.

---

### Motor overshoots badly, then slowly creeps to position

High overshoot with slow settling = `kp` too high and `kd` too low. The proportional term drives the motor past the target, and there isn't enough derivative damping to slow it down as it approaches.

Also check the **velocity profile**. The firmware uses a "ghost target" trajectory ramp — the internal target moves toward the commanded angle at `active_velocity` deg/s. If velocity is set very high (or 0, which means instant), the PID sees a huge instantaneous step and overshoots.

```python
# Move with a gentle velocity ramp
servo.move(180, velocity=90)  # 90 deg/s instead of instant
```

---

## 5. Power & EMI

### MCU crashes or resets when motor starts / stalls / reverses

This is the most common hardware issue. DC motors generate massive current spikes and back-EMF when starting, stalling, or changing direction. This can:

1. **Sag the power rail** below the LDO's dropout voltage → MCU brown-out resets
2. **Inject noise** into the UART or SWD lines → corrupted packets or MCU lockup

**Fixes:**
- **Never** power the motor from USB or the Pico's 3.3V/5V pins. Always use a separate external supply rated for the motor's stall current.
- Add a **100μF – 470μF electrolytic cap** across the motor power input (V+ and GND on the μDrive board), as close to the board as possible.
- Solder a **100nF ceramic cap** directly across the motor terminals to suppress brush arcing.
- Verify that bypass caps C2 and C3 (100nF) are populated near the MCU.

**Diagnosis:** Probe the 3.3V test pad with a scope while stalling the motor. If the 3.3V rail dips below ~2.7V, the MCU is brown-out resetting.

---

### Current readings are wrong or always zero

The current sensor (INA180A2 + 0.01Ω shunt on PA2) is calibrated at boot via `calibrate_current_sensor()`. It takes 16 ADC samples with the motor idle to establish a zero-current baseline.

If you're seeing wrong readings:
- Make sure the motor is **not running** during the first ~20ms after power-on (the calibration window)
- If R1 (the 0.01Ω sense resistor) is not populated or cracked, current will always read 0
- The calibration slope (`1.465 mA/count`) was derived from a specific dummy-load bench test. Your board's component tolerances may differ — if readings are consistently off by a fixed percentage, the slope factor in `update_current_ma()` may need adjustment

---

## 6. Potentiometer / Angle Feedback

### Reported angle is wrong or jumping around

**Check `zero_adc` and `adc_per_360` calibration.** These two config values map the raw 12-bit ADC reading to degrees:

- `zero_adc`: the raw ADC value when the shaft is at your defined 0° position
- `adc_per_360`: how many ADC counts correspond to a full 360° rotation

If these are wrong, the angle will be offset or scaled incorrectly. Use the calibration script:

```bash
# On the Pico running MicroPython
import microdrive
# Follow the manual_angle_calibrate.py procedure
```

**Noisy readings** (angle jumping ±2-3° at rest) usually mean:
- Worn potentiometer with a dead spot
- Poor connection at the pot wiper (intermittent contact on the SDA pad)
- Missing decoupling cap near the ADC input

The firmware applies a low-pass EMA filter (`alpha = 0.10`) on the ADC signal, which helps with normal noise. If readings are still jumpy, the pot may need replacement.

---

### Angle reads 0 or max constantly regardless of shaft position

The pot wiper is probably disconnected. Measure continuity from the potentiometer center pin to the **SDA** test pad. Also check that the pot end-pins are connected to **3.3V** and **GND** — if one is floating, the voltage divider doesn't work.

---

## 7. Flash / Configuration

### Config changes don't persist after power cycle

When sending a CONFIG packet, **bit 6** of the `update_mask` controls persistence:
- Bit 6 **clear** (default) → config is written to flash page 15 (`0x08003C00`)
- Bit 6 **set** → config is RAM-only (volatile, lost on reboot)

If you're using the MicroPython driver:

```python
servo.configure(kp=50.0)              # persisted to flash (default)
servo.configure(kp=50.0, volatile=True)  # RAM only, lost on reboot
```

If config *still* doesn't persist, the flash page may be corrupted. Re-flashing the firmware erases everything and resets to defaults.

---

### Want to factory-reset all config values

Re-flash the firmware. The `flash_load_config()` function checks for a `0xDEADBEEF` magic word at `0x08003C00`. If it's missing (erased flash = all `0xFF`), it writes factory defaults:

| Parameter | Default |
|---|---|
| servo_id | 0 |
| direction_invert | 0 (normal) |
| min_angle | 0° |
| max_angle | 180° |
| max_velocity | 180 deg/s |
| current_limit | 1000 mA |
| kp | 100.0 |
| ki | 0.05 |
| kd | 8.0 |
| zero_adc | 0 |
| adc_per_360 | 6600 |

---

## 8. Multi-Servo Bus

### Multiple servos on the same bus cause garbled replies

If two servos have the **same ID**, both will try to reply simultaneously, corrupting each other's packets. Every servo on the bus must have a unique ID (0–127).

To fix, disconnect all servos except one, assign it a unique ID, reconnect, and repeat:

```python
servo = bus.servo(0)  # connect to one servo at a time
servo.configure(servo_id=1)  # assign new ID
# power cycle the servo, now address it as ID 1
```

### CONTROL packets don't generate replies (by design)

This is intentional. The `0x01 CONTROL` instruction does **not** send a status reply — this was done to maximize control loop throughput on the bus. Use `0x03 POLL` to explicitly request status after sending movement commands.

---

## Quick Reference: Test Points

Use a multimeter to check these pads on the μDrive board:

| Pad | Expected | If Wrong |
|---|---|---|
| **3.3V** | 3.3V ± 5% | LDO dead or no input power |
| **GND** | 0V reference | — |
| **SDA** | 0.1V – 3.2V (varies with shaft angle) | Pot disconnected or dead |
| **PA12 bus** | 3.3V when idle | Stuck low = short or TX driver issue |
| **+VE / -VE** | Motor supply voltage | No motor power |
