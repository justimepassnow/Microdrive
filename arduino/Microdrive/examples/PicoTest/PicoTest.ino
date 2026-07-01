/**
 * PicoTest.ino — Test Microdrive library on Raspberry Pi Pico
 *
 * Board: Raspberry Pi Pico (Arduino Mbed OS RP2040 core)
 * 
 * Wiring:
 *   GP4 (UART1 TX) → Servo bus data line
 *   GP5 (UART1 RX) → Servo bus data line (same wire for single-wire mode)
 *   VBUS (5V)      → Servo VCC
 *   GND            → Servo GND
 *
 * Serial Monitor on USB (Serial) at 115200 for debug output.
 * Servo communication on UART1 (GP4/GP5) at 250000 baud.
 */

#include <Microdrive.h>

// ─── Pico UART Setup ────────────────────────────────────────────────────────
// Serial  = USB CDC (debug/monitor)
// servoSerial = UART1 on GP4 (TX) / GP5 (RX) → servo bus

UART servoSerial(digitalPinToPinName(4), digitalPinToPinName(5), NC, NC);

ServoBus bus(servoSerial, -1);  // No direction pin needed for single-wire
Servo myServo = bus.servo(1);   // Servo ID 1 (found by bus scan)

// ─── Setup ──────────────────────────────────────────────────────────────────

void setup() {
    // USB serial for debug output
    Serial.begin(115200);
    delay(2000);  // Wait for USB serial to enumerate
    Serial.println("\n=== Microdrive Pico Test ===\n");

    // Servo bus UART1 at 250000 baud on GP4 (TX) / GP5 (RX)
    servoSerial.begin(250000);

    // ── Test 1: Bus Scan ────────────────────────────────────────────────
    Serial.println("[TEST 1] Scanning bus for servos (ID 0-5)...");
    ServoStatus results[8];
    uint8_t found = bus.scan(results, 8, 0, 5);

    if (found == 0) {
        Serial.println("  No servos found! Check wiring and power.");
        Serial.println("  Continuing anyway — some tests will fail.\n");
    } else {
        for (uint8_t i = 0; i < found; i++) {
            Serial.print("  Found servo ID ");
            Serial.print(results[i].servo_id);
            Serial.print(" at ");
            Serial.print(results[i].angle);
            Serial.println(" deg");
        }
        Serial.println();
    }

    // ── Test 2: Poll Status ─────────────────────────────────────────────
    Serial.println("[TEST 2] Polling servo 0 status...");
    ServoStatus status;
    if (myServo.poll(status)) {
        Serial.print("  Angle:   "); Serial.print(status.angle); Serial.println(" deg");
        Serial.print("  Current: "); Serial.print(status.current_ma); Serial.println(" mA");
        Serial.print("  Moving:  "); Serial.println(status.is_moving ? "YES" : "NO");
        Serial.print("  Fault:   "); Serial.println(status.hasFault() ? "YES" : "NO");
    } else {
        Serial.println("  No response (timeout).");
    }
    Serial.println();

    // ── Test 3: Read Config ─────────────────────────────────────────────
    Serial.println("[TEST 3] Reading servo configuration...");
    ServoConfigData cfg;
    if (myServo.readConfig(cfg)) {
        Serial.print("  ID:           "); Serial.println(cfg.servo_id);
        Serial.print("  Dir Invert:   "); Serial.println(cfg.direction_invert ? "YES" : "NO");
        Serial.print("  Angle Range:  "); Serial.print(cfg.min_angle);
        Serial.print("-");                Serial.print(cfg.max_angle); Serial.println(" deg");
        Serial.print("  Max Velocity: "); Serial.print(cfg.max_velocity); Serial.println(" deg/s");
        Serial.print("  Current Lim:  "); Serial.print(cfg.current_limit); Serial.println(" mA");
        Serial.print("  Kp:           "); Serial.println(cfg.kp, 2);
        Serial.print("  Ki:           "); Serial.println(cfg.ki, 4);
        Serial.print("  Kd:           "); Serial.println(cfg.kd, 2);
        Serial.print("  Magic:        0x"); Serial.println(cfg.magic, HEX);
    } else {
        Serial.println("  No response (timeout).");
    }
    Serial.println();

    // ── Test 4: Move Servo ──────────────────────────────────────────────
    Serial.println("[TEST 4] Moving to 90 deg at 200 deg/s...");
    myServo.move(90, 200);
    delay(1500);

    if (myServo.poll(status)) {
        Serial.print("  Arrived at: "); Serial.print(status.angle); Serial.println(" deg");
    }
    Serial.println();

    // ── Test 5: Move and Wait ───────────────────────────────────────────
    Serial.println("[TEST 5] moveAndWait to 180 deg...");
    ServoStatus finalStatus;
    if (myServo.moveAndWait(180, 150, 5000, &finalStatus)) {
        Serial.print("  Done! Final angle: "); Serial.print(finalStatus.angle); Serial.println(" deg");
    } else {
        Serial.println("  Timeout waiting for servo.");
    }
    Serial.println();

    // ── Test 6: Move back ───────────────────────────────────────────────
    Serial.println("[TEST 6] Moving back to 0 deg...");
    myServo.move(0, 200);
    delay(2000);

    if (myServo.poll(status)) {
        Serial.print("  Final angle: "); Serial.print(status.angle); Serial.println(" deg");
    }
    Serial.println();

    Serial.println("=== All tests complete! ===");
}

// ─── Loop ───────────────────────────────────────────────────────────────────

void loop() {
    // Continuous polling every 2 seconds
    ServoStatus status;
    if (myServo.poll(status)) {
        Serial.print("[POLL] angle=");
        Serial.print(status.angle);
        Serial.print(" deg, current=");
        Serial.print(status.current_ma);
        Serial.print("mA");
        if (status.is_moving)   Serial.print(" MOVING");
        if (status.is_holding)  Serial.print(" HOLDING");
        if (status.overcurrent) Serial.print(" FAULT");
        Serial.println();
    }
    delay(2000);
}
