/**
 * @file Microdrive.cpp
 * @brief Implementation of the Microdrive Arduino/ESP32 driver.
 *
 * Protocol-compatible with the MM32 firmware and the MicroPython microdrive.py driver.
 * No firmware changes required — uses the same binary packet format, instruction set,
 * CONFIG bitmask layout, and Q16 fixed-point PID encoding.
 */

#include "Microdrive.h"
#include <string.h>

// ─── Protocol Instruction Codes ─────────────────────────────────────────────

static const uint8_t INST_CONTROL     = 0x01;
static const uint8_t INST_CONFIG      = 0x02;
static const uint8_t INST_POLL        = 0x03;
static const uint8_t INST_CLEAR_ERR   = 0x04;
static const uint8_t INST_READ_CONFIG = 0x05;

// CONFIG update mask bits
static const uint8_t MASK_ID_DIR    = 1 << 0;
static const uint8_t MASK_ANGLE_LIM = 1 << 1;
static const uint8_t MASK_VELOCITY  = 1 << 2;
static const uint8_t MASK_CURRENT   = 1 << 3;
static const uint8_t MASK_PID       = 1 << 4;
static const uint8_t MASK_HARD_CAL  = 1 << 5;
static const uint8_t MASK_RAM_ONLY  = 1 << 6;

// ─── Low-level Packet Helpers ───────────────────────────────────────────────

/**
 * Compute protocol checksum: ~(sum of bytes) & 0xFF.
 */
static uint8_t computeChecksum(const uint8_t* data, uint8_t len) {
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++) {
        sum += data[i];
    }
    return ~sum;
}

/**
 * Assemble a complete protocol packet into buf.
 * Returns the total packet length (header + body + checksum).
 *
 * Layout: [0xFF] [0xFF] [id] [length] [instruction] [params...] [checksum]
 */
static uint8_t buildPacket(uint8_t* buf, uint8_t servoId,
                           uint8_t instruction,
                           const uint8_t* params = nullptr,
                           uint8_t paramLen = 0) {
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = servoId;
    buf[3] = 1 + paramLen + 1;  // instruction + params + checksum
    buf[4] = instruction;

    if (paramLen > 0 && params != nullptr) {
        memcpy(&buf[5], params, paramLen);
    }

    // Checksum covers bytes [2..end-1] (id, length, instruction, params)
    uint8_t chk = computeChecksum(&buf[2], 3 + paramLen);
    buf[5 + paramLen] = chk;

    return 6 + paramLen;
}

/**
 * Parse an 11-byte status reply packet into a ServoStatus struct.
 * Returns true if the packet is valid (correct header, length field, checksum).
 */
static bool parseStatusReply(const uint8_t* raw, ServoStatus& status) {
    if (raw[0] != 0xFF || raw[1] != 0xFF) return false;
    if (raw[3] != 0x07) return false;

    // Verify checksum: bytes [2..9] -> checksum at byte [10]
    uint8_t expected = computeChecksum(&raw[2], 8);
    if (raw[10] != expected) return false;

    status.servo_id    = raw[2];
    status.instruction = raw[4];

    // Angle: signed 16-bit little-endian
    uint16_t rawAngle = raw[5] | ((uint16_t)raw[6] << 8);
    status.angle = (int16_t)rawAngle;

    // Current: unsigned 16-bit little-endian
    status.current_ma = raw[7] | ((uint16_t)raw[8] << 8);

    // Flags
    uint8_t flags = raw[9];
    status.is_moving   = (flags & 0x01) != 0;
    status.overcurrent = (flags & 0x02) != 0;
    status.is_holding  = (flags & 0x04) != 0;

    return true;
}

/**
 * Convert a float PID gain to Q16 fixed-point (signed int32).
 */
static int32_t floatToQ16(float value) {
    int64_t raw = (int64_t)(value * 65536.0f);
    if (raw > 0x7FFFFFFF)  raw = 0x7FFFFFFF;
    if (raw < -0x80000000LL) raw = -0x80000000LL;
    return (int32_t)raw;
}

/**
 * Convert a Q16 fixed-point int32 back to float.
 */
static float q16ToFloat(int32_t raw) {
    return (float)raw / 65536.0f;
}

/**
 * Parse a 36-byte configuration reply packet into a ServoConfigData struct.
 * Returns true if the packet is valid.
 */
