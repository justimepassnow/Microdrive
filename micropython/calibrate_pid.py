"""
calibrate_pid.py — Automated PID Calibration Utility for Microdrive

This script uses a Gradient Ascent Step Response auto-tuner algorithm:
1. Scans the UART bus for connected servos.
2. Prompts the user to position the servo and start.
3. Phase 1: Finds Friction Floor (Kp) by increasing Kp until a 45-degree step is successful.
4. Phase 2: Finds Spring Limit by increasing Kp until 5-10% overshoot is reached.
5. Phase 3: Damps the motor by increasing Kd until overshoot is eliminated.
6. Phase 4: Injects Ki to overcome deadband and close steady-state error.
7. Saves the new PID parameters to Flash memory.
"""

from machine import UART, Pin
import time
import sys
import uselect
from microdrive import ServoBus

# ─── 1. Initialize UART1 on Pi Pico ──────────────────────────────────────
print("Initializing UART1 on GP4 (TX) and GP5 (RX)...")
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart)

# ─── 2. Scan for Servos ───────────────────────────────────────────────────────
print("\n--- Scanning for active Servo ID(s) ---")
found = bus.scan(id_range=range(0, 6))

if not found:
    print("❌ No servos detected! Verify power and connections.")
    sys.exit()

target_id = found[0][0]
print("🎯 Selected Servo ID: {}".format(target_id))
servo = bus.servo(target_id)

# ─── 3. Manual Positioning Phase ─────────────────────────────────────────────
print("\n" + "=" * 55)
print("⚠️  SAFETY AND CALIBRATION WARNING ⚠️")
print("1. Ensure the servo output shaft can rotate freely.")
print("2. The motor will make sharp 45-degree steps back and forth.")
print("=" * 55)

print("\nDisarming the motor...")
servo.clear_error()

print("\n👉 MANUAL ALIGNMENT:")
print("Rotate the servo close to 45°, then press ENTER.")

poll_input = uselect.poll()
poll_input.register(sys.stdin, uselect.POLLIN)
while poll_input.poll(0):
    sys.stdin.read(1)
pos=servo.poll()
start_angle = pos.angle
last_angle = pos.angle
while True:
    pos = servo.poll()
    if pos:
        last_angle = pos.angle
        print("\r  Current Position: {:3d}° | Press ENTER to start...".format(pos.angle), end="")
    
    if poll_input.poll(0):
        sys.stdin.readline()
        start_angle = last_angle if last_angle != -999 else 90
        print(f"\n\n✨ Position locked at {start_angle}°!")
        break
        
    time.sleep_ms(200)

time.sleep_ms(500)

# ─── 4. Gradient Ascent Step Response ────────────────────────────────────────

def perform_step(target_angle, timeout_ms=1000):
    """Commands a step and measures maximum angle reached to calculate overshoot."""
    st = servo.poll()
    start_ang = st.angle if st else target_angle
    
    servo.move(target_angle, 0)
    start_time = time.ticks_ms()
    
    max_ang = start_ang
    
    while True:
        status = servo.poll()
        if not status:
            time.sleep_ms(10)
            continue
            
        current_angle = status.angle
        
        if target_angle > start_ang:
            if current_angle > max_ang:
                max_ang = current_angle
        else:
            if current_angle < max_ang:
                max_ang = current_angle
                
        elapsed = time.ticks_diff(time.ticks_ms(), start_time)
        if elapsed > timeout_ms:
            break
            
        if elapsed > 200 and not status.is_moving:
            break
            
        time.sleep_ms(10)
        
    step_size = abs(target_angle - start_ang)
    if step_size == 0: step_size = 1
    
    if target_angle > start_ang:
        overshoot_deg = max(0, max_ang - target_angle)
    else:
        overshoot_deg = max(0, target_angle - max_ang)
        
    overshoot_pct = (overshoot_deg / step_size) * 100.0
    
    time.sleep_ms(300) # Settle time
    status = servo.poll()
    steady_error = abs(target_angle - status.angle) if status else 0
    
    return max_ang, overshoot_pct, elapsed, steady_error

step_size = 90
target1 = start_angle + step_size
target2 = start_angle

# Ensure target1 doesn't hit hardware limits (assuming 0-280 default limits)
if target1 > 270:
    target1 = start_angle - step_size
    target2 = start_angle

