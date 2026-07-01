/**
 * BasicMove.ino — Minimal Microdrive example
 *
 * Moves a servo back and forth between 0° and 180° with status polling.
 *
 * Wiring (ESP32):
 *   Servo bus data line → GPIO 16 (TX) and GPIO 17 (RX)
 *   Or single-wire: GPIO 16 for both (set RX_PIN = TX_PIN)
 *
 * Wiring (Arduino Mega):
 *   Servo bus data line → Serial1 TX/RX pins
 *   Direction pin (if using RS-485 transceiver) → Pin 4
 */

#include <Microdrive.h>

// ─── Configuration ──────────────────────────────────────────────────────────

// ESP32: Use UART1 with explicit pins
#if defined(ESP32)
  #define TX_PIN 16
  #define RX_PIN 17
  HardwareSerial servoSerial(1);
#else
  // Arduino Mega/Due: Use Serial1 (pins 18/19 on Mega)
  #define servoSerial Serial1
#endif

// Set to a valid GPIO pin if using a direction pin for half-duplex control,
// or -1 if wired single-wire (echo-draining handles it automatically).
#define DIR_PIN -1

// ─── Objects ────────────────────────────────────────────────────────────────

ServoBus bus(servoSerial, DIR_PIN);
Servo myServo = bus.servo(0);  // Servo at bus address 0

// ─── Setup ──────────────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    while (!Serial) { ; }  // Wait for serial monitor (USB boards)

#if defined(ESP32)
    servoSerial.begin(250000, SERIAL_8N1, RX_PIN, TX_PIN);
#else
    servoSerial.begin(250000);
#endif

    Serial.println("Microdrive BasicMove Example");
    Serial.println("----------------------------");

    // Poll to confirm the servo is online
    ServoStatus status;
    if (myServo.poll(status)) {
        Serial.print("Servo found! Current angle: ");
        Serial.print(status.angle);
        Serial.println(" deg");
    } else {
        Serial.println("WARNING: No servo response. Check wiring and ID.");
    }
}

// ─── Loop ───────────────────────────────────────────────────────────────────

void loop() {
    // Move to 180° at 200 deg/s
    Serial.println("Moving to 180 deg...");
    myServo.move(180, 200);

    delay(2000);

    // Poll status
    ServoStatus status;
    if (myServo.poll(status)) {
        Serial.print("  Angle: ");
        Serial.print(status.angle);
        Serial.print(" deg | Current: ");
        Serial.print(status.current_ma);
        Serial.print(" mA | Moving: ");
        Serial.println(status.is_moving ? "YES" : "NO");
    }

    delay(1000);

    // Move to 0° at 200 deg/s
    Serial.println("Moving to 0 deg...");
    myServo.move(0, 200);

    delay(2000);

    // Poll again
    if (myServo.poll(status)) {
        Serial.print("  Angle: ");
        Serial.print(status.angle);
        Serial.print(" deg | Current: ");
        Serial.print(status.current_ma);
        Serial.print(" mA | Moving: ");
        Serial.println(status.is_moving ? "YES" : "NO");
    }

    delay(1000);
}