static bool parseConfigReply(const uint8_t* raw, ServoConfigData& cfg) {
    if (raw[0] != 0xFF || raw[1] != 0xFF) return false;
    if (raw[3] != 32) return false;  // length: instruction(1) + params(30) + checksum(1)

    // Verify checksum: bytes [2..34] -> checksum at byte [35]
    uint8_t expected = computeChecksum(&raw[2], 33);
    if (raw[35] != expected) return false;

    // 30 parameter bytes starting at offset 5
    const uint8_t* p = &raw[5];

    cfg.servo_id         = p[0];
    cfg.direction_invert = (p[1] != 0);
    cfg.min_angle        = p[2]  | ((uint16_t)p[3]  << 8);
    cfg.max_angle        = p[4]  | ((uint16_t)p[5]  << 8);
    cfg.max_velocity     = p[6]  | ((uint16_t)p[7]  << 8);
    cfg.current_limit    = p[8]  | ((uint16_t)p[9]  << 8);

    int32_t kp_q16 = (int32_t)((uint32_t)p[10] | ((uint32_t)p[11] << 8) |
                                ((uint32_t)p[12] << 16) | ((uint32_t)p[13] << 24));
    int32_t ki_q16 = (int32_t)((uint32_t)p[14] | ((uint32_t)p[15] << 8) |
                                ((uint32_t)p[16] << 16) | ((uint32_t)p[17] << 24));
    int32_t kd_q16 = (int32_t)((uint32_t)p[18] | ((uint32_t)p[19] << 8) |
                                ((uint32_t)p[20] << 16) | ((uint32_t)p[21] << 24));

    cfg.kp = q16ToFloat(kp_q16);
    cfg.ki = q16ToFloat(ki_q16);
    cfg.kd = q16ToFloat(kd_q16);

    cfg.zero_adc    = (int16_t)(p[22] | ((uint16_t)p[23] << 8));
    cfg.adc_per_360 = (int16_t)(p[24] | ((uint16_t)p[25] << 8));
    cfg.magic       = (uint32_t)p[26] | ((uint32_t)p[27] << 8) |
                      ((uint32_t)p[28] << 16) | ((uint32_t)p[29] << 24);

    return true;
}

/**
 * Pack an unsigned 16-bit value as 2 little-endian bytes into dst.
 */
static inline void packU16LE(uint8_t* dst, uint16_t val) {
    dst[0] = (uint8_t)(val & 0xFF);
    dst[1] = (uint8_t)((val >> 8) & 0xFF);
}

/**
 * Pack a signed 32-bit value as 4 little-endian bytes into dst.
 */
static inline void packI32LE(uint8_t* dst, int32_t val) {
    uint32_t u = (uint32_t)val;
    dst[0] = (uint8_t)(u & 0xFF);
    dst[1] = (uint8_t)((u >> 8) & 0xFF);
    dst[2] = (uint8_t)((u >> 16) & 0xFF);
    dst[3] = (uint8_t)((u >> 24) & 0xFF);
}

/**
 * Pack a signed 16-bit value as 2 little-endian bytes into dst.
 */
static inline void packI16LE(uint8_t* dst, int16_t val) {
    uint16_t u = (uint16_t)val;
    dst[0] = (uint8_t)(u & 0xFF);
    dst[1] = (uint8_t)((u >> 8) & 0xFF);
}


// ═══════════════════════════════════════════════════════════════════════════
//  ServoBus Implementation
// ═══════════════════════════════════════════════════════════════════════════

ServoBus::ServoBus(Stream& serial, int8_t dirPin, uint8_t replyTimeoutMs)
    : _serial(serial), _dirPin(dirPin), _timeoutMs(replyTimeoutMs)
{
    if (_dirPin >= 0) {
        pinMode(_dirPin, OUTPUT);
        digitalWrite(_dirPin, LOW);  // Start in RX mode
    }
}

Servo ServoBus::servo(uint8_t servoId) {
    return Servo(*this, servoId);
}

// ── Direction Control ───────────────────────────────────────────────────────

void ServoBus::_txMode() {
    if (_dirPin >= 0) {
        digitalWrite(_dirPin, HIGH);
    }
}

void ServoBus::_rxMode() {
    if (_dirPin >= 0) {
        digitalWrite(_dirPin, LOW);
    }
}

void ServoBus::_flushRx() {
    while (_serial.available()) {
        _serial.read();
    }
}

// ── Raw TX / RX ─────────────────────────────────────────────────────────────

