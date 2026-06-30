"""
Speed and sweep test for Microdrive.
Sweeps the servo continuously with reducing time to reach the target and prints telemetry.
"""

from machine import UART, Pin
import time
import sys
from microdrive import ServoBus

uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart)

print("Scanning for active servos...")
found = bus.scan(id_range=range(0, 6))
if not found:
    print("No servos detected. Check power and connections.")
    sys.exit()

for sid, status in found:
    print(f"Found ID {sid}: Pos {status.angle}°, Current {status.current_ma}mA")

target_id = 0 if any(s[0] == 0 for s in found) else found[0][0]
print(f"Targeting servo ID {target_id}")
servo = bus.servo(target_id)

initial_config = servo.read_config()
if not initial_config:
    print("Failed to read initial configuration.")
    sys.exit()

print(f"Limits: {initial_config.min_angle}° to {initial_config.max_angle}°")
print(f"PID: Kp={initial_config.kp:.2f}, Ki={initial_config.ki:.4f}, Kd={initial_config.kd:.2f}")

servo.clear_error()
time.sleep_ms(100)

targets = [0, 45,90, 45, 0]
print(f"\nStarting sweep loop through: {targets}")
print("Press Ctrl+C to stop.")
print("-" * 60)

loop_count = 1
timeout=2000
try:
    while True:
        print(f"\nIteration #{loop_count}")
        for target in targets:
            servo.move(target)
            start_time = time.ticks_ms()
            while True:
                pos = servo.poll()
                if pos:
                    print(f"  Angle: {pos.angle:3d}° | Current: {pos.current_ma:4d} mA | Moving: {pos.is_moving} | Fault: {'OC' if pos.overcurrent else 'None'}")
                    
                    if not pos.is_moving:
                        print(f"Reached {pos.angle}°!")
                        break
                    
                    if time.ticks_diff(time.ticks_ms(), start_time) > timeout:
                        print("Timeout: Target took too long to reach.")
                        print(f"Minimum  timeout:{timeout}")
                        sys.exit()
                        
                time.sleep_ms(100)
            time.sleep_ms(50)
        loop_count += 1
        timeout-=100
        
except KeyboardInterrupt:
    print("\nStopped.")
