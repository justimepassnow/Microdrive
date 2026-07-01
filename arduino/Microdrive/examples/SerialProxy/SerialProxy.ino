/**
 * SerialProxy.ino — Arduino serial proxy for Microdrive GUI
 *
 * Drop-in replacement for micropython/serial_proxy.py
 * 
 * Bridges the GUI (JSON over USB serial) to the Microdrive servo bus (UART1).
 * The GUI sends JSON commands on USB, this sketch translates them to servo
 * bus commands and returns JSON responses — identical protocol to serial_proxy.py.
 *
 * Board: Raspberry Pi Pico (Arduino Mbed OS RP2040 core)
 * 
 * Wiring:
 *   GP4 (UART1 TX) → Servo bus data line
 *   GP5 (UART1 RX) → Servo bus data line
 *   VBUS (5V)      → Servo VCC
 *   GND            → Servo GND
 */

#include <Microdrive.h>

// ─── UART Setup ─────────────────────────────────────────────────────────────
UART servoSerial(digitalPinToPinName(4), digitalPinToPinName(5), NC, NC);
ServoBus bus(servoSerial, -1);

// ─── JSON Helpers ───────────────────────────────────────────────────────────
// Minimal JSON handling — no external library needed.

void sendLog(const char* msg) {
    Serial.print("{\"res\":\"log\",\"msg\":\"");
    Serial.print(msg);
    Serial.println("\"}");
}

void sendError(const char* msg) {
    Serial.print("{\"res\":\"error\",\"msg\":\"");
    Serial.print(msg);
    Serial.println("\"}");
}

void sendAck(const char* cmd) {
    Serial.print("{\"res\":\"ack\",\"cmd\":\"");
    Serial.print(cmd);
    Serial.println("\"}");
}

void sendAckWithId(const char* cmd, uint8_t id, uint8_t newId) {
    Serial.print("{\"res\":\"ack\",\"cmd\":\"");
    Serial.print(cmd);
    Serial.print("\",\"id\":");
    Serial.print(id);
    Serial.print(",\"new_id\":");
    Serial.print(newId);
    Serial.println("}");
}

void sendScanResult(ServoStatus* results, uint8_t count) {
    Serial.print("{\"res\":\"scan\",\"data\":[");
    for (uint8_t i = 0; i < count; i++) {
        if (i > 0) Serial.print(",");
        Serial.print(results[i].servo_id);
    }
    Serial.println("]}");
}

void sendPollResult(ServoStatus& s) {
    Serial.print("{\"res\":\"poll\",\"data\":{\"id\":");
    Serial.print(s.servo_id);
    Serial.print(",\"angle\":");
    Serial.print(s.angle);
    Serial.print(",\"current_ma\":");
    Serial.print(s.current_ma);
    Serial.print(",\"is_moving\":");
    Serial.print(s.is_moving ? "true" : "false");
    Serial.print(",\"is_holding\":");
    Serial.print(s.is_holding ? "true" : "false");
    Serial.print(",\"overcurrent\":");
    Serial.print(s.overcurrent ? "true" : "false");
    Serial.println("}}");
}

void sendConfigResult(ServoConfigData& c) {
    Serial.print("{\"res\":\"read_config\",\"data\":{\"servo_id\":");
    Serial.print(c.servo_id);
    Serial.print(",\"direction_invert\":");
    Serial.print(c.direction_invert ? "true" : "false");
    Serial.print(",\"min_angle\":");
    Serial.print(c.min_angle);
    Serial.print(",\"max_angle\":");
    Serial.print(c.max_angle);
    Serial.print(",\"max_velocity\":");
    Serial.print(c.max_velocity);
    Serial.print(",\"current_limit\":");
    Serial.print(c.current_limit);
    Serial.print(",\"kp\":");
    Serial.print(c.kp, 4);
    Serial.print(",\"ki\":");
    Serial.print(c.ki, 6);
    Serial.print(",\"kd\":");
    Serial.print(c.kd, 4);
    Serial.print(",\"zero_adc\":");
    Serial.print(c.zero_adc);
    Serial.print(",\"adc_per_360\":");
    Serial.print(c.adc_per_360);
    Serial.println("}}");
}