void ServoBus::_send(const uint8_t* packet, uint8_t len) {
    _flushRx();
    _txMode();
    _serial.write(packet, len);
    _serial.flush();  // Wait for all TX bytes to clock out
    _rxMode();
}

bool ServoBus::_receiveReply(uint8_t* outBuf, uint8_t expectedLen) {
    uint8_t buf[48];
    uint8_t bufLen = 0;
    unsigned long deadline = millis() + _timeoutMs;

    while ((long)(deadline - millis()) > 0) {
        if (_serial.available()) {
            int b = _serial.read();
            if (b >= 0 && bufLen < sizeof(buf)) {
                buf[bufLen++] = (uint8_t)b;
            }

            // Scan for a valid packet whenever we have enough bytes
            while (bufLen >= expectedLen) {
                // Find 0xFF 0xFF header
                uint8_t idx = 0;
                bool found = false;
                while (idx <= bufLen - 2) {
                    if (buf[idx] == 0xFF && buf[idx + 1] == 0xFF) {
                        found = true;
                        break;
                    }
                    idx++;
                }

                if (!found) {
                    // No header — keep a trailing 0xFF if present
                    if (bufLen > 0 && buf[bufLen - 1] == 0xFF) {
                        buf[0] = 0xFF;
                        bufLen = 1;
                    } else {
                        bufLen = 0;
                    }
                    break;
                }

                // Discard bytes before the header
                if (idx > 0) {
                    memmove(buf, buf + idx, bufLen - idx);
                    bufLen -= idx;
                }

                if (bufLen < expectedLen) break;  // Need more bytes

                // Verify checksum on candidate packet
                uint8_t sum = 0;
                for (uint8_t i = 2; i < expectedLen - 1; i++) {
                    sum += buf[i];
                }

                if (buf[expectedLen - 1] == (uint8_t)(~sum)) {
                    memcpy(outBuf, buf, expectedLen);
                    return true;
                }

                // Bad checksum — skip past this header and keep scanning
                memmove(buf, buf + 2, bufLen - 2);
                bufLen -= 2;
            }
        } else {
            delayMicroseconds(100);
        }
    }
    return false;
}

bool ServoBus::_transact(const uint8_t* packet, uint8_t packetLen,
                         bool expectReply, uint8_t* replyBuf,
                         uint8_t expectedReplyLen) {
    _send(packet, packetLen);

    if (!expectReply) return true;

    // On a single-wire half-duplex bus, every transmitted byte is echoed back
    // into the RX buffer. Drain the echo deterministically before scanning
    // for the servo's real reply.
    uint8_t remaining = packetLen;
    unsigned long deadline = millis() + _timeoutMs;
    while (remaining > 0 && (long)(deadline - millis()) > 0) {
        if (_serial.available()) {
            _serial.read();
            remaining--;
        } else {
            delayMicroseconds(50);
        }
    }

    return _receiveReply(replyBuf, expectedReplyLen);
}

// ── High-level Bus Commands ─────────────────────────────────────────────────

void ServoBus::broadcastMove(uint16_t angle, uint16_t velocity, uint16_t current) {
    uint8_t params[6];
    packU16LE(&params[0], angle);
    packU16LE(&params[2], velocity);
    packU16LE(&params[4], current);

    uint8_t pkt[14];
    uint8_t pktLen = buildPacket(pkt, MICRODRIVE_BROADCAST_ID, INST_CONTROL, params, 6);
    _transact(pkt, pktLen, false);
}

void ServoBus::broadcastClearError() {
    uint8_t params[1] = { 0x01 };
    uint8_t pkt[8];
    uint8_t pktLen = buildPacket(pkt, MICRODRIVE_BROADCAST_ID, INST_CLEAR_ERR, params, 1);
    _transact(pkt, pktLen, false);
}

void ServoBus::broadcastDisarm() {
    broadcastClearError();
}

uint8_t ServoBus::scan(ServoStatus* results, uint8_t maxResults,
                       uint8_t startId, uint8_t endId) {
    uint8_t count = 0;
    for (uint8_t sid = startId; sid <= endId && count < maxResults; sid++) {
        uint8_t pkt[8];
        uint8_t pktLen = buildPacket(pkt, sid, INST_POLL);

        uint8_t reply[MICRODRIVE_STATUS_REPLY_LEN];
        if (_transact(pkt, pktLen, true, reply, MICRODRIVE_STATUS_REPLY_LEN)) {
            ServoStatus st;
            if (parseStatusReply(reply, st)) {
                results[count++] = st;
            }
        }
    }
    return count;
}


