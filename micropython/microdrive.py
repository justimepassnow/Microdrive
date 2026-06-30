"""
microdrive.py — MicroPython driver for Microdrive (MM32 firmware)

Communicates over a half-duplex single-wire UART bus at 250000 baud.
Protocol: binary packets with 0xFF 0xFF header, ID, length, instruction,
parameters (little-endian), and inverted-sum checksum.

Supports daisy-chained servos on the same bus, each addressed by a unique ID.

Usage:
    from machine import UART, Pin
    from microdrive import ServoBus

    bus = ServoBus(UART(1, 250000), dir_pin=Pin(4, Pin.OUT))
    servo = bus.servo(0)
    servo.move(180, velocity=200)
    status = servo.poll()
    print(status)
"""

import struct
import time

# Protocol Constants

_HEADER          = b'\xff\xff'
_BROADCAST_ID    = 0xFE

_INST_CONTROL    = 0x01
_INST_CONFIG     = 0x02
_INST_POLL       = 0x03
_INST_CLEAR_ERR  = 0x04
_INST_READ_CONFIG = 0x05

_STATUS_REPLY_LEN = 11  # Total bytes in a status reply packet
_CONFIG_REPLY_LEN = 36  # Total bytes in a configuration reply packet

# CONFIG update mask bits
_MASK_ID_DIR     = 1 << 0
_MASK_ANGLE_LIM  = 1 << 1
_MASK_VELOCITY   = 1 << 2
_MASK_CURRENT    = 1 << 3
_MASK_PID        = 1 << 4
_MASK_HARD_CAL   = 1 << 5
_MASK_RAM_ONLY   = 1 << 6

# Reply timeout (ms) — optimized for fast RP2040 turnaround (active node replies in ~2.7ms)
_REPLY_TIMEOUT_MS = 8


# Status Reply Container

class ServoStatus:
    """Parsed status reply from the servo."""

    __slots__ = ('servo_id', 'instruction', 'angle', 'current_ma',
                 'is_moving', 'overcurrent', 'is_holding')

    def __init__(self, servo_id, instruction, angle, current_ma, flags):
        self.servo_id    = servo_id
        self.instruction = instruction
        self.angle       = angle
        self.current_ma  = current_ma
        self.is_moving   = bool(flags & 0x01)
        self.overcurrent = bool(flags & 0x02)
        self.is_holding  = bool(flags & 0x04)

    @property
    def has_fault(self):
        """True if any fault flag is active."""
        return self.overcurrent

    def __repr__(self):
        parts = [
            'angle={}°'.format(self.angle),
            'current={}mA'.format(self.current_ma),
        ]
        flags = []
        if self.is_moving:
            flags.append('MOVING')
        if self.is_holding:
            flags.append('HOLDING')
        if self.overcurrent:
            flags.append('OVERCURRENT')
        if flags:
            parts.append('flags=' + '|'.join(flags))
        return '<ServoStatus {}>'.format(' '.join(parts))


# Configuration Reply Container
class ServoConfigData:
    """Parsed configuration stored in the servo's flash memory."""

    __slots__ = ('servo_id', 'direction_invert', 'min_angle', 'max_angle',
                 'max_velocity', 'current_limit', 'kp', 'ki', 'kd',
                 'zero_adc', 'adc_per_360', 'magic')

    def __init__(self, servo_id, direction_invert, min_angle, max_angle,
                 max_velocity, current_limit, kp_q16, ki_q16, kd_q16,
                 zero_adc, adc_per_360, magic):
        self.servo_id         = servo_id
        self.direction_invert = bool(direction_invert)
        self.min_angle        = min_angle
        self.max_angle        = max_angle
        self.max_velocity     = max_velocity
        self.current_limit    = current_limit
        self.kp               = _q16_to_float(kp_q16)
        self.ki               = _q16_to_float(ki_q16)
        self.kd               = _q16_to_float(kd_q16)
        self.zero_adc         = zero_adc
        self.adc_per_360      = adc_per_360
        self.magic            = magic

    def __repr__(self):
        return (
            "<ServoConfigData id={} dir_invert={} limits={}°-{}° "
            "max_vel={} current_lim={}mA kp={:.2f} ki={:.4f} kd={:.2f} zero_adc={} adc_per_360={} magic={:#X}>"
        ).format(
            self.servo_id, self.direction_invert, self.min_angle, self.max_angle,
            self.max_velocity, self.current_limit, self.kp, self.ki, self.kd,
            self.zero_adc, self.adc_per_360, self.magic
        )