// ─── Minimal JSON Parser ────────────────────────────────────────────────────
// Extracts string/int/float values by key from a flat JSON object.
// No nested objects — matches the serial_proxy.py protocol exactly.

static char lineBuf[512];

// Find the value string for a given key in the JSON line.
// Returns pointer into lineBuf at the start of the value, or NULL if not found.
const char* jsonFindKey(const char* json, const char* key) {
    // Search for "key": pattern
    char pattern[64];
    snprintf(pattern, sizeof(pattern), "\"%s\"", key);
    const char* p = strstr(json, pattern);
    if (!p) return NULL;
    p += strlen(pattern);
    // Skip whitespace and colon
    while (*p == ' ' || *p == ':') p++;
    return p;
}

// Extract a string value (returns length, copies into out without quotes)
int jsonGetString(const char* json, const char* key, char* out, int maxLen) {
    const char* p = jsonFindKey(json, key);
    if (!p || *p != '"') return -1;
    p++; // skip opening quote
    int i = 0;
    while (*p && *p != '"' && i < maxLen - 1) {
        out[i++] = *p++;
    }
    out[i] = '\0';
    return i;
}

// Extract an integer value
int32_t jsonGetInt(const char* json, const char* key, int32_t defaultVal) {
    const char* p = jsonFindKey(json, key);
    if (!p) return defaultVal;
    if (*p == '"') return defaultVal; // it's a string, not int
    return atol(p);
}

// Extract a float value
float jsonGetFloat(const char* json, const char* key, float defaultVal) {
    const char* p = jsonFindKey(json, key);
    if (!p) return defaultVal;
    if (*p == '"') return defaultVal;
    // Check for null
    if (strncmp(p, "null", 4) == 0) return defaultVal;
    return atof(p);
}

// Check if a key exists and is not null
bool jsonHasKey(const char* json, const char* key) {
    const char* p = jsonFindKey(json, key);
    if (!p) return false;
    if (strncmp(p, "null", 4) == 0) return false;
    return true;
}

// Check for boolean true inside a nested "params" object
// This is a simplified approach: we find the "params" section first
const char* jsonFindParams(const char* json) {
    const char* p = strstr(json, "\"params\"");
    if (!p) return NULL;
    p += 8; // skip "params"
    while (*p == ' ' || *p == ':') p++;
    if (*p == '{') p++;
    return p;
}

// ─── Command Handler ────────────────────────────────────────────────────────

