/**
 * @file Microdrive.h
 * @brief Arduino/ESP32 driver for Microdrive (MM32 firmware)
 *
 * Communicates over a half-duplex single-wire UART bus at 250000 baud.
 * Protocol: binary packets with 0xFF 0xFF header, ID, length, instruction,
 * parameters (little-endian), and inverted-sum checksum.
 *
 * Supports daisy-chained servos on the same bus, each addressed by a unique ID.
 *
 * Usage (ESP32):
 *   #include <Microdrive.h>
 *
 *   HardwareSerial servoSerial(1);
 *   ServoBus bus(servoSerial);
 *
 *   void setup() {
 *       servoSerial.begin(250000, SERIAL_8N1, RX_PIN, TX_PIN);
 *       Servo servo = bus.servo(0);
 *       servo.move(180, 200);
 *   }
 *
 * Usage (Arduino with direction pin for RS-485 style half-duplex):
 *   #include <Microdrive.h>
 *
 *   ServoBus bus(Serial1, 4);  // dir_pin = 4
 *   Servo servo = bus.servo(0);
 */

#ifndef MICRODRIVE_H
#define MICRODRIVE_H

#include <Arduino.h>
#include <math.h>

// ─── Protocol Constants ─────────────────────────────────────────────────────

#define MICRODRIVE_BROADCAST_ID       0xFE
#define MICRODRIVE_STATUS_REPLY_LEN   11
#define MICRODRIVE_CONFIG_REPLY_LEN   36
#define MICRODRIVE_DEFAULT_TIMEOUT_MS 8

// Forward declarations
class ServoBus;

// ─── Status Reply Container ─────────────────────────────────────────────────

/**
 * @brief Parsed status reply from the servo.
 */
struct ServoStatus {
    uint8_t  servo_id;      ///< Servo bus address
    uint8_t  instruction;   ///< Echoed instruction code
    int16_t  angle;         ///< Current angle in degrees (signed)
    uint16_t current_ma;    ///< Current draw in milliamps
    bool     is_moving;     ///< True if servo is actively moving
    bool     overcurrent;   ///< True if overcurrent fault is active
    bool     is_holding;    ///< True if servo is in admittance/yield mode

    /** @return True if any fault flag is active. */
    bool hasFault() const { return overcurrent; }
};

// ─── Config Reply Container ─────────────────────────────────────────────────

/**
 * @brief Parsed configuration stored in the servo's flash memory.
 */
struct ServoConfigData {
    uint8_t  servo_id;          ///< Servo bus address (0-127)
    bool     direction_invert;  ///< True if motor direction is inverted
    uint16_t min_angle;         ///< Minimum allowable target angle (degrees)
    uint16_t max_angle;         ///< Maximum allowable target angle (degrees)
    uint16_t max_velocity;      ///< Default velocity limit (deg/s)
    uint16_t current_limit;     ///< Over-current fault threshold (mA)
    float    kp;                ///< PID proportional gain
    float    ki;                ///< PID integral gain
    float    kd;                ///< PID derivative gain
    int16_t  zero_adc;          ///< Raw ADC value at 0 degrees
    int16_t  adc_per_360;       ///< ADC ticks per 360 degrees
    uint32_t magic;             ///< Flash magic word (should be 0xDEADBEEF)
};

// ─── Servo Handle ───────────────────────────────────────────────────────────

/**
 * @brief High-level interface to a single Microdrive servo on the bus.
 *
 * Created via bus.servo(id) — lightweight value type holding a reference
 * to the parent ServoBus. The ServoBus must outlive any Servo handles.
 */
class Servo {
public:
    Servo(ServoBus& bus, uint8_t servoId);

    /** @return This servo's bus address. */
    uint8_t id() const { return _id; }

    // ── CONTROL (0x01) ──────────────────────────────────────────────────

    /**
     * @brief Command the servo to move to a target angle.
     *
     * No reply is expected — fire-and-forget for fast control loops.
     *
     * @param angle    Target angle in degrees (clamped by servo's config limits).
     * @param velocity Temporary speed in deg/s. 0 = use servo's flash default.
     * @param current  Temporary force/current limit in mA. 0 = use flash default.
     */
    void move(uint16_t angle, uint16_t velocity = 0, uint16_t current = 0);

    // ── POLL_STATUS (0x03) ──────────────────────────────────────────────

    /**
     * @brief Request the servo's current status without changing anything.
     *
     * @param[out] status Filled with current angle, current draw, and flags.
     * @return True if a valid reply was received, false on timeout.
     */
    bool poll(ServoStatus& status);

    // ── CLEAR_ERROR (0x04) ──────────────────────────────────────────────

    /**
     * @brief Clear overcurrent fault, reset PID, lock target to current position.
     */
    void clearError();

    /**
     * @brief Disarm motor H-bridge so shaft spins freely.
     *        Re-arms automatically on next move() command.
     */
    void disarm();

    // ── READ_CONFIG (0x05) ──────────────────────────────────────────────

    /**
     * @brief Read the servo's full persistent configuration from flash.
     *
     * @param[out] config Filled with parsed config data.
     * @return True if a valid reply was received, false on timeout.
     */
    bool readConfig(ServoConfigData& config);

    // ── CONFIG (0x02) — Individual Setters ──────────────────────────────

    /**
     * @brief Change the servo's bus address and/or motor direction.
     * @note  After changing the ID, create a new bus.servo(newId) handle.
     */
    bool setId(uint8_t newId, bool directionInvert = false, ServoStatus* status = nullptr);