def _parse_config_reply(raw):
    """
    Parse a 36-byte configuration reply packet.
    Returns a ServoConfigData or None if the packet is invalid.
    """
    if len(raw) != _CONFIG_REPLY_LEN:
        return None
    if raw[0] != 0xFF or raw[1] != 0xFF:
        return None

    sid   = raw[2]
    length = raw[3]
    inst  = raw[4]

    if length != 32:  # instruction (1) + params (30) + checksum (1)
        return None

    # Verify checksum (bytes 2..34 -> checksum at byte 35)
    expected = _checksum(raw[2:35])
    if raw[35] != expected:
        return None

    # Unpack the 30 parameter bytes
    params = raw[5:35]
    unpacked = struct.unpack('<BBHHHHiiihhI', params)
    
    return ServoConfigData(*unpacked)


# Low-level Packet Helpers

def _checksum(data):
    """Compute protocol checksum: ~(sum of bytes) & 0xFF."""
    return (~sum(data)) & 0xFF


def _build_packet(servo_id, instruction, params=b''):
    """Assemble a complete protocol packet as bytes."""
    length = 1 + len(params) + 1  # instruction + params + checksum
    body = bytes([servo_id, length, instruction]) + params
    chk = _checksum(body)
    return _HEADER + body + bytes([chk])


def _parse_status_reply(raw):
    """
    Parse an 11-byte status reply packet.
    Returns a ServoStatus or None if the packet is invalid.
    """
    if len(raw) != _STATUS_REPLY_LEN:
        return None
    if raw[0] != 0xFF or raw[1] != 0xFF:
        return None

    sid   = raw[2]
    length = raw[3]
    inst  = raw[4]

    if length != 0x07:
        return None

    # Verify checksum (bytes 2..9 -> checksum at byte 10)
    expected = _checksum(raw[2:10])
    if raw[10] != expected:
        return None

    angle      = raw[5] | (raw[6] << 8)
    if angle >= 32768:
        angle -= 65536
        
    current_ma = raw[7] | (raw[8] << 8)
    flags      = raw[9]

    return ServoStatus(sid, inst, angle, current_ma, flags)


# Fixed-point conversion helpers

def _float_to_q16(value):
    """Convert a float PID gain to Q16 fixed-point (signed int32)."""
    raw = int(value * 65536)
    # Clamp to signed 32-bit range
    if raw > 0x7FFFFFFF:
        raw = 0x7FFFFFFF
    elif raw < -0x80000000:
        raw = -0x80000000
    return raw


def _q16_to_float(raw):
    """Convert a Q16 fixed-point int32 back to float."""
    # Handle signed 32-bit
    if raw >= 0x80000000:
        raw -= 0x100000000
    return raw / 65536.0


def _pack_u16_le(val):
    """Pack an unsigned 16-bit integer as 2 little-endian bytes."""
    return struct.pack('<H', val)


# Servo Bus Manager

