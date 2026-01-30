/*
  VNH5019-style Motor Driver Test
  Pins:
    D10 = ENA/DIAGA (active HIGH enable, LOW = fault/diag)
    D9  = ENB/DIAGB (active HIGH enable, LOW = fault/diag)
    D8  = INA
    D7  = INB
    D5  = PWM (speed)
    A0  = CS (current sense analog)
  Behavior:
    - Enables the bridge
    - Ramps forward, brakes, ramps reverse
    - Reports current sense and fault flags each phase
*/

const uint8_t PIN_ENA  = 10;
const uint8_t PIN_ENB  = 9;
const uint8_t PIN_INA  = 8;
const uint8_t PIN_INB  = 7;
const uint8_t PIN_PWM  = 5;
const uint8_t PIN_CS   = A0;

const uint8_t PWM_MAX    = 255;
const uint8_t PWM_STEP   = 8;
const unsigned long STEP_MS  = 30;
const unsigned long DWELL_MS = 800;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_INA, OUTPUT);
  pinMode(PIN_INB, OUTPUT);
  pinMode(PIN_PWM, OUTPUT);
  pinMode(PIN_CS, INPUT);

  // Safe defaults
  digitalWrite(PIN_ENA, HIGH);  // enable
  digitalWrite(PIN_ENB, HIGH);  // enable
  digitalWrite(PIN_INA, LOW);
  digitalWrite(PIN_INB, LOW);
  analogWrite(PIN_PWM, 0);

  Serial.println(F("Motor driver test starting..."));
}

void loop() {
  runDirection(true, "FWD");
  brakeAndReport();
  delay(400);
  runDirection(false, "REV");
  brakeAndReport();
  delay(800);
}

void runDirection(bool forward, const char* label) {
  // Set direction
  digitalWrite(PIN_INA, forward ? HIGH : LOW);
  digitalWrite(PIN_INB, forward ? LOW  : HIGH);

  // Ramp up
  for (uint8_t d = 0; d <= PWM_MAX; d += PWM_STEP) {
    analogWrite(PIN_PWM, d);
    delay(STEP_MS);
  }
  analogWrite(PIN_PWM, PWM_MAX);
  delay(DWELL_MS);

  // Ramp down
  for (int d = PWM_MAX; d >= 0; d -= PWM_STEP) {
    analogWrite(PIN_PWM, d);
    delay(STEP_MS);
  }
  analogWrite(PIN_PWM, 0);

  report(label);
}

void brakeAndReport() {
  // Brake by driving both inputs LOW (or set both HIGH for high-side brake)
  digitalWrite(PIN_INA, LOW);
  digitalWrite(PIN_INB, LOW);
  analogWrite(PIN_PWM, 0);
  delay(200);
  report("BRAKE");
}

void report(const char* phase) {
  const int csRaw = analogRead(PIN_CS);
  const float csVolts = (csRaw / 1023.0f) * 5.0f;

  const bool diagA = digitalRead(PIN_ENA); // DIAG goes LOW on fault
  const bool diagB = digitalRead(PIN_ENB);

  Serial.print(phase);
  Serial.print(F(" | CSraw="));
  Serial.print(csRaw);
  Serial.print(F(" ("));
  Serial.print(csVolts, 3);
  Serial.print(F(" V)"));
  Serial.print(F(" | DIAGA="));
  Serial.print(diagA ? F("OK") : F("FAULT"));
  Serial.print(F(" | DIAGB="));
  Serial.println(diagB ? F("OK") : F("FAULT"));
}
