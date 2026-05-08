/*
  Microver 2026 simple VNH5019 both-side motor test

  Upload this to A1 / Main_Arduino_Nano_Every.

  Start with the rover lifted. For first testing, plug in only one motor per
  side so the startup current stays low.
*/

#include <Arduino.h>

const uint8_t TEST_PWM = 70;
const unsigned long RUN_MS = 1500;
const unsigned long STOP_MS = 1500;

struct MotorPins {
  uint8_t pwm;
  uint8_t ina;
  uint8_t inb;
  uint8_t diagA;
  uint8_t diagB;
  const char *name;
};

const MotorPins RIGHT = {
  9,   // PWM, U1, Drive_1-Drive_3
  4,   // INA
  5,   // INB
  8,   // ENA/DIAGA
  13,  // ENB/DIAGB
  "RIGHT Drive_1-Drive_3"
};

const MotorPins LEFT = {
  10,  // PWM, U2, Drive_4-Drive_6
  6,   // INA
  7,   // INB
  A6,  // ENA/DIAGA
  A7,  // ENB/DIAGB
  "LEFT Drive_4-Drive_6"
};

void stopMotor(const MotorPins &pins) {
  analogWrite(pins.pwm, 0);
  digitalWrite(pins.ina, LOW);
  digitalWrite(pins.inb, LOW);
}

void forward(const MotorPins &pins) {
  digitalWrite(pins.ina, HIGH);
  digitalWrite(pins.inb, LOW);
  analogWrite(pins.pwm, TEST_PWM);
}

void reverse(const MotorPins &pins) {
  digitalWrite(pins.ina, LOW);
  digitalWrite(pins.inb, HIGH);
  analogWrite(pins.pwm, TEST_PWM);
}

bool driverOk(const MotorPins &pins) {
  return digitalRead(pins.diagA) == HIGH && digitalRead(pins.diagB) == HIGH;
}

bool bothDriversOk() {
  return driverOk(RIGHT) && driverOk(LEFT);
}

void printDiag(const MotorPins &pins) {
  Serial.print(pins.name);
  Serial.print(F(" "));
  Serial.print(F("DIAG A="));
  Serial.print(digitalRead(pins.diagA) == HIGH ? F("HIGH") : F("LOW"));
  Serial.print(F(" DIAG B="));
  Serial.println(digitalRead(pins.diagB) == HIGH ? F("HIGH") : F("LOW"));
}

void printAllDiag() {
  printDiag(RIGHT);
  printDiag(LEFT);
}

void stopBoth() {
  stopMotor(RIGHT);
  stopMotor(LEFT);
}

void forwardBoth() {
  forward(RIGHT);
  forward(LEFT);
}

void reverseBoth() {
  reverse(RIGHT);
  reverse(LEFT);
}

void setupMotor(const MotorPins &pins) {
  pinMode(pins.pwm, OUTPUT);
  pinMode(pins.ina, OUTPUT);
  pinMode(pins.inb, OUTPUT);
  pinMode(pins.diagA, INPUT_PULLUP);
  pinMode(pins.diagB, INPUT_PULLUP);
  stopMotor(pins);
}

void setup() {
  Serial.begin(115200);

  setupMotor(RIGHT);
  setupMotor(LEFT);
  delay(1000);

  Serial.println(F("Simple both-side motor test"));
  printAllDiag();
}

void loop() {
  if (!bothDriversOk()) {
    stopBoth();
    Serial.println(F("Driver fault or disabled. Motors stopped."));
    printAllDiag();
    delay(STOP_MS);
    return;
  }

  Serial.println(F("Both forward"));
  forwardBoth();
  delay(RUN_MS);

  Serial.println(F("Stop"));
  stopBoth();
  delay(STOP_MS);

  if (!bothDriversOk()) {
    stopBoth();
    Serial.println(F("Driver fault before reverse. Motors stopped."));
    printAllDiag();
    delay(STOP_MS);
    return;
  }

  Serial.println(F("Both reverse"));
  reverseBoth();
  delay(RUN_MS);

  Serial.println(F("Stop"));
  stopBoth();
  delay(STOP_MS);
}