void handleCommand(const char* json) {
    char cmd[20];
    if (jsonGetString(json, "cmd", cmd, sizeof(cmd)) < 0) {
        sendError("Missing cmd");
        return;
    }

    uint8_t sid = (uint8_t)jsonGetInt(json, "id", 0);

    // ── scan ────────────────────────────────────────────────────────────
    if (strcmp(cmd, "scan") == 0) {
        ServoStatus results[128];
        uint8_t found = bus.scan(results, 128, 0, 127);
        sendScanResult(results, found);
    }
    // ── move ────────────────────────────────────────────────────────────
    else if (strcmp(cmd, "move") == 0) {
        uint16_t angle    = (uint16_t)jsonGetInt(json, "angle", 0);
        uint16_t velocity = (uint16_t)jsonGetInt(json, "velocity", 0);
        uint16_t current  = (uint16_t)jsonGetInt(json, "current", 0);
        bus.servo(sid).move(angle, velocity, current);
        sendAck("move");
    }
    // ── poll ────────────────────────────────────────────────────────────
    else if (strcmp(cmd, "poll") == 0) {
        ServoStatus status;
        if (bus.servo(sid).poll(status)) {
            sendPollResult(status);
        } else {
            char msg[48];
            snprintf(msg, sizeof(msg), "Poll Timeout for ID %d", sid);
            sendError(msg);
        }
    }
    // ── read_config ─────────────────────────────────────────────────────
    else if (strcmp(cmd, "read_config") == 0) {
        ServoConfigData cfg;
        if (bus.servo(sid).readConfig(cfg)) {
            sendConfigResult(cfg);
        } else {
            char msg[48];
            snprintf(msg, sizeof(msg), "Config Read Timeout for ID %d", sid);
            sendError(msg);
        }
    }
    // ── configure ───────────────────────────────────────────────────────
    else if (strcmp(cmd, "configure") == 0) {
        // Parse the nested "params" object
        const char* params = jsonFindParams(json);
        if (!params) {
            sendAckWithId("configure", sid, sid);
            return;
        }

        // Use the full json to find params.* keys
        // The configure() method uses sentinel values for "not provided"
        int16_t newServoId      = jsonHasKey(params, "servo_id")         ? (int16_t)jsonGetInt(params, "servo_id", -1)           : -1;
        int8_t  dirInvert       = jsonHasKey(params, "direction_invert") ? (int8_t)jsonGetInt(params, "direction_invert", -1)    : -1;
        int32_t minAngle        = jsonHasKey(params, "min_angle")        ? jsonGetInt(params, "min_angle", -1)                   : -1;
        int32_t maxAngle        = jsonHasKey(params, "max_angle")        ? jsonGetInt(params, "max_angle", -1)                   : -1;
        int32_t maxVelocity     = jsonHasKey(params, "max_velocity")     ? jsonGetInt(params, "max_velocity", -1)                : -1;
        int32_t currentLimit    = jsonHasKey(params, "current_limit")    ? jsonGetInt(params, "current_limit", -1)               : -1;
        float   kp              = jsonGetFloat(params, "kp", NAN);
        float   ki              = jsonGetFloat(params, "ki", NAN);
        float   kd              = jsonGetFloat(params, "kd", NAN);
        int32_t zeroAdc         = jsonHasKey(params, "zero_adc")         ? jsonGetInt(params, "zero_adc", INT32_MIN)             : INT32_MIN;
        int32_t adcPer360       = jsonHasKey(params, "adc_per_360")      ? jsonGetInt(params, "adc_per_360", INT32_MIN)          : INT32_MIN;
        bool    ramOnly         = jsonGetInt(params, "ram_only", 0) != 0;

        bus.servo(sid).configure(newServoId, dirInvert, minAngle, maxAngle,
                                 maxVelocity, currentLimit, kp, ki, kd,
                                 zeroAdc, adcPer360, ramOnly);

        uint8_t finalId = (newServoId >= 0) ? (uint8_t)newServoId : sid;
        sendAckWithId("configure", sid, finalId);
    }
    // ── clear_error ─────────────────────────────────────────────────────
    else if (strcmp(cmd, "clear_error") == 0) {
        bus.servo(sid).clearError();
        sendAck("clear_error");
    }
    // ── unknown ─────────────────────────────────────────────────────────
    else {
        char msg[48];
        snprintf(msg, sizeof(msg), "Unknown command: %s", cmd);
        sendError(msg);
    }
}

// ─── Setup & Loop ───────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    servoSerial.begin(250000);
    delay(500);
    sendLog("Microdrive Proxy Started.");
}

void loop() {
    // Read a full JSON line from USB serial
    if (Serial.available()) {
        int len = Serial.readBytesUntil('\n', lineBuf, sizeof(lineBuf) - 1);
        if (len > 0) {
            lineBuf[len] = '\0';
            // Trim trailing \r
            if (len > 0 && lineBuf[len - 1] == '\r') lineBuf[len - 1] = '\0';
            if (strlen(lineBuf) > 0) {
                handleCommand(lineBuf);
            }
        }
    }
}
