/**
 * ConfigServo.ino — Read and modify Microdrive servo configuration
 *
 * Demonstrates reading the servo's flash config, changing PID gains,
 * setting angle limits, and assigning a new servo ID.
 */

#include <Microdrive.h>

// ─── Configuration ──────────────────────────────────────────────────────────

#if defined(ESP32)
  #define TX_PIN 16
  #define RX_PIN 17
  HardwareSerial servoSerial(1);
#else
  #define servoSerial Serial1
#endif

#define DIR_PIN -1

// ─── Objects ────────────────────────────────────────────────────────────────

ServoBus bus(servoSerial, DIR_PIN);
Servo myServo = bus.servo(0);

// ─── Setup ──────────────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    while (!Serial) { ; }

#if defined(ESP32)
    servoSerial.begin(250000, SERIAL_8N1, RX_PIN, TX_PIN);
#else
    servoSerial.begin(250000);
#endif

    Serial.println("Microdrive Config Example");
    Serial.println("=========================\n");

    // ── 1. Read current configuration ───────────────────────────────────

    ServoConfigData cfg;
    if (myServo.readConfig(cfg)) {
        Serial.println("Current Configuration:");
        Serial.print("  ID:             "); Serial.println(cfg.servo_id);
        Serial.print("  Dir Invert:     "); Serial.println(cfg.direction_invert ? "YES" : "NO");
        Serial.print("  Angle Limits:   "); Serial.print(cfg.min_angle);
        Serial.print("° - ");              Serial.print(cfg.max_angle); Serial.println("°");
        Serial.print("  Max Velocity:   "); Serial.print(cfg.max_velocity); Serial.println(" deg/s");
        Serial.print("  Current Limit:  "); Serial.print(cfg.current_limit); Serial.println(" mA");
        Serial.print("  PID Kp:         "); Serial.println(cfg.kp, 2);
        Serial.print("  PID Ki:         "); Serial.println(cfg.ki, 4);
        Serial.print("  PID Kd:         "); Serial.println(cfg.kd, 2);
        Serial.print("  Zero ADC:       "); Serial.println(cfg.zero_adc);
        Serial.print("  ADC per 360°:   "); Serial.println(cfg.adc_per_360);
        Serial.print("  Magic:          0x"); Serial.println(cfg.magic, HEX);
    } else {
        Serial.println("ERROR: Could not read config. Check wiring.");
        return;
    }

    // ── 2. Set angle limits ─────────────────────────────────────────────

    Serial.println("\nSetting angle limits to 10° - 170°...");
    if (myServo.setAngleLimits(10, 170)) {
        Serial.println("  OK!");
    } else {
        Serial.println("  Failed (timeout).");
    }

    // ── 3. Tune PID gains (RAM only — won't wear flash) ────────────────

    Serial.println("Setting PID gains (RAM only): Kp=120, Ki=0.08, Kd=10...");
    if (myServo.setPid(120.0f, 0.08f, 10.0f, true)) {
        Serial.println("  OK (changes active in RAM, not saved to flash).");
    }

    // ── 4. Set velocity ─────────────────────────────────────────────────

    Serial.println("Setting default velocity to 300 deg/s...");
    myServo.setVelocity(300);

    // ── 5. Verify changes ───────────────────────────────────────────────

    Serial.println("\nRe-reading configuration...");
    if (myServo.readConfig(cfg)) {
        Serial.print("  Angle Limits:  "); Serial.print(cfg.min_angle);
        Serial.print("° - ");             Serial.print(cfg.max_angle); Serial.println("°");
        Serial.print("  Max Velocity:  "); Serial.print(cfg.max_velocity); Serial.println(" deg/s");
        Serial.print("  PID Kp:        "); Serial.println(cfg.kp, 2);
        Serial.print("  PID Ki:        "); Serial.println(cfg.ki, 4);
        Serial.print("  PID Kd:        "); Serial.println(cfg.kd, 2);
    }

    // ── 6. Multi-field configure example (commented out) ────────────────

    // Uncomment to change ID to 5 and set direction invert in one packet:
    // myServo.configure(
    //     5,     // servoId = 5
    //     1,     // directionInvert = true
    //     0,     // minAngle = 0
    //     270    // maxAngle = 270
    // );
    // // After changing ID, create a new handle:
    // Servo newServo = bus.servo(5);

    Serial.println("\nDone!");
}

void loop() {
    // Nothing — config is a one-time operation
}
