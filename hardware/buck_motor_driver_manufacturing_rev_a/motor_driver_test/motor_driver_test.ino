/*
  VNH5019 Motor Driver Test (datasheet-scaled)
  Pins:
    D10 = ENA/DIAGA (pull-up; low on fault)
    D9  = ENB/DIAGB
    D8  = INA
    D7  = INB
    D5  = PWM
    A0  = CS
*/

const uint8_t PIN_ENA = 10;
const uint8_t PIN_ENB = 9;
const uint8_t PIN_INA = 8;
const uint8_t PIN_INB = 7;
const uint8_t PIN_PWM = 5;
const uint8_t PIN_CS  = A0;

const uint8_t PWM_MAX  = 255;
const uint8_t PWM_STEP = 8;
const unsigned long STEP_MS  = 30;
const unsigned long DWELL_MS = 800;
const unsigned long REPORT_INTERVAL_MS = 50;  // how often to print live samples

// Datasheet Iout/Isense ≈ 7.03k typ; Pololu carrier uses 1k sense resistor → ~0.142 V/A
const float CS_RATIO_Typ = 7030.0f;   // Iout / Isense
const float CS_RSENSE    = 1000.0f;   // ohms on current-sense resistor (Pololu: 1k)
const float CS_V_PER_A   = CS_RSENSE / CS_RATIO_Typ;  // ≈0.142 V/A

unsigned long lastSampleMs = 0;

void setup() {
  Serial.begin(115200);

  // EN/DIAG pins: leave as inputs with pull-ups so they can pull low on fault.
  pinMode(PIN_ENA, INPUT_PULLUP);
  pinMode(PIN_ENB, INPUT_PULLUP);

  pinMode(PIN_INA, OUTPUT);
  pinMode(PIN_INB, OUTPUT);
  pinMode(PIN_PWM, OUTPUT);
  pinMode(PIN_CS, INPUT);

  digitalWrite(PIN_INA, LOW);
  digitalWrite(PIN_INB, LOW);
  analogWrite(PIN_PWM, 0);

  Serial.println(F("Motor driver test starting..."));
}

void loop() {
  runDirection(true,  "FWD");
  brakeAndReport();
  delay(400);
  runDirection(false, "REV");
  brakeAndReport();
  delay(800);
}

void runDirection(bool forward, const char* label) {
  digitalWrite(PIN_INA, forward ? HIGH : LOW);
  digitalWrite(PIN_INB, forward ? LOW  : HIGH);

  for (int d = 0; d <= PWM_MAX; d += PWM_STEP) {
    analogWrite(PIN_PWM, d);
    logSample(label, d);
    delay(STEP_MS);
  }

  analogWrite(PIN_PWM, PWM_MAX);
  delay(DWELL_MS / 2);
  report(label);              // sample while driving
  delay(DWELL_MS / 2);

  for (int d = PWM_MAX; d >= 0; d -= PWM_STEP) {
    analogWrite(PIN_PWM, d);
    logSample(label, d);
    delay(STEP_MS);
  }
  analogWrite(PIN_PWM, 0);
}

void brakeAndReport() {
  digitalWrite(PIN_INA, LOW);
  digitalWrite(PIN_INB, LOW);
  analogWrite(PIN_PWM, 0);
  delay(200);
  report("BRAKE");
}

void logSample(const char* phase, int pwmValue) {
  const unsigned long now = millis();
  if (now - lastSampleMs < REPORT_INTERVAL_MS) {
    return;
  }
  lastSampleMs = now;

  const int csRaw = analogRead(PIN_CS);
  const float csVolts = (csRaw / 1023.0f) * 5.0f;
  const float amps = csVolts / CS_V_PER_A;
  const bool diagA_ok = digitalRead(PIN_ENA);
  const bool diagB_ok = digitalRead(PIN_ENB);

  Serial.print(phase);
  Serial.print(F(" pwm="));
  Serial.print(pwmValue);
  Serial.print(F(" | CSraw="));
  Serial.print(csRaw);
  Serial.print(F(" ("));
  Serial.print(csVolts, 3);
  Serial.print(F(" V, "));
  Serial.print(amps, 2);
  Serial.print(F(" A) | DIAGA="));
  Serial.print(diagA_ok ? F("OK") : F("FAULT"));
  Serial.print(F(" | DIAGB="));
  Serial.println(diagB_ok ? F("OK") : F("FAULT"));
}

void report(const char* phase) {
  const int csRaw = analogRead(PIN_CS);
  const float csVolts = (csRaw / 1023.0f) * 5.0f;
  const float amps = csVolts / CS_V_PER_A;

  const bool diagA_ok = digitalRead(PIN_ENA); // active LOW
  const bool diagB_ok = digitalRead(PIN_ENB);

  Serial.print(phase);
  Serial.print(F(" | CSraw="));
  Serial.print(csRaw);
  Serial.print(F(" ("));
  Serial.print(csVolts, 3);
  Serial.print(F(" V, "));
  Serial.print(amps, 2);
  Serial.print(F(" A) | DIAGA="));
  Serial.print(diagA_ok ? F("OK") : F("FAULT"));
  Serial.print(F(" | DIAGB="));
  Serial.println(diagB_ok ? F("OK") : F("FAULT"));
}
