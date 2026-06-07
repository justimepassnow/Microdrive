"""
manual_calibrate.py — Manual Multi-Point Calibration Utility for Smart Servo

This script performs a precise manual calibration of the potentiometer:
1. Temporarily sets the servo's scale to 1:1 (zero_adc=0, adc_per_360=360) in RAM.
   This clever trick causes the servo's `angle` telemetry to exactly mirror its raw 12-bit ADC value!
2. Prompts the user to physically align the servo shaft to 0° by hand.
3. Reads the raw ADC at 0°.
4. Prompts the user to physically align the servo shaft to 90° by hand.
5. Reads the raw ADC at 90°.
6. Computes the exact ADC sweep for a full 360 degrees.
7. Writes `zero_adc` and `adc_per_360` to persistent flash.
"""

from machine import UART, Pin
import time
import sys
try:
    import select
except ImportError:
    import uselect as select
from smart_servo import ServoBus

def wait_for_enter_with_live_adc(servo, prompt_text):
    print(prompt_text)
    print("👉 (Press Enter when ready to lock in the position)")
    
    poll_obj = select.poll()
    poll_obj.register(sys.stdin, select.POLLIN)
    
    # Flush any stale input (like a previous Enter key) before we start
    while poll_obj.poll(0):
        sys.stdin.read(1)
    
    while True:
        status = servo.poll()
        if status:
            print("\rLive ADC: {:4d}   ".format(status.angle), end="")
        
        # Wait up to 50ms for user input
        if poll_obj.poll(50):
            sys.stdin.readline()
            # Drain any trailing \r or \n from Windows terminals
            while poll_obj.poll(0):
                sys.stdin.read(1)
            print() # newline
            break

# ─── 1. Initialize UART1 on Pi Pico ──────────────────────────────────────
print("Initializing UART1 on GP4 (TX) and GP5 (RX)...")
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart)

# ─── 2. Scan for Servos ───────────────────────────────────────────────────────
print("\n--- Scanning for active Servo ID(s) ---")
found = bus.scan(id_range=range(0, 6))

if not found:
    print("❌ No servos detected! Verify power and connections.")
    import sys
    sys.exit()

target_id = found[0][0]
print("🎯 Selected Servo ID: {}".format(target_id))
servo = bus.servo(target_id)

# ─── 3. Enable Raw ADC Telemetry Mode ─────────────────────────────────────────
print("\n--- Enabling Raw ADC Telemetry Mode ---")
# By setting zero=0 and scale=360, the servo's internal math outputs Angle = ADC!
servo.configure(zero_adc=0, adc_per_360=360, ram_only=True)
servo.clear_error() # Disarm motor so it spins freely
time.sleep(0.5)

# ─── 4. Measure ADC at 0 Degrees ─────────────────────────────────────────────
print("\n--- Step 1: Align to 0° (Zero Point) ---")
print("⚠️ The motor is UNPOWERED. You can rotate it easily by hand.")
wait_for_enter_with_live_adc(servo, "Rotate the servo output shaft to your desired 0° position.")

# Poll several times to get a clean, settled reading
pos_samples = []
for _ in range(5):
    status = servo.poll()
    if status:
        pos_samples.append(status.angle) # This is actually the RAW ADC now!
    time.sleep_ms(50)

if not pos_samples:
    print("❌ Failed to communicate with servo!")
    sys.exit()

adc_0 = int(sum(pos_samples) / len(pos_samples))
print("✅ 0° calibration point locked. Raw ADC: {}".format(adc_0))

# ─── 5. Measure ADC at 90 Degrees ────────────────────────────────────────────
print("\n--- Step 2: Align to 90° ---")
wait_for_enter_with_live_adc(servo, "Rotate the servo output shaft exactly 90° forward from 0°.")

pos_samples_90 = []
for _ in range(5):
    status = servo.poll()
    if status:
        pos_samples_90.append(status.angle)
    time.sleep_ms(50)

if not pos_samples_90:
    print("❌ Failed to communicate with servo!")
    sys.exit()

adc_90 = int(sum(pos_samples_90) / len(pos_samples_90))
print("✅ 90° calibration point locked. Raw ADC: {}".format(adc_90))

# ─── 6. Compute True Scale ───────────────────────────────────────────────────
adc_delta = adc_90 - adc_0

if adc_delta == 0:
    print("❌ Error: Potentiometer ADC did not change between 0° and 90°! Calibration aborted.")
    import sys
    sys.exit()

adc_per_360 = adc_delta * 4

print("\n--- Calibration Results ---")
print("  - Zero ADC (0°):        {}".format(adc_0))
print("  - 90° ADC:              {}".format(adc_90))
print("  - Computed ADC per 360°:{}".format(adc_per_360))

# ─── 7. Set Software Angle Limits ────────────────────────────────────────────
print("\n--- Step 3: Software Angle Limits ---")
print("To prevent the motor from crashing into its physical endpoints,")
print("you should set safe software travel limits.")

def get_int_input(prompt, default_val):
    while True:
        val = input(prompt).strip()
        if not val:
            return default_val
        try:
            return int(val)
        except ValueError:
            print("❌ Invalid number. Try again.")

min_angle = get_int_input("👉 Enter minimum safe angle [default 0]: ", 0)
max_angle = get_int_input("👉 Enter maximum safe angle [default 280]: ", 280)

# ─── 8. Write Calibration to Flash ───────────────────────────────────────────
input("\n👉 Press Enter to write calibration and limits to Flash...")
print("Saving parameters...")

# Save calibration and restore software limits
servo.configure(
    zero_adc=adc_0,
    adc_per_360=adc_per_360,
    min_angle=min_angle,
    max_angle=max_angle,
    ram_only=False
)
time.sleep(0.5)

# ─── 9. Print Final Verified Configuration ───────────────────────────────────
print("\n--- Verifying Saved Flash Settings ---")
final_verify = servo.read_config()
if final_verify:
    print("Final Verified Flash Settings:")
    print("  - Software Limits:     {}° to {}°".format(final_verify.min_angle, final_verify.max_angle))
    print("  - Physical Calibration:zero_adc={}, adc_per_360={}".format(final_verify.zero_adc, final_verify.adc_per_360))
    print("  - PID Tuning:          Kp={:.2f}, Ki={:.4f}, Kd={:.2f}".format(final_verify.kp, final_verify.ki, final_verify.kd))
    print("  - Magic Word:          {:#X}".format(final_verify.magic))
    print("\n🎉 MANUAL MULTI-POINT CALIBRATION COMPLETE!")
else:
    print("❌ Failed to read back final configuration!")




