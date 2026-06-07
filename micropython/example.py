"""
example.py — RP2040-Zero Quick-Start & Configuration Utility for Smart Servo

This script demonstrates how to set up, calibrate, scan, and configure 
an unconfigured Smart Servo (factory default ID 0) using a Waveshare RP2040-Zero.

===============================================================================
                       CONNECTION & WIRING GUIDE
===============================================================================

1. POWER CONNECTIONS:
   - RP2040-Zero GND ───────── Joint Common Ground ─── Servo GND
   - External Power Supply (5V - 8.4V) ───────────────── Servo V+
     (Warning: Do NOT power the motor directly from the RP2040-Zero 3V3 or 5V pin!
      Motors draw high currents that will damage or reset the RP2040-Zero.)

2. HALF-DUPLEX SINGLE-WIRE DATA BUS:
   - RP2040-Zero Pin '0' (GP0 / TX0) ───┬─── Servo Bus Data Line (PA12 on MM32 board)
   - RP2040-Zero Pin '1' (GP1 / RX0) ───┘
   - Connect a 4.7kΩ (or 10kΩ) Pull-Up Resistor from the combined Data Line to
     RP2040-Zero '3V3' pin.
     *Note: Since the MM32 board is configured in Open-Drain mode (AF_OD), 
     a physical pull-up resistor is REQUIRED to pull the data line high.*

                 RP2040-ZERO WIRING SCHEMA:
                     
      Waveshare RP2040-Zero
      ┌─────────────────────┐
      │     Pin '0' (GP0)   ├───────┬─────────────────── To Servo Data Line
      │     Pin '1' (GP1)   ├───────┤                    (PA12 on MM32 Board)
      │                     │       │
      │     Pin '3V3'       ├─[4.7k]┘ (Pull-Up Resistor)
      │     Pin 'GND'       ├─────────────────────────── To Servo GND & Power Supply GND
      └─────────────────────┘
"""

from machine import UART, Pin
import time
from smart_servo import ServoBus

# ─── 1. Initialize UART1 on Pi Pico ──────────────────────────────────────
# On Pi Pico, GPIO 4 and GPIO 5 are used for TX and RX.
print("Initializing UART1 on GP4 (Pin 4) and GP5 (Pin 5)...")
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart, reply_timeout_ms=5)

# ─── 2. Step 1: Scan for Unconfigured Servo (Default ID 0) ───────────────────
print("\n--- STEP 1: Scanning for Servo(s) ---")
print("Scanning IDs 0 to 127 to find active units...")
found = bus.scan(id_range=range(0, 127))

if not found:
    print("❌ No servos detected!")
    print("Please verify your connections:")
    print("  1. Is the servo powered by a suitable external power supply?")
    print("  2. Are Pi Pico pins GP4 and GP5 tied together and connected to the servo data line?")
    print("  3. Do you have a physical pull-up resistor (4.7k-10k) connected to 3V3?")
    print("  4. Are the Pi Pico GND and External Supply GND tied together?")
    import sys
    sys.exit()

for sid, status in found:
    print("✅ Detected Servo ID {}: Position={}°, Current={}mA".format(sid, status.angle, status.current_ma))

# Identify our target servo (prefer ID 0 if unconfigured, otherwise the first found)
target_id = 0
if not any(sid == 0 for sid, _ in found):
    target_id = found[0][0]
    print("⚠️ No unconfigured (ID 0) servo found. Using first detected ID: {}".format(target_id))
else:
    print("🎯 Found unconfigured servo on target ID 0.")

servo = bus.servo(target_id)

# ─── 3. Step 2: Show Initial Telemetry ───────────────────────────────────────
print("\n--- STEP 2: Querying Telemetry ---")
status = servo.poll()
if status:
    print("Initial Servo State:")
    print("  - Angle:      {}°".format(status.angle))
    print("  - Current:    {} mA".format(status.current_ma))
    print("  - Moving:     {}".format(status.is_moving))
    print("  - Holding:    {}".format(status.is_holding))
    print("  - Overcurrent:{}".format(status.overcurrent))