// ═══════════════════════════════════════════════════════════════════════════
//  Servo Implementation
// ═══════════════════════════════════════════════════════════════════════════

Servo::Servo(ServoBus& bus, uint8_t servoId)
    : _bus(bus), _id(servoId) {}

// ── CONTROL (0x01) ──────────────────────────────────────────────────────────

void Servo::move(uint16_t angle, uint16_t velocity, uint16_t current) {
    uint8_t params[6];
    packU16LE(&params[0], angle);
    packU16LE(&params[2], velocity);
    packU16LE(&params[4], current);

    uint8_t pkt[14];
    uint8_t pktLen = buildPacket(pkt, _id, INST_CONTROL, params, 6);
    _bus._transact(pkt, pktLen, false);
}

// ── POLL_STATUS (0x03) ──────────────────────────────────────────────────────

bool Servo::poll(ServoStatus& status) {
    uint8_t pkt[8];
    uint8_t pktLen = buildPacket(pkt, _id, INST_POLL);

    uint8_t reply[MICRODRIVE_STATUS_REPLY_LEN];
    if (_bus._transact(pkt, pktLen, true, reply, MICRODRIVE_STATUS_REPLY_LEN)) {
        return parseStatusReply(reply, status);
    }
    return false;
}

// ── CLEAR_ERROR (0x04) ──────────────────────────────────────────────────────

void Servo::clearError() {
    uint8_t params[1] = { 0x01 };
    uint8_t pkt[8];
    uint8_t pktLen = buildPacket(pkt, _id, INST_CLEAR_ERR, params, 1);
    _bus._transact(pkt, pktLen, false);
}

void Servo::disarm() {
    clearError();
}

// ── READ_CONFIG (0x05) ──────────────────────────────────────────────────────

bool Servo::readConfig(ServoConfigData& config) {
    uint8_t pkt[8];
    uint8_t pktLen = buildPacket(pkt, _id, INST_READ_CONFIG);

    uint8_t reply[MICRODRIVE_CONFIG_REPLY_LEN];
    if (_bus._transact(pkt, pktLen, true, reply, MICRODRIVE_CONFIG_REPLY_LEN)) {
        return parseConfigReply(reply, config);
    }
    return false;
}

// ── CONFIG (0x02) — Internal Helper ─────────────────────────────────────────

bool Servo::_sendConfig(uint8_t mask, const uint8_t* params25, ServoStatus* status) {
    // Build full parameter payload: [mask] + [25 param bytes]
    uint8_t fullParams[26];
    fullParams[0] = mask;
    memcpy(&fullParams[1], params25, 25);

    uint8_t pkt[34];  // header(2) + id(1) + len(1) + inst(1) + params(26) + chk(1) = 32
    uint8_t pktLen = buildPacket(pkt, _id, INST_CONFIG, fullParams, 26);

    if (_id == MICRODRIVE_BROADCAST_ID) {
        _bus._transact(pkt, pktLen, false);
        return false;
    }

    uint8_t reply[MICRODRIVE_STATUS_REPLY_LEN];
    bool ok = _bus._transact(pkt, pktLen, true, reply, MICRODRIVE_STATUS_REPLY_LEN);
    if (ok && status != nullptr) {
        parseStatusReply(reply, *status);
    }
    return ok;
}

// ── CONFIG (0x02) — Individual Setters ──────────────────────────────────────

bool Servo::setId(uint8_t newId, bool directionInvert, ServoStatus* status) {
    uint8_t p[25] = {0};
    p[0] = (newId & 0x7F) | (directionInvert ? 0x80 : 0x00);
    return _sendConfig(MASK_ID_DIR, p, status);
}

bool Servo::setAngleLimits(uint16_t minAngle, uint16_t maxAngle, ServoStatus* status) {
    uint8_t p[25] = {0};
    packU16LE(&p[1], minAngle);
    packU16LE(&p[3], maxAngle);
    return _sendConfig(MASK_ANGLE_LIM, p, status);
}

bool Servo::setVelocity(uint16_t maxVelocity, ServoStatus* status) {
    uint8_t p[25] = {0};
    packU16LE(&p[5], maxVelocity);
    return _sendConfig(MASK_VELOCITY, p, status);
}

bool Servo::setCurrentLimit(uint16_t currentLimit, ServoStatus* status) {
    uint8_t p[25] = {0};
    packU16LE(&p[7], currentLimit);
    return _sendConfig(MASK_CURRENT, p, status);
}

