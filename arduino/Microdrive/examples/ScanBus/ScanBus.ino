/**
 * ScanBus.ino — Scan the Microdrive bus for connected servos
 *
 * Polls every ID from 0-127 and prints the status of each responding servo.
 * Useful for discovering servo IDs and verifying wiring.
 *
 * NOTE: This is slow (~1 second per non-responding ID due to timeout).
 *       If you know your servo IDs, narrow the scan range.
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

// ─── Setup ──────────────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    while (!Serial) { ; }

#if defined(ESP32)
    servoSerial.begin(250000, SERIAL_8N1, RX_PIN, TX_PIN);
#else
    servoSerial.begin(250000);
#endif

    Serial.println("Microdrive Bus Scanner");
    Serial.println("======================");
    Serial.println("Scanning IDs 0-10 (modify range for full scan)...\n");

    // Scan a limited range for speed. Change to 0-127 for full scan.
    ServoStatus results[16];
    uint8_t found = bus.scan(results, 16, 0, 10);

    if (found == 0) {
        Serial.println("No servos found! Check wiring and power.");
    } else {
        Serial.print("Found ");
        Serial.print(found);
        Serial.println(" servo(s):\n");

        for (uint8_t i = 0; i < found; i++) {
            Serial.print("  ID ");
            Serial.print(results[i].servo_id);
            Serial.print(": angle=");
            Serial.print(results[i].angle);
            Serial.print("° current=");
            Serial.print(results[i].current_ma);
            Serial.print("mA");

            if (results[i].is_moving)   Serial.print(" [MOVING]");
            if (results[i].is_holding)  Serial.print(" [HOLDING]");
            if (results[i].overcurrent) Serial.print(" [OVERCURRENT]");

            Serial.println();
        }
    }

    Serial.println("\nScan complete.");
}

void loop() {
    // Nothing to do — scan runs once in setup()
}
