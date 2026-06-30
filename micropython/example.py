"""
Quick-start example for controlling a Microdrive servo using a Raspberry Pi Pico / RP2040 
"""

from machine import UART, Pin
import time
import sys
from microdrive import ServoBus

# Setup UART1 on GP4 (TX) and GP5 (RX) at 250000 baud
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart, reply_timeout_ms=8)

print("Scanning for active servos...")
found = bus.scan(id_range=range(0, 127))

if not found:
    print("No servos detected. Check wiring and power supply.")
    sys.exit()

for sid, status in found:
    print(f"Found ID {sid}: Pos {status.angle}°, Current {status.current_ma}mA")

# Target ID 0 if found, otherwise use first active ID
target_id = 0 if any(s[0] == 0 for s in found) else found[0][0]
print(f"Targeting servo ID {target_id}")
servo = bus.servo(target_id)

# Read current config from flash
config_data = servo.read_config()
if config_data:
    print("\nServo configuration:")
    print(f"  ID: {config_data.servo_id}")
    print(f"  Limits: {config_data.min_angle}° to {config_data.max_angle}°")
    print(f"  Max Velocity: {config_data.max_velocity}°/s")
    print(f"  Current Limit: {config_data.current_limit}mA")
    print(f"  PID: Kp={config_data.kp:.2f}, Ki={config_data.ki:.4f}, Kd={config_data.kd:.2f}")
else:
    print("Could not read flash configuration. Initializing default settings...")
    servo.configure(
        servo_id=1,
        min_angle=0,
        max_angle=200,
        max_velocity=180,
        current_limit=1000
    )

servo.clear_error()
time.sleep(0.1)

print("\nEnter target angle (0 to 180). Type 'exit' to quit.")
try:
    while True:
        user_input = input("\nTarget angle: ").strip()
        if user_input.lower() == 'exit':
            break
            
        try:
            target_angle = int(user_input)
            target_velocity = int(input("Target velocity (deg/s, 0=default): ").strip())
            target_current = int(input("Force limit (mA, 0=default): ").strip())
        except ValueError:
            print("Invalid input! Please enter numbers.")
            continue
            
        if not (0 <= target_angle <= 180):
            print("Angle out of safe limits (0 to 180)!")
            continue

        print(f"Moving to {target_angle}°...")
        servo.move(target_angle, velocity=target_velocity, current=target_current)
        
        # Poll telemetry until movement stops
        has_printed_hold = False
        while True:
            pos = servo.poll()
            if pos:
                print(f"  Angle: {pos.angle:3d}° | Current: {pos.current_ma:4d} mA | Moving: {pos.is_moving} | Holding: {pos.is_holding}")
                
                if pos.is_holding and not has_printed_hold:
                    print(f"🚧 Obstacle detected! Holding at {pos.current_ma}mA.")
                    has_printed_hold = True
                
                if not pos.is_moving:
                    print(f"Arrived at {pos.angle}°!")
                    break
            else:
                print("Error: Servo not responding to poll")
                break
                
            time.sleep_ms(150)
            
except KeyboardInterrupt:
    print("\nStopped.")
