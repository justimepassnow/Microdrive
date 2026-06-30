"""
Manual Calibration Utility for Microdrive.
Reads raw ADC values at 0° and 90° to calibrate potentiometer scaling.
"""

from machine import UART, Pin
import time
import sys
try:
    import select
except ImportError:
    import uselect as select
from microdrive import ServoBus

def wait_for_enter_with_live_adc(servo, prompt_text):
    print(prompt_text)
    print("👉 (Press Enter when ready to lock in the position)")
    
    poll_obj = select.poll()
    poll_obj.register(sys.stdin, select.POLLIN)
    
    # Flush stale inputs
    while poll_obj.poll(0):
        sys.stdin.read(1)
    
    while True:
        status = servo.poll()
        if status:
            print(f"\rLive ADC: {status.angle}   ", end="")
        
        if poll_obj.poll(50):
            sys.stdin.readline()
            while poll_obj.poll(0):
                sys.stdin.read(1)
            print()
            break

uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart)

print("Scanning for active servos...")
found = bus.scan(id_range=range(0, 6))
if not found:
    print("No servos detected. Check power and connections.")
    sys.exit()

target_id = found[0][0]
print(f"Targeting servo ID {target_id}")
servo = bus.servo(target_id)

# Force 1:1 scale in RAM to read raw ADC directly via status.angle
servo.configure(zero_adc=0, adc_per_360=360, ram_only=True)
servo.clear_error() # Disarm H-bridge for manual rotation
time.sleep(0.5)

print("\n--- Step 1: Align to 0° ---")
wait_for_enter_with_live_adc(servo, "Manually rotate the servo shaft to 0°.")

pos_samples = []
for _ in range(5):
    status = servo.poll()
    if status:
        pos_samples.append(status.angle)
    time.sleep_ms(50)

if not pos_samples:
    print("Communication failed.")
    sys.exit()

adc_0 = int(sum(pos_samples) / len(pos_samples))
print(f"0° reference ADC locked: {adc_0}")

print("\n--- Step 2: Align to 90° ---")
wait_for_enter_with_live_adc(servo, "Rotate the servo shaft exactly 90° forward.")

pos_samples_90 = []
for _ in range(5):
    status = servo.poll()
    if status:
        pos_samples_90.append(status.angle)
    time.sleep_ms(50)

if not pos_samples_90:
    print("Communication failed.")
    sys.exit()

adc_90 = int(sum(pos_samples_90) / len(pos_samples_90))
print(f"90° reference ADC locked: {adc_90}")

adc_delta = adc_90 - adc_0
if adc_delta == 0:
    print("Error: ADC did not change between 0° and 90°.")
    sys.exit()

adc_per_360 = adc_delta * 4
print(f"\nCalculated: zero_adc={adc_0}, adc_per_360={adc_per_360}")

print("\n--- Step 3: Software Angle Limits ---")
def get_int_input(prompt, default_val):
    while True:
        val = input(prompt).strip()
        if not val:
            return default_val
        try:
            return int(val)
        except ValueError:
            print("Invalid input. Try again.")

min_angle = get_int_input("Enter minimum safe angle [0]: ", 0)
max_angle = get_int_input("Enter maximum safe angle [280]: ", 280)

input("\n👉 Press Enter to write calibration and limits to Flash...")
print("Saving parameters...")

servo.configure(
    zero_adc=adc_0,
    adc_per_360=adc_per_360,
    min_angle=min_angle,
    max_angle=max_angle,
    ram_only=False
)
time.sleep(0.5)

final_verify = servo.read_config()
if final_verify:
    print("\nVerified configuration in flash:")
    print(f"  Limits: {final_verify.min_angle}° to {final_verify.max_angle}°")
    print(f"  Zero ADC: {final_verify.zero_adc} | ADC Scale: {final_verify.adc_per_360}")
    print(f"  PID: Kp={final_verify.kp:.2f}, Ki={final_verify.ki:.4f}, Kd={final_verify.kd:.2f}")
else:
    print("Failed to verify saved configuration.")
