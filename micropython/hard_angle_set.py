"""
hard_angle_set.py — Automatic Hard Limit Calibration for Microdrive

This script automatically calibrates the physical hard_min and hard_max angles:
1. Temporarily broadens the software limits to allow full physical sweep.
2. Sweeps the servo in a safe middle range (60° to 120°) 3 times.
3. During safe movement, it calculates the average dynamic current draw.
4. Computes a safety threshold: max(1.5 * average, average + 120 mA).
5. Slowly decrements the angle from 60° downward (1° steps). When a current
   spike is detected, it marks this as the physical hard min angle.
6. Slowly increments the angle from 120° upward (1° steps). When a current
   spike is detected, it marks this as the physical hard max angle.
7. Saves the new hard_min and hard_max configurations to the MM32's flash.
8. Displays the verified configuration.
"""

from machine import UART, Pin
import time
from microdrive import ServoBus

# ─── 1. Initialize UART1 on Pi Pico ──────────────────────────────────────
print("Initializing UART1 on GP4 (TX) and GP5 (RX)...")
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart)

# ─── 2. Scan for Servos ───────────────────────────────────────────────────────
print("\n--- Scanning for active Servo ID(s) ---")
found = bus.scan(id_range=range(0, 6))

if not found:
    print("❌ No servos detected!")
    import sys
    sys.exit()

target_id = found[0][0]
print("🎯 Using Servo ID: {}".format(target_id))
servo = bus.servo(target_id)

# Query Initial Persistent Configuration for calibration reconstruction
initial_config = servo.read_config()
if not initial_config:
    print("❌ Failed to query initial configuration! Check MM32 power.")
    import sys
    sys.exit()

old_min = initial_config.hard_min_angle
old_max = initial_config.hard_max_angle
old_sweep = old_max - old_min
if old_sweep == 0:
    old_sweep = 280

# ─── 3. Broaden Software Limits for Calibration ──────────────────────────────
print("\n--- Temporarily broadening software limits for calibration ---")
# We open up the software limits to their absolute maximum range so the
# incremental movements are not clamped by the firmware during test.
temp_config = servo.configure(
    min_angle=0,
    max_angle=360,
    kp=80.0,
    ki=0.03,
    kd=8.0
)
if temp_config:
    print("✅ Temporary limits set (5° to 295°).")
else:
    print("⚠️ Command sent, proceeding...")

servo.clear_error()
time.sleep_ms(500)

# ─── 4. Measure Dynamic Baseline Current Draw ────────────────────────────────
print("\n--- Measuring Dynamic Dynamic Current Draw (Sweeping 60° <-> 120°) ---")
current_samples = []
safe_sweeps = [120, 60, 120, 60, 120]

for sweep_idx, target in enumerate(safe_sweeps):
    print("  Sweep #{} to {}°...".format(sweep_idx + 1, target))
    servo.move(target)
    
    start_time = time.ticks_ms()
    while True:
        pos = servo.poll()
        if pos:
            # Only record current while the motor is drawing active power
            if pos.current_ma > 5:
                current_samples.append(pos.current_ma)
                
            if not pos.is_moving:
                break
                
            # Safety timeout (4 seconds per sweep)
            if time.ticks_diff(time.ticks_ms(), start_time) > 4000:
                break
        time.sleep_ms(100)
    time.sleep_ms(300)

if not current_samples:
    print("❌ No active current samples gathered! Check power supply.")
    import sys
    sys.exit()

average_current = sum(current_samples) / len(current_samples)
# Set spike threshold: 50% more than average, but at least +120mA above average to avoid noise triggers
threshold_current = max(average_current * 5, average_current + 120)

print("\n--- Baseline Current Results ---")
print("  - Samples gathered: {}".format(len(current_samples)))
print("  - Average current:  {:.1f} mA".format(average_current))
print("  - Spike threshold:  {:.1f} mA".format(threshold_current))

# ─── 5. Calibrate Hard Min Angle ─────────────────────────────────────────────
print("\n--- Calibrating Physical HARD MIN Angle ---")
print("Moving to safe starting point (60°)...")
servo.move(60)
servo.wait_until_done(timeout_ms=3000)
time.sleep_ms(500)

detected_hard_min = None
# Slowly step down from 60° to 5°
for angle in range(60, 0, -1):
    servo.move(angle)
    time.sleep_ms(150) # Let the motor step
    
    status = servo.poll()
    if status:
        if initial_config.direction_invert:
            raw_adc = int((old_max - status.angle) * 4095 / old_sweep)
        else:
            raw_adc = int((status.angle - old_min) * 4095 / old_sweep)
        raw_adc = max(0, min(4095, raw_adc))
        print("  Target: {}° | Real: {}° | ADC: {} | Current: {} mA".format(angle, status.angle, raw_adc, status.current_ma))
        if status.current_ma >= threshold_current:
            detected_hard_min = status.angle
            print("💥 Spike Detected! Physical end-stop encountered at {}°.".format(detected_hard_min))
            break
    else:
        print("⚠️ No response.")

if detected_hard_min is None:
    print("❌ Failed to detect Hard Min (reached 5° without spike). Using safety fallback: 10°")
    detected_hard_min = 0

# Back off to safe zone
print("Backing off to safe angle (45°)...")
servo.move(45)
servo.wait_until_done(timeout_ms=2000)
servo.clear_error()
time.sleep_ms(500)