# Query and print the full non-volatile persistent configuration
print("\n--- Querying Non-Volatile Flash Configuration ---")
config_data = servo.read_config()
if config_data:
    print("Persistent Servo Configuration:")
    print("  - Servo ID:        {}".format(config_data.servo_id))
    print("  - Invert Direction:{}".format(config_data.direction_invert))
    print("  - Min/Max Angle:   {}° to {}°".format(config_data.min_angle, config_data.max_angle))
    print("  - Max Velocity:    {}°/sec".format(config_data.max_velocity))
    print("  - Current Limit:   {} mA".format(config_data.current_limit))
    print("  - Tuning PID:      Kp={:.2f}, Ki={:.4f}, Kd={:.2f}".format(config_data.kp, config_data.ki, config_data.kd))
    print("  - Calibration:     zero_adc={}, adc_per_360={}".format(config_data.zero_adc, config_data.adc_per_360))
    print("  - Magic Word:      {:#X}".format(config_data.magic))
else:
    print("⚠️ Could not read configuration from flash writing new configs!")
    servo.configure(
    servo_id=1,
    min_angle=0,
    max_angle=200,
    max_velocity=180,
    current_limit=1000)


print("Clearing any active or startup safety faults...")
servo.clear_error()
time.sleep(0.1)
clear_status = servo.poll()
if clear_status:
    print("✅ Faults cleared successfully. Current State: Overcurrent={}".format(
        clear_status.overcurrent
    ))
else:
    print("⚠️ Could not reach servo to verify fault status.")

# ─── 5. Step 3: Interactive Tracking Loop ─────────────────────────────────────
print("\n--- STEP 3: Interactive Tracking Loop ---")
print("Enter target angles to command the servo. Type 'exit' to stop.")
print("-" * 60)

try:
    while True:
        # Prompt the user for an angle
        user_input = input("\nEnter target angle (0 to 180) or 'exit': ").strip()
        if user_input.lower() == 'exit':
            break
            
        try:
            target_angle = int(user_input)
        
        except ValueError:
            print("❌ Invalid input! Please enter a number.")
            continue
        try:
            target_velocity = int(input("\nEnter target velocity: ").strip())
        except ValueError:
            print("❌ Invalid input! Please enter a number.")
            continue
            
        try:
            target_current = int(input("\nEnter target force limit (mA, 0=default): ").strip())
        except ValueError:
            print("❌ Invalid input! Please enter a number.")
            continue
            
        if target_angle < 0 or target_angle > 180:
            print("❌ Angle out of safe limits (0° to 180°)! Please try again.")
            continue

        print("Commanding target angle {}° with {} deg/s and {}mA limit...".format(target_angle, target_velocity, target_current))
        servo.move(target_angle, velocity=target_velocity, current=target_current)
        
            
        # Poll until the target angle is reached
        print("Moving and polling telemetry...")
        start_time = time.ticks_ms()
        has_printed_hold = False
        
        while True:
            pos = servo.poll()
            if pos:
                print("  Angle: {:3d}° | Current: {:4d} mA | Moving: {!s:<5} | Holding: {!s:<5} | Fault: {}".format(
                    pos.angle, pos.current_ma, pos.is_moving, pos.is_holding,
                    "OVERCURRENT" if pos.overcurrent else "None"
                ))
                
                # Check if it has hit an obstacle and is actively yielding
                if pos.is_holding and not has_printed_hold:
                    print("🚧 Obstacle detected! Actively holding with {}mA of force.".format(pos.current_ma))
                    has_printed_hold = True
                
                # Check if it has arrived (Moving flag is False)
                if not pos.is_moving:
                    print("✨ Arrived at target angle {}°!".format(pos.angle))
                    break
                    
                # Safe fallback timeout (e.g. 8 seconds) in case it gets physically blocked
                #if time.ticks_diff(time.ticks_ms(), start_time) > 8000:
                   # print("⚠️ Timeout: Took too long to reach the target.")
                    #break
            else:
                print("⚠️ Timeout - Servo not responding to poll")
                
            time.sleep_ms(150)
            
except KeyboardInterrupt:
    print("\nInteractive tracking stopped by user.")

print("\n--- Diagnostic & Configuration Sequence Complete! ---")