    /** @brief Set software-enforced angle limits (degrees). */
    bool setAngleLimits(uint16_t minAngle, uint16_t maxAngle, ServoStatus* status = nullptr);

    /** @brief Set the flash-stored default velocity limit (deg/s). */
    bool setVelocity(uint16_t maxVelocity, ServoStatus* status = nullptr);

    /** @brief Set the over-current fault threshold (mA). */
    bool setCurrentLimit(uint16_t currentLimit, ServoStatus* status = nullptr);

    /**
     * @brief Set PID gains. Accepts float values (converted to Q16 internally).
     * @param kp      Proportional gain (firmware default: 100.0).
     * @param ki      Integral gain (firmware default: 0.05).
     * @param kd      Derivative gain (firmware default: 8.0).
     * @param ramOnly If true, skip saving to flash (useful during rapid tuning).
     */
    bool setPid(float kp = 100.0f, float ki = 0.05f, float kd = 8.0f,
                bool ramOnly = false, ServoStatus* status = nullptr);

    /**
     * @brief Set the physical ADC calibration.
     * @param zeroAdc   Raw ADC value at 0 degrees.
     * @param adcPer360 ADC ticks per 360 degree rotation.
     */
    bool setCalibration(int16_t zeroAdc, int16_t adcPer360, ServoStatus* status = nullptr);

    /**
     * @brief Update multiple configuration fields in a single CONFIG packet.
     *
     * Only non-sentinel values are written. Pass -1 for integer fields you
     * don't want to change, NAN for float fields, and INT32_MIN for
     * signed calibration fields.
     *
     * @return True if a valid status reply was received, false on timeout or nothing to update.
     */
    bool configure(int16_t  servoId         = -1,
                   int8_t   directionInvert = -1,
                   int32_t  minAngle        = -1,
                   int32_t  maxAngle        = -1,
                   int32_t  maxVelocity     = -1,
                   int32_t  currentLimit    = -1,
                   float    kp              = NAN,
                   float    ki              = NAN,
                   float    kd              = NAN,
                   int32_t  zeroAdc         = INT32_MIN,
                   int32_t  adcPer360       = INT32_MIN,
                   bool     ramOnly         = false,
                   ServoStatus* status      = nullptr);

    // ── Convenience ─────────────────────────────────────────────────────

    /** @brief Poll and return true if the servo reports it is still moving. */
    bool isMoving();

    /**
     * @brief Block until the servo reports it has finished moving, or timeout.
     * @return True if servo reached target, false on timeout.
     */
    bool waitUntilDone(uint32_t timeoutMs = 10000, uint32_t pollIntervalMs = 50,
                       ServoStatus* finalStatus = nullptr);

    /**
     * @brief Send a move command and block until the servo reaches the target.
     * @return True if servo reached target, false on timeout.
     */
    bool moveAndWait(uint16_t angle, uint16_t velocity = 0,
                     uint32_t timeoutMs = 10000, ServoStatus* finalStatus = nullptr);

private:
    ServoBus& _bus;
    uint8_t   _id;

    bool _sendConfig(uint8_t mask, const uint8_t* params25, ServoStatus* status);
};

// ─── Servo Bus ──────────────────────────────────────────────────────────────

/**
 * @brief Manages the shared half-duplex UART bus for one or more Microdrives.
 *
 * @param serial          Pre-configured Stream (e.g. HardwareSerial) at 250000 baud, 8N1.
 * @param dirPin          Optional direction control pin (HIGH = transmit). Pass -1 if unused.
 * @param replyTimeoutMs  Milliseconds to wait for a servo reply before giving up.
 */
class ServoBus {
    friend class Servo;

public:
    ServoBus(Stream& serial, int8_t dirPin = -1,
             uint8_t replyTimeoutMs = MICRODRIVE_DEFAULT_TIMEOUT_MS);

    /**
     * @brief Create a lightweight Servo handle bound to this bus.
     * @param servoId The servo's bus address (0–127). ID 0 targets unconfigured servos.
     */
    Servo servo(uint8_t servoId);

    /**
     * @brief Move all servos on the bus simultaneously (no reply).
     */
    void broadcastMove(uint16_t angle, uint16_t velocity = 0, uint16_t current = 0);

    /** @brief Clear faults on all servos (no reply). */
    void broadcastClearError();

    /** @brief Disarm all servos, turning off H-bridges (no reply). */
    void broadcastDisarm();

    /**
     * @brief Scan the bus for connected servos by polling each ID.
     *
     * @warning Slow — each non-responding ID waits for the full timeout.
     *          Narrow the range if you know the expected IDs.
     *
     * @param[out] results   Array to fill with found servo statuses.
     * @param      maxResults Maximum number of results to store.
     * @param      startId   First ID to scan (inclusive).
     * @param      endId     Last ID to scan (inclusive).
     * @return Number of servos found.
     */
    uint8_t scan(ServoStatus* results, uint8_t maxResults,
                 uint8_t startId = 0, uint8_t endId = 127);

private:
    Stream&  _serial;
    int8_t   _dirPin;
    uint8_t  _timeoutMs;

    void _txMode();
    void _rxMode();
    void _flushRx();
    void _send(const uint8_t* packet, uint8_t len);
    bool _receiveReply(uint8_t* outBuf, uint8_t expectedLen);
    bool _transact(const uint8_t* packet, uint8_t packetLen,
                   bool expectReply, uint8_t* replyBuf = nullptr,
                   uint8_t expectedReplyLen = 0);
};

#endif // MICRODRIVE_H