bool Servo::setPid(float kp, float ki, float kd, bool ramOnly, ServoStatus* status) {
    uint8_t p[25] = {0};
    uint8_t mask = MASK_PID;
    if (ramOnly) mask |= MASK_RAM_ONLY;

    packI32LE(&p[9],  floatToQ16(kp));
    packI32LE(&p[13], floatToQ16(ki));
    packI32LE(&p[17], floatToQ16(kd));
    return _sendConfig(mask, p, status);
}

bool Servo::setCalibration(int16_t zeroAdc, int16_t adcPer360, ServoStatus* status) {
    uint8_t p[25] = {0};
    packI16LE(&p[21], zeroAdc);
    packI16LE(&p[23], adcPer360);
    return _sendConfig(MASK_HARD_CAL, p, status);
}

// ── CONFIG (0x02) — Multi-field Update ──────────────────────────────────────

bool Servo::configure(int16_t  servoId,
                      int8_t   directionInvert,
                      int32_t  minAngle,
                      int32_t  maxAngle,
                      int32_t  maxVelocity,
                      int32_t  currentLimit,
                      float    kp,
                      float    ki,
                      float    kd,
                      int32_t  zeroAdc,
                      int32_t  adcPer360,
                      bool     ramOnly,
                      ServoStatus* status) {
    uint8_t mask = 0;
    uint8_t p[25] = {0};

    // Bit 0 — ID / Direction
    if (servoId >= 0 || directionInvert >= 0) {
        mask |= MASK_ID_DIR;
        uint8_t sid = (servoId >= 0) ? ((uint8_t)servoId & 0x7F) : (_id & 0x7F);
        uint8_t dInv = (directionInvert > 0) ? 1 : 0;
        p[0] = sid | (dInv << 7);
    }

    // Bit 1 — Angle limits (both must be provided)
    if (minAngle >= 0 && maxAngle >= 0) {
        mask |= MASK_ANGLE_LIM;
        packU16LE(&p[1], (uint16_t)minAngle);
        packU16LE(&p[3], (uint16_t)maxAngle);
    }

    // Bit 2 — Velocity
    if (maxVelocity >= 0) {
        mask |= MASK_VELOCITY;
        packU16LE(&p[5], (uint16_t)maxVelocity);
    }

    // Bit 3 — Current limit
    if (currentLimit >= 0) {
        mask |= MASK_CURRENT;
        packU16LE(&p[7], (uint16_t)currentLimit);
    }

    // Bit 4 — PID (if any gain is provided, all three are written)
    if (!isnan(kp) || !isnan(ki) || !isnan(kd)) {
        mask |= MASK_PID;
        packI32LE(&p[9],  floatToQ16(isnan(kp) ? 100.0f : kp));
        packI32LE(&p[13], floatToQ16(isnan(ki) ? 0.05f  : ki));
        packI32LE(&p[17], floatToQ16(isnan(kd) ? 8.0f   : kd));
    }

    // Bit 5 — Calibration (both must be provided)
    if (zeroAdc != INT32_MIN && adcPer360 != INT32_MIN) {
        mask |= MASK_HARD_CAL;
        packI16LE(&p[21], (int16_t)zeroAdc);
        packI16LE(&p[23], (int16_t)adcPer360);
    }

    // Bit 6 — RAM-only flag
    if (ramOnly) {
        mask |= MASK_RAM_ONLY;
    }

    // Nothing to update?
    if (mask == 0 || mask == MASK_RAM_ONLY) {
        return false;
    }

    return _sendConfig(mask, p, status);
}

// ── Convenience Methods ─────────────────────────────────────────────────────

bool Servo::isMoving() {
    ServoStatus st;
    if (!poll(st)) return false;
    return st.is_moving;
}

bool Servo::waitUntilDone(uint32_t timeoutMs, uint32_t pollIntervalMs,
                          ServoStatus* finalStatus) {
    unsigned long deadline = millis() + timeoutMs;
    while ((long)(deadline - millis()) > 0) {
        ServoStatus st;
        if (poll(st) && !st.is_moving) {
            if (finalStatus) *finalStatus = st;
            return true;
        }
        delay(pollIntervalMs);
    }
    return false;
}

bool Servo::moveAndWait(uint16_t angle, uint16_t velocity,
                        uint32_t timeoutMs, ServoStatus* finalStatus) {
    move(angle, velocity);
    return waitUntilDone(timeoutMs, 50, finalStatus);
}
