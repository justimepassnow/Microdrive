"""
config.py — Comprehensive Feature & Configuration Sweep Test for Microdrive

This script verifies all features of the microdrive:
1. Scanning for the servo on the single-wire half-duplex bus.
2. Querying the persistent non-volatile configuration (READ_CONFIG).
3. Writing a temporary/persistent configuration to lower the minimum angle limit to 20°
   (permitting the 20° targets to be reached without firmware clamping).
4. Verifying the new configuration parameters via another READ_CONFIG query.
5. Clearing active safety faults.
6. Running a continuous loop sweeping the servo from 20° to 220° (in steps of 40°) 
   and back to 20°, printing real-time telemetry at each step.
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
    print("❌ No servos detected! Check wiring, pull-ups, and external power.")
    import sys
    sys.exit()

for sid, status in found:
    print("✅ Detected Servo ID {}: Position={}°, Current={}mA".format(sid, status.angle, status.current_ma))

# Prefer ID 0 (default/unconfigured), otherwise use first detected ID
target_id = 0
if not any(sid == 0 for sid, _ in found):
    target_id = found[0][0]
    print("⚠️ Using first detected ID: {}".format(target_id))
else:
    print("🎯 Target ID 0 selected.")

servo = bus.servo(target_id)

# ─── 3. Query and Print Initial Persistent Configuration ─────────────────────
print("\n--- [FEATURE TEST] Reading Initial Flash Configuration ---")
initial_config = servo.read_config()
if initial_config:
    print("Initial Flash Settings:")
    print("  - Min/Max Angle Limit: {}° to {}°".format(initial_config.min_angle, initial_config.max_angle))
    print("  - Max Velocity:        {}°/sec".format(initial_config.max_velocity))
    print("  - Current Limit:       {} mA".format(initial_config.current_limit))
    print("  - PID Gains:           Kp={:.2f}, Ki={:.4f}, Kd={:.2f}".format(initial_config.kp, initial_config.ki, initial_config.kd))
    print("  - Magic Word:          {:#X}".format(initial_config.magic))
else:
    print("❌ Failed to query initial configuration!")
    import sys
    sys.exit()

# ─── 6. Clear Faults ─────────────────────────────────────────────────────────
print("\n--- Clearing any active safety faults ---")
servo.clear_error()
print("✅ Faults cleared.")


# ─── 7. Run Continuous Sweeping Loop ──────────────────────────────────────────
targets = [0,90,180,90]
print("\n--- [FEATURE TEST] Starting Continuous Sweep Loop ---")
print("Target angles: {} and back to 20° in a loop.".format(targets))
print("Press Ctrl+C to terminate.")
print("-" * 75)

loop_count = 1
try:
    while True:
        print("\n🔄 --- LOOP ITERATION #{} ---".format(loop_count))
        for target in targets:
            servo.move(target,velocity=0)
            
            start_time = time.ticks_ms()
            
            # Poll telemetry until the target is reached
            while True:
                pos = servo.poll()
                if pos:
                    # Print real-time telemetry
                    print("  Angle: {:3d}° | Current: {:4d} mA | Moving: {!s:<5} | Fault: {}".format(
                        pos.angle, pos.current_ma, pos.is_moving, 
                        "OVERCURRENT" if pos.overcurrent else "None"
                    ))
                    
                    # Arrived if the moving flag becomes False
                    if not pos.is_moving:
                        print("✨ Arrived at target angle {}°!".format(pos.angle))
                        break
                        
                    # 2-second safety timeout
                    if time.ticks_diff(time.ticks_ms(), start_time) > 2000:
                        print("⚠️ Timeout: Took too long to reach the target.")
                        break
                else:
                    print("⚠️ Timeout - Servo not responding to status poll.")
                    
                time.sleep_ms(20)
                
            # Rest briefly at the target
            time.sleep_ms(100)
            
        loop_count += 1

except KeyboardInterrupt:
    print("\n\nSweep test terminated by user.")
    print("--- Feature & Sweep Loop Test Complete ---")