current_kp = 10.0
current_ki = 0.0
current_kd = 0.0

print("\n🚀 Starting Gradient Ascent Step Response Autotuning...")

print("\n--- Warm-up: Breaking Stiction ---")
# Sweep back and forth a few times with current PID to break any mechanical stiction
for _ in range(3):
    servo.move(target1, 0)
    time.sleep_ms(800)
    servo.move(target2, 0)
    time.sleep_ms(800)

# Phase 1: Finding the Friction Floor (Kp)
print("\n--- Phase 1: Finding Friction Floor (Kp) ---")
servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
time.sleep_ms(100)

while True:
    print(f"Trying Kp={current_kp}...")
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    
    # Step to target1 with a strict 250ms time limit
    # This forces Kp to keep rising until the motor is fast enough to reach the target in <`50ms
    max_ang, ovs, elapsed, err = perform_step(target1, timeout_ms=100)
    
    reached = False
    if target1 > start_angle and max_ang >= target1 - 2:
        reached = True
    elif target1 < start_angle and max_ang <= target1 + 2:
        reached = True
        
    if reached:
        print(f"✅ Friction floor found! Baseline Kp = {current_kp}")
        break
        
    current_kp += 10.0
    
    # Reset position to start_angle for next try
    servo.move(target2, 0)
    time.sleep_ms(600)

# Phase 2: Finding the Spring Limit (Kp Overshoot)
print("\n--- Phase 2: Finding Spring Limit (Kp Overshoot) ---")

while True:
    current_kp += 2.0
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    print(f"Trying Kp={current_kp}...")
    
    # 2 sweeps for bi-directional averaging
    _, ovs1, _, _ = perform_step(target1)
    _, ovs2, _, _ = perform_step(target2)
    
    avg_ovs = (ovs1 + ovs2) / 2.0
    print(f"  Avg Overshoot: {avg_ovs:.1f}% (Fwd: {ovs1:.1f}%, Rev: {ovs2:.1f}%)")
    
    if avg_ovs >= 5.0:
        print(f"✅ Spring limit found! Locked Kp = {current_kp}")
        break

# Phase 3: The Shock Absorber (Kd)
print("\n--- Phase 3: The Shock Absorber (Kd) ---")
while True:
    current_kd += 1.0
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    print(f"Trying Kd={current_kd}...")
    
    _, ovs1, _, _ = perform_step(target1)
    _, ovs2, _, _ = perform_step(target2)
    
    avg_ovs = (ovs1 + ovs2) / 2.0
    print(f"  Avg Overshoot: {avg_ovs:.1f}%")
    
    if avg_ovs <= 0.5:
        print(f"✅ Critical damping achieved! Locked Kd = {current_kd}")
        break

# Phase 4: Closing the Gap (Ki)
print("\n--- Phase 4: Closing the Gap (Ki) ---")
max_ang, ovs, elapsed, err = perform_step(target1)

if err > 0:
    print(f"Steady state error is {err} deg. Injecting Ki = 0.01...")
    current_ki = 0.1
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    
    start_watch = time.ticks_ms()
    while time.ticks_diff(time.ticks_ms(), start_watch) < 2500:
        st = servo.poll()
        if st:
            e = abs(target1 - st.angle)
            print(f"\r  Error: {e} deg... (watching for 2.5s)", end="")
            if e == 0:
                print("\n✅ Deadband reached!")
                break
        time.sleep_ms(100)
    print("")
else:
    print("✅ No steady state error detected. Ki remains 0.0.")

# ─── 5. Final Output ─────────────────────────────────────────────────────────
print("\n--- Saving Final Verified PID Gains to Flash ---")
servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=False)
time.sleep_ms(100)

final_config = servo.read_config()
if final_config:
    print("  - Kp: {:.2f}  (Proportional)".format(final_config.kp))
    print("  - Ki: {:.4f}  (Integral)".format(final_config.ki))
    print("  - Kd: {:.2f}  (Derivative)".format(final_config.kd))
    print("\n🎉 AUTOMATED PID CALIBRATION AND FLASH SAVING COMPLETE!")
else:
    print(f"  - Kp: {current_kp:.2f}")
    print(f"  - Ki: {current_ki:.4f}")
    print(f"  - Kd: {current_kd:.2f}")
    print("\n⚠️ Failed to read back config, but PID was set.")