class ServoBus:
    """
    Manages the shared half-duplex UART bus for one or more Microdrives.

    Parameters
    ----------
    uart : machine.UART
        Pre-configured UART instance at 250000 baud, 8N1.
        For single-wire mode the TX pin should be wired to the servo bus line.
    dir_pin : machine.Pin or None
        Optional direction control pin (active-high = transmit).
        Set to None if the UART hardware handles half-duplex natively
        or if using a shared open-drain TX/RX line.
    reply_timeout_ms : int
        Milliseconds to wait for a servo reply before giving up.
    """

    def __init__(self, uart, dir_pin=None, reply_timeout_ms=_REPLY_TIMEOUT_MS):
        self._uart = uart
        self._dir_pin = dir_pin
        self._timeout_ms = reply_timeout_ms

    # Raw TX / RX functions

    def _tx_mode(self):
        if self._dir_pin is not None:
            self._dir_pin.value(1)

    def _rx_mode(self):
        if self._dir_pin is not None:
            self._dir_pin.value(0)

    def _flush_rx(self):
        """Drain any stale bytes sitting in the RX buffer."""
        while self._uart.any():
            self._uart.read(self._uart.any())

    def _send(self, packet):
        """Transmit a raw packet onto the bus."""
        self._flush_rx()
        self._tx_mode()
        self._uart.write(packet)
        # uart.write() is non-blocking on ESP32/RP2040 — bytes clock out in
        # Flush if supported by the port, otherwise fallback to hardcoded delay
        if hasattr(self._uart, 'flush'):
            self._uart.flush()
        else:
            wait_us = len(packet) * 40 + 200
            time.sleep_us(wait_us)
            
        self._rx_mode()

    def _receive_reply(self, expected_len=_STATUS_REPLY_LEN):
        """
        Wait for and read an expected number of bytes in a reply packet.
        Returns ServoStatus, ServoConfigData or None on timeout / bad data.
        """
        buf = bytearray()
        deadline = time.ticks_add(time.ticks_ms(), self._timeout_ms)

        while time.ticks_diff(deadline, time.ticks_ms()) > 0:
            if self._uart.any():
                chunk = self._uart.read(self._uart.any())
                if chunk:
                    buf.extend(chunk)

                # Scan for header and attempt parse once we have enough bytes
                while len(buf) >= expected_len:
                    # Find header
                    idx = 0
                    while idx <= len(buf) - 2:
                        if buf[idx] == 0xFF and buf[idx + 1] == 0xFF:
                            break
                        idx += 1
                    else:
                        # No header found — discard everything except a trailing 0xFF
                        if buf and buf[-1] == 0xFF:
                            buf = bytearray([0xFF])
                        else:
                            buf = bytearray()
                        break

                    # Discard bytes before the header
                    if idx > 0:
                        buf = buf[idx:]

                    if len(buf) < expected_len:
                        break  # Need more bytes

                    candidate = bytes(buf[:expected_len])
                    if expected_len == _STATUS_REPLY_LEN:
                        result = _parse_status_reply(candidate)
                    elif expected_len == _CONFIG_REPLY_LEN:
                        result = _parse_config_reply(candidate)
                    else:
                        result = None
                    
                    if result is not None:
                        return result

                    # Bad packet — skip past this header and keep scanning
                    buf = buf[2:]
            else:
                time.sleep_us(100)

        return None

    def _transact(self, packet, expect_reply=True, expected_len=_STATUS_REPLY_LEN):
        """Send a packet and optionally wait for the status reply."""
        self._send(packet)
        if expect_reply:
            # On a single-wire half-duplex bus, every transmitted byte is
            # echoed back into the RX buffer.  Drain the echo deterministically
            # before scanning for the servo's real reply.
            remaining = len(packet)
            deadline = time.ticks_add(time.ticks_ms(), self._timeout_ms)
            while remaining > 0 and time.ticks_diff(deadline, time.ticks_ms()) > 0:
                if self._uart.any():
                    chunk = self._uart.read(min(remaining, self._uart.any()))
                    if chunk:
                        remaining -= len(chunk)
                else:
                    time.sleep_us(50)
            return self._receive_reply(expected_len=expected_len)
        return None

    # High-level bus commands

    def servo(self, servo_id):
        """
        Create a Servo handle bound to this bus.

        Parameters
        ----------
        servo_id : int
            The servo's address (0–127). ID 0 targets unconfigured servos.
        """
        return Servo(self, servo_id)

    def broadcast_move(self, angle, velocity=0, current=0):
        """
        Move all servos on the bus simultaneously (no reply expected).

        Parameters
        ----------
        angle : int
            Target angle in degrees.
        velocity : int
            Temporary velocity in deg/s. 0 = use each servo's flash default.
        current : int
            Temporary force/current limit in mA. 0 = use each servo's flash default.
        """
        params = _pack_u16_le(int(angle)) + _pack_u16_le(int(velocity)) + _pack_u16_le(int(current))
        pkt = _build_packet(_BROADCAST_ID, _INST_CONTROL, params)
        self._transact(pkt, expect_reply=False)

    def broadcast_clear_error(self):
        """Clear faults on all servos (no reply expected)."""
        pkt = _build_packet(_BROADCAST_ID, _INST_CLEAR_ERR, b'\x01')
        self._transact(pkt, expect_reply=False)

    def broadcast_disarm(self):
        """
        Disarm all servos on the bus simultaneously, turning off H-bridges
        so that all servo shafts spin completely freely.
        """
        return self.broadcast_clear_error()

    def scan(self, id_range=range(0, 128)):
        """
        Scan the bus for connected servos by polling each ID.
        Returns a list of (servo_id, ServoStatus) tuples for servos that replied.

        Warning: This is slow — each non-responding ID waits for the full timeout.
        Narrow the range if you know the expected IDs.
        """
        found = []
        for sid in id_range:
            pkt = _build_packet(sid, _INST_POLL)
            reply = self._transact(pkt, expect_reply=True)
            if reply is not None:
                found.append((sid, reply))
        return found


