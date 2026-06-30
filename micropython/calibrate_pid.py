"""
Automated PID calibration utility for Microdrive using step response tuning.
Note: While this utility provides a solid starting baseline, it may sometimes
fail to compute optimal gains. Manual retuning may be required for your specific setup.
"""

from machine import UART, Pin
import time
import sys
import uselect
from microdrive import ServoBus

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

print("\n--- Manual Alignment ---")
print("Rotate the output shaft close to 45 degrees, then press ENTER.")
servo.clear_error()

poll_input = uselect.poll()
poll_input.register(sys.stdin, uselect.POLLIN)
while poll_input.poll(0):
    sys.stdin.read(1)

start_angle = 90
last_angle = 90
while True:
    pos = servo.poll()
    if pos:
        last_angle = pos.angle
        print(f"\r  Position: {pos.angle}° | Press ENTER to start...", end="")
    if poll_input.poll(0):
        sys.stdin.readline()
        start_angle = last_angle
        print(f"\nPosition locked at {start_angle}°.")
        break
    time.sleep_ms(200)

time.sleep_ms(500)

def perform_step(target_angle, timeout_ms=1000):
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
        
    step_size = abs(target_angle - start_ang) or 1
    overshoot_deg = max(0, max_ang - target_angle) if target_angle > start_ang else max(0, target_angle - max_ang)
    overshoot_pct = (overshoot_deg / step_size) * 100.0
    
    time.sleep_ms(300)
    status = servo.poll()
    steady_error = abs(target_angle - status.angle) if status else 0
    return max_ang, overshoot_pct, elapsed, steady_error

step_size = 90
target1 = start_angle + step_size
target2 = start_angle
if target1 > 270:
    target1 = start_angle - step_size

current_kp = 10.0
current_ki = 0.0
current_kd = 0.0

print("\nRunning startup sweeps to break friction...")
for _ in range(3):
    servo.move(target1, 0)
    time.sleep_ms(800)
    servo.move(target2, 0)
    time.sleep_ms(800)

# Phase 1: Friction Floor
print("\nPhase 1: Finding Friction Floor (Kp)")
while True:
    print(f"Trying Kp={current_kp}...")
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    max_ang, _, _, _ = perform_step(target1, timeout_ms=100)
    
    reached = (max_ang >= target1 - 2) if target1 > start_angle else (max_ang <= target1 + 2)
    if reached:
        print(f"Baseline Kp found: {current_kp}")
        break
    current_kp += 10.0
    servo.move(target2, 0)
    time.sleep_ms(600)

# Phase 2: overshoot detection
print("\nPhase 2: Tuning Spring Limit (Kp)")
while True:
    current_kp += 2.0
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    print(f"Trying Kp={current_kp}...")
    
    _, ovs1, _, _ = perform_step(target1)
    _, ovs2, _, _ = perform_step(target2)
    avg_ovs = (ovs1 + ovs2) / 2.0
    print(f"  Overshoot: {avg_ovs:.1f}%")
    
    if avg_ovs >= 5.0:
        print(f"Spring limit reached at Kp={current_kp}")
        break

# Phase 3: Damping (Kd)
print("\nPhase 3: Tuning Damping (Kd)")
while True:
    current_kd += 1.0
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    print(f"Trying Kd={current_kd}...")
    
    _, ovs1, _, _ = perform_step(target1)
    _, ovs2, _, _ = perform_step(target2)
    avg_ovs = (ovs1 + ovs2) / 2.0
    print(f"  Overshoot: {avg_ovs:.1f}%")
    
    if avg_ovs <= 0.5:
        print(f"Damping locked at Kd={current_kd}")
        break

# Phase 4: Steady-State Error (Ki)
print("\nPhase 4: Steady-State Error Correction (Ki)")
_, _, _, err = perform_step(target1)
if err > 0:
    print(f"Steady state error: {err}°. Setting Ki=0.1...")
    current_ki = 0.1
    servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=True)
    
    start_watch = time.ticks_ms()
    while time.ticks_diff(time.ticks_ms(), start_watch) < 2500:
        st = servo.poll()
        if st:
            e = abs(target1 - st.angle)
            print(f"\r  Error: {e}°", end="")
            if e == 0:
                break
        time.sleep_ms(100)
    print()
else:
    print("No steady state error detected. Ki remains 0.0")

# Save tuned gains to flash
print("\nSaving PID parameters to flash...")
servo.set_pid(kp=current_kp, ki=current_ki, kd=current_kd, ram_only=False)
time.sleep_ms(100)

final_config = servo.read_config()
if final_config:
    print(f"Configured PID: Kp={final_config.kp:.2f}, Ki={final_config.ki:.4f}, Kd={final_config.kd:.2f}")
else:
    print(f"PID set: Kp={current_kp:.2f}, Ki={current_ki:.4f}, Kd={current_kd:.2f}")