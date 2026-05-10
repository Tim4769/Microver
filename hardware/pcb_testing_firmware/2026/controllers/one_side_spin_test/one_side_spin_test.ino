/*
  Microver 2026 One-Side Wheel Spin Test

  Upload to the main Arduino Nano Every.
  The rover must be lifted so the wheels cannot drive away.

  Set SIDE_TO_TEST to RIGHT_SIDE for Drive_1 to Drive_3.
  Set SIDE_TO_TEST to LEFT_SIDE for Drive_4 to Drive_6.
*/

#include <Arduino.h>

enum Side {
  RIGHT_SIDE,
  LEFT_SIDE
};

const Side SIDE_TO_TEST = RIGHT_SIDE;

const uint8_t TEST_SPEED = 80;
const unsigned long RAMP_STEP_MS = 30;
const unsigned long RUN_MS = 3000;
const unsigned long STOP_MS = 2000;

struct DrivePins {
  uint8_t pwm;
  uint8_t ina;
  uint8_t inb;
  uint8_t diagA;
  uint8_t diagB;
  const char *name;
};

const DrivePins RIGHT = {
  9,   // DRV1_PWM_OUT
  4,   // DRV1_CTRL_A_OUT / INA
  5,   // DRV1_CTRL_B_OUT / INB
  8,   // DRV1_STATUS_A_IN / ENA-DIAGA
  13,  // DRV1_STATUS_B_IN / ENB-DIAGB
  "RIGHT Drive_1-Drive_3"
};

const DrivePins LEFT = {
  10,  // DRV2_PWM_OUT
  6,   // DRV2_CTRL_A_OUT / INA
  7,   // DRV2_CTRL_B_OUT / INB
  A6,  // DRV2_STATUS_A_IN / ENA-DIAGA
  A7,  // DRV2_STATUS_B_IN / ENB-DIAGB
  "LEFT Drive_4-Drive_6"
};

const DrivePins &drive = (SIDE_TO_TEST == RIGHT_SIDE) ? RIGHT : LEFT;

void stopDrive() {
  analogWrite(drive.pwm, 0);
  digitalWrite(drive.ina, LOW);
  digitalWrite(drive.inb, LOW);
}

bool driverLooksEnabled() {
  return digitalRead(drive.diagA) == HIGH && digitalRead(drive.diagB) == HIGH;
}

void printDiag() {
  Serial.print(drive.name);
  Serial.print(F(" diagA="));
  Serial.print(digitalRead(drive.diagA) == HIGH ? F("HIGH") : F("LOW"));
  Serial.print(F(" diagB="));
  Serial.println(digitalRead(drive.diagB) == HIGH ? F("HIGH") : F("LOW"));
}

void spinForward() {
  digitalWrite(drive.ina, HIGH);
  digitalWrite(drive.inb, LOW);

  for (uint8_t pwm = 0; pwm <= TEST_SPEED; pwm += 5) {
    analogWrite(drive.pwm, pwm);
    delay(RAMP_STEP_MS);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(drive.pwm, OUTPUT);
  pinMode(drive.ina, OUTPUT);
  pinMode(drive.inb, OUTPUT);

  pinMode(drive.diagA, INPUT_PULLUP);
  pinMode(drive.diagB, INPUT_PULLUP);

  stopDrive();
  delay(1000);

  Serial.println(F("One-side wheel spin test"));
  Serial.println(drive.name);
  Serial.println(F("Status HIGH = enabled/healthy. Status LOW = disabled or driver fault."));
  printDiag();
}

void loop() {
  if (!driverLooksEnabled()) {
    stopDrive();
    Serial.println(F("Driver diag low. Stopped. Check motor power, driver pull-ups, or wiring."));
    printDiag();
    delay(STOP_MS);
    return;
  }

  Serial.println(F("Spin forward"));
  spinForward();
  delay(RUN_MS);

  Serial.println(F("Stop"));
  stopDrive();
  delay(STOP_MS);
}