# Servo Handle

class Servo:
    """
    High-level interface to a single Microdrive on the bus.

    Created via ``bus.servo(id)`` — do not instantiate directly.
    """

    def __init__(self, bus, servo_id):
        self._bus = bus
        self._id = servo_id

    @property
    def id(self):
        """This servo's bus address."""
        return self._id

    # CONTROL (0x01) command

    def move(self, angle, velocity=0, current=0):
        """
        Command the servo to move to `angle` degrees.

        Parameters
        ----------
        angle : int
            Target angle in degrees (clamped to the servo's configured limits).
        velocity : int
            Temporary movement speed in deg/s. 0 = use flash default.
        current : int
            Temporary force/current limit in mA. 0 = use flash default.

        Returns
        -------
        None
            No reply is expected to speed up the loop.
        """
        params = _pack_u16_le(int(angle)) + _pack_u16_le(int(velocity)) + _pack_u16_le(int(current))
        pkt = _build_packet(self._id, _INST_CONTROL, params)
        self._bus._transact(pkt, expect_reply=False)
        return None

    # POLL_STATUS (0x03) command

    def poll(self):
        """
        Request the servo's current status without changing anything.

        Returns
        -------
        ServoStatus or None
            Current angle, current draw, and fault flags (None on timeout).
        """
        pkt = _build_packet(self._id, _INST_POLL)
        return self._bus._transact(pkt, expect_reply=True)

    # CLEAR_ERROR (0x04) command

    def clear_error(self):
        """
        Clear overcurrent fault flag, reset PID memory,
        and lock the target angle to the servo's current physical position.

        Returns
        -------
        None
        """
        pkt = _build_packet(self._id, _INST_CLEAR_ERR, b'\x01')
        self._bus._transact(pkt, expect_reply=False)
        return None

    def disarm(self):
        """
        Disarm the motor H-bridge, disabling power so the shaft spins freely.
        Re-arms automatically upon sending the next move command.
        """
        return self.clear_error()

    # READ_CONFIG (0x05) command

    def read_config(self):
        """
        Request the servo's full stored persistent configuration from flash memory.

        Returns
        -------
        ServoConfigData or None
            Parsed config data, or None on timeout/error.
        """
        pkt = _build_packet(self._id, _INST_READ_CONFIG)
        return self._bus._transact(pkt, expect_reply=True, expected_len=_CONFIG_REPLY_LEN)


    # CONFIG (0x02) — Granular Setters
    #    Each setter only sets its own update_mask bit.  All 25 parameter bytes
    # are always sent (fixed-length packet), with zeros in the unused slots.
    # The firmware only reads the fields whose mask bits are set.

    def _send_config(self, mask, params_25):
        """
        Send a CONFIG packet with the given update mask and 25-byte parameter payload.
        The firmware reads rx_params[0] as the mask and rx_params[1..25] as the
        config fields — exactly 25 data bytes after the mask.
        """
        assert len(params_25) == 25, "CONFIG params must be exactly 25 bytes"
        full_params = bytes([mask]) + params_25
        pkt = _build_packet(self._id, _INST_CONFIG, full_params)
        return self._bus._transact(pkt, expect_reply=(self._id != _BROADCAST_ID))

    def _blank_params(self):
        """Return a mutable 25-byte zeroed parameter buffer."""
        return bytearray(25)

    def set_id(self, new_id, direction_invert=False):
        """
        Change the servo's bus address and/or motor direction.

        Parameters
        ----------
        new_id : int
            New servo ID (0–127). 0 = unconfigured.
        direction_invert : bool
            True to invert the motor rotation direction.

        Returns
        -------
        ServoStatus or None

        Note
        ----
        After changing the ID, create a new ``bus.servo(new_id)`` handle.
        """
        p = self._blank_params()
        p[0] = (new_id & 0x7F) | ((1 if direction_invert else 0) << 7)
        return self._send_config(_MASK_ID_DIR, bytes(p))

    def set_angle_limits(self, min_angle, max_angle):
        """
        Set the software-enforced angle limits (degrees).

        Parameters
        ----------
        min_angle : int
            Minimum allowable target angle.
        max_angle : int
            Maximum allowable target angle.
        """
        p = self._blank_params()
        struct.pack_into('<HH', p, 1, int(min_angle), int(max_angle))
        return self._send_config(_MASK_ANGLE_LIM, bytes(p))

    def set_velocity(self, max_velocity):
        """
        Set the flash-stored default velocity limit (deg/s).

        Parameters
        ----------
        max_velocity : int
            Default maximum velocity in degrees per second.
        """
        p = self._blank_params()
        struct.pack_into('<H', p, 5, int(max_velocity))
        return self._send_config(_MASK_VELOCITY, bytes(p))

    def set_current_limit(self, current_limit):
        """
        Set the over-current fault threshold (mA).

        Parameters
        ----------
        current_limit : int
            Current draw threshold in milliamps.
        """
        p = self._blank_params()
        struct.pack_into('<H', p, 7, int(current_limit))
        return self._send_config(_MASK_CURRENT, bytes(p))

    def set_pid(self, kp=None, ki=None, kd=None, ram_only=False):
        """
        Set PID gains. Accepts float values — they are converted to Q16 internally.

        Parameters
        ----------
        kp : float or None
            Proportional gain. Default 100.0 in firmware.
        ki : float or None
            Integral gain. Default 0.05 in firmware.
        kd : float or None
            Derivative gain. Default 8.0 in firmware.
        ram_only : bool
            If True, updates the active parameters in RAM but skips saving to Flash.
            Useful for rapid updates during tuning to prevent flash degradation.

        Note
        ----
        All three gains are written together as a group. Pass all three values
        to avoid overwriting one with zero. If None is passed for a gain, the
        firmware's default value is used.
        """
        if kp is None:
            kp = 100.0
        if ki is None:
            ki = 0.05
        if kd is None:
            kd = 8.0

        p = self._blank_params()
        mask = _MASK_PID
        if ram_only:
            mask |= _MASK_RAM_ONLY
            
        struct.pack_into('<i', p, 9,  _float_to_q16(kp))
        struct.pack_into('<i', p, 13, _float_to_q16(ki))
        struct.pack_into('<i', p, 17, _float_to_q16(kd))
        return self._send_config(mask, bytes(p))

    def set_calibration(self, zero_adc, adc_per_360):
        """
        Set the physical ADC calibration.

        Parameters
        ----------
        zero_adc : int
            Raw ADC value corresponding to 0 degrees.
        adc_per_360 : int
            Number of ADC ticks for 360 degree rotation.
        """
        p = self._blank_params()
        struct.pack_into('<hh', p, 21, int(zero_adc), int(adc_per_360))
        return self._send_config(_MASK_HARD_CAL, bytes(p))

    def configure(self, servo_id=None, direction_invert=None,
                  min_angle=None, max_angle=None,
                  max_velocity=None, current_limit=None,
                  kp=None, ki=None, kd=None,
                  zero_adc=None, adc_per_360=None, ram_only=False):
        """
        Update multiple configuration fields in a single CONFIG packet.
        Only the provided (non-None) fields are written; all others are
        left untouched on the servo.

        Parameters
        ----------
        servo_id : int or None
            New bus address (0–127).
        direction_invert : bool or None
            Invert motor direction.
        min_angle, max_angle : int or None
            Software angle limits (degrees).
        max_velocity : int or None
            Default velocity (deg/s).
        current_limit : int or None
            Over-current threshold (mA).
        kp, ki, kd : float or None
            PID gains (written as a group; provide all three or use set_pid).
        hard_min, hard_max : int or None
            Physical calibration angles (written as a group).
        hard_min_adc, hard_max_adc : int or None
            Physical calibration ADC limits (written as a group).
        ram_only : bool
            If True, skip writing changes to Flash memory.

        Returns
        -------
        ServoStatus or None
        """
        mask = 0
        p = self._blank_params()

        # Bit 0 — ID / Direction
        if servo_id is not None or direction_invert is not None:
            mask |= _MASK_ID_DIR
            sid = (servo_id if servo_id is not None else self._id) & 0x7F
            d_inv = 1 if direction_invert else 0
            p[0] = sid | (d_inv << 7)

        # Bit 1 — Angle limits (must provide both)
        if min_angle is not None and max_angle is not None:
            mask |= _MASK_ANGLE_LIM
            struct.pack_into('<HH', p, 1, int(min_angle), int(max_angle))

        # Bit 2 — Velocity
        if max_velocity is not None:
            mask |= _MASK_VELOCITY
            struct.pack_into('<H', p, 5, int(max_velocity))

        # Bit 3 — Current limit
        if current_limit is not None:
            mask |= _MASK_CURRENT
            struct.pack_into('<H', p, 7, int(current_limit))

        # Bit 4 — PID (must provide all three)
        if kp is not None or ki is not None or kd is not None:
            mask |= _MASK_PID
            struct.pack_into('<i', p, 9,  _float_to_q16(kp if kp is not None else 100.0))
            struct.pack_into('<i', p, 13, _float_to_q16(ki if ki is not None else 0.05))
            struct.pack_into('<i', p, 17, _float_to_q16(kd if kd is not None else 8.0))

        # Bit 5 — Calibration (must provide both)
        if zero_adc is not None and adc_per_360 is not None:
            mask |= _MASK_HARD_CAL
            struct.pack_into('<hh', p, 21, int(zero_adc), int(adc_per_360))
            
        if ram_only:
            mask |= _MASK_RAM_ONLY

        if mask == 0 or mask == _MASK_RAM_ONLY:
            return None  # Nothing to update

        return self._send_config(mask, bytes(p))

    # Convenience functions

    def is_moving(self):
        """Poll and return True if the servo reports it is still moving."""
        status = self.poll()
        if status is None:
            return False
        return status.is_moving

    def wait_until_done(self, timeout_ms=10000, poll_interval_ms=50):
        """
        Block until the servo reports it has finished moving, or timeout.

        Returns the final ServoStatus, or None on timeout.
        """
        deadline = time.ticks_add(time.ticks_ms(), timeout_ms)
        while time.ticks_diff(deadline, time.ticks_ms()) > 0:
            status = self.poll()
            if status is not None and not status.is_moving:
                return status
            time.sleep_ms(poll_interval_ms)
        return None

    def move_and_wait(self, angle, velocity=0, timeout_ms=10000):
        """
        Send a move command and block until the servo reaches the target.

        Returns the final ServoStatus, or None on timeout.
        """
        self.move(angle, velocity)
        return self.wait_until_done(timeout_ms=timeout_ms)

    def __repr__(self):
        return '<Servo id={}>'.format(self._id)
