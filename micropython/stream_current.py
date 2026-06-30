"""
Live current streaming utility for Microdrive.
Reads and prints the current draw of a selected servo at regular intervals.
"""

from machine import UART, Pin
import time
import sys
from microdrive import ServoBus

def stream_live_current():
    uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
    bus = ServoBus(uart)

    print("Scanning for active servos...")
    found = bus.scan(id_range=range(0, 6))
    if not found:
        print("No servos detected.")
        return

    target_id = found[0][0]
    print(f"Targeting servo ID {target_id}")
    servo = bus.servo(target_id)
    
    print("\nLive Current draw (mA):")
    print("Press Ctrl+C to stop.\n")
    
    try:
        while True:
            status = servo.poll()
            if status:
                print(f"\rCurrent: {status.current_ma:4d} mA   ", end="")
            else:
                print("\rFailed to read servo.         ", end="")
            time.sleep_ms(50)
            
    except KeyboardInterrupt:
        print("\nStopped.")

if __name__ == "__main__":
    stream_live_current()