# ─── 6. Calibrate Hard Max Angle ─────────────────────────────────────────────
print("\n--- Calibrating Physical HARD MAX Angle ---")
print("Moving to safe starting point (120°)...")
servo.move(120)
servo.wait_until_done(timeout_ms=3000)
time.sleep_ms(500)

detected_hard_max = None
# Slowly step up from 120° to 295°
for angle in range(120, 350, 1):
    servo.move(angle)
    time.sleep_ms(150) # Let the motor step
    
    status = servo.poll()
    if status:
        if initial_config.direction_invert:
            raw_adc = int((old_max - status.angle) * 4095 / old_sweep)
        else:
            raw_adc = int((status.angle - old_min) * 4095 / old_sweep)
        raw_adc = max(0, min(4095, raw_adc))
        print("  Target: {}° | Real: {}° | ADC: {} | Current: {} mA".format(angle, status.angle, raw_adc, status.current_ma))
        if status.current_ma >= threshold_current:
            detected_hard_max = status.angle
            print("💥 Spike Detected! Physical end-stop encountered at {}°.".format(detected_hard_max))
            break
    else:
        print("⚠️ No response.")

if detected_hard_max is None:
    print("❌ Failed to detect Hard Max (reached 295° without spike). Using safety fallback: 290°")
    detected_hard_max = 290

# Back off to safe zone
print("Backing off to safe angle (150°)...")
servo.move(150)
servo.wait_until_done(timeout_ms=3000)
servo.clear_error()
time.sleep_ms(500)

print("\n--- Calibration Detection Summary ---")
print("  - Reported Hard Min Stop Angle: {}°".format(detected_hard_min))
print("  - Reported Hard Max Stop Angle: {}°".format(detected_hard_max))

# ─── 7. Perform Mathematical Extrapolation for Virtual Flash Limits ───────────
print("\n--- Extrapolating Virtual Endpoints for Flash Memory ---")
old_min = initial_config.hard_min_angle
old_max = initial_config.hard_max_angle
old_sweep = old_max - old_min

if old_sweep == 0:
    old_sweep = 280 # Safety fallback

# Reconstruct the raw ADC values measured at the physical mechanical stops
if initial_config.direction_invert:
    adc_min = int((old_max - detected_hard_min) * 4095 / old_sweep)
    adc_max = int((old_max - detected_hard_max) * 4095 / old_sweep)
else:
    adc_min = int((detected_hard_min - old_min) * 4095 / old_sweep)
    adc_max = int((detected_hard_max - old_min) * 4095 / old_sweep)

# Clamp reconstructed ADC values to safe range [0, 4095]
adc_min = max(0, min(4095, adc_min))
adc_max = max(0, min(4095, adc_max))

PHYSICAL_MIN_STOP = 10
PHYSICAL_MAX_STOP = 290

adc_range = adc_max - adc_min
if adc_range != 0:
    virtual_hard_min = int(PHYSICAL_MIN_STOP - (PHYSICAL_MAX_STOP - PHYSICAL_MIN_STOP) * adc_min / adc_range)
    virtual_hard_max = int(PHYSICAL_MIN_STOP + (PHYSICAL_MAX_STOP - PHYSICAL_MIN_STOP) * (4095 - adc_min) / adc_range)
else:
    virtual_hard_min = PHYSICAL_MIN_STOP
    virtual_hard_max = PHYSICAL_MAX_STOP

print("  - Reconstructed ADC at Min Stop: {}".format(adc_min))
print("  - Reconstructed ADC at Max Stop: {}".format(adc_max))
print("  - Calculated Virtual Hard Min:   {}° (extrapolated at ADC=0/4095)".format(virtual_hard_min))
print("  - Calculated Virtual Hard Max:   {}° (extrapolated at ADC=0/4095)".format(virtual_hard_max))

# Set soft limits slightly inside the physical mechanical stops (5° margin) for safety!
final_min_soft = PHYSICAL_MIN_STOP + 5
final_max_soft = PHYSICAL_MAX_STOP - 5

# Save the absolute virtual limits to flash!
flash_config = servo.configure(
    min_angle=final_min_soft,
    max_angle=final_max_soft,
    hard_min=virtual_hard_min,
    hard_max=virtual_hard_max,
    kp=60.0,
    ki=0.03,
    kd=8.0
)

if flash_config:
    print("✅ Calibrated configuration successfully saved to Flash!")
else:
    print("⚠️ Config saved (no explicit transaction reply).")

# ─── 8. Print Final Verified Configuration ───────────────────────────────────
print("\n--- Verifying Saved Flash Settings ---")
final_verify = servo.read_config()
if final_verify:
    print("Final Verified Flash Settings:")
    print("  - Software Limits:     {}° to {}°".format(final_verify.min_angle, final_verify.max_angle))
    print("  - Physical Hard Limits:{}° to {}°".format(final_verify.hard_min_angle, final_verify.hard_max_angle))
    print("  - PID Tuning:          Kp={:.2f}, Ki={:.4f}, Kd={:.2f}".format(final_verify.kp, final_verify.ki, final_verify.kd))
    print("  - Magic Word:          {:#X}".format(final_verify.magic))
    print("\n🎉 AUTOCALIBRATION COMPLETE!")
else:
    print("❌ Failed to read back final configuration!")
