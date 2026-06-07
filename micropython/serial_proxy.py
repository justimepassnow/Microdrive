import sys
import json
import select
from machine import UART, Pin
from smart_servo import ServoBus

# Configure UART for the Servo Bus. 
uart = UART(1, baudrate=250000, tx=Pin(4), rx=Pin(5))
bus = ServoBus(uart)

def send_response(data):
    print(json.dumps(data))
    
def log_msg(msg):
    send_response({"res": "log", "msg": msg})

log_msg("Smart Servo Proxy Started.")

while True:
    line = sys.stdin.readline().strip()
    if not line: continue
    try:
        req = json.loads(line)
        cmd = req.get("cmd")
        sid = req.get("id", 0)
        
        if cmd == "scan":
            # Scan full range of IDs 0-253 (extremely fast now with 15ms timeout)
            servos = bus.scan()
            send_response({"res": "scan", "data": [s[0] for s in servos]})
        elif cmd == "move":
            bus.servo(sid).move(req.get("angle", 0), req.get("velocity", 0), req.get("current", 0))
            send_response({"res": "ack", "cmd": "move"})
        elif cmd == "poll":
            status = bus.servo(sid).poll()
            if status:
                send_response({"res": "poll", "data": {
                    "id": status.servo_id,
                    "angle": status.angle,
                    "current_ma": status.current_ma,
                    "is_moving": status.is_moving,
                    "is_holding": status.is_holding,
                    "overcurrent": status.overcurrent
                }})
            else:
                send_response({"res": "error", "msg": "Poll Timeout for ID {}".format(sid)})
        elif cmd == "read_config":
            cfg = bus.servo(sid).read_config()
            if cfg:
                send_response({"res": "read_config", "data": {
                    "servo_id": cfg.servo_id,
                    "direction_invert": cfg.direction_invert,
                    "min_angle": cfg.min_angle,
                    "max_angle": cfg.max_angle,
                    "max_velocity": cfg.max_velocity,
                    "current_limit": cfg.current_limit,
                    "kp": cfg.kp, "ki": cfg.ki, "kd": cfg.kd,
                    "zero_adc": cfg.zero_adc,
                    "adc_per_360": cfg.adc_per_360
                }})
            else:
                send_response({"res": "error", "msg": "Config Read Timeout for ID {}".format(sid)})
        elif cmd == "configure":
            params = req.get("params", {})
            bus.servo(sid).configure(**params)
            send_response({
                "res": "ack",
                "cmd": "configure",
                "id": sid,
                "new_id": params.get("servo_id", sid)
            })
        elif cmd == "clear_error":
            bus.servo(sid).clear_error()
            send_response({"res": "ack", "cmd": "clear_error"})
    except Exception as e:
        send_response({"res": "error", "msg": str(e)})
