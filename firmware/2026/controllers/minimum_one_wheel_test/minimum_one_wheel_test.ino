/*
  Microver 2026 Minimum One-Wheel Test

  Use this first:
  1. Lift the rover so the wheel cannot drive away.
  2. Plug one motor into Drive_1, Drive_2, or Drive_3.
  3. Upload this to the main Arduino Nano Every.
  4. The connected wheel should run slowly for 2 seconds, stop for 2 seconds,
     and repeat.

  Current Rev A KiCad pin map for the right drive channel:
  - PWM -> D9
  - INA -> D4
  - INB -> D5
  - ENA/DIAGA -> D8
  - ENB/DIAGB -> D13

  Note: Drive_1 to Drive_3 share the same right-side driver. To spin only one
  wheel, connect only one motor on that side during this test.
  D3 is not a motor-control pin on the Rev A final board; it maps to boost
  on/off, so leave it alone for this test.
*/

#include <Arduino.h>

const uint8_t PWM_PIN = 9;
const uint8_t INA_PIN = 4;
const uint8_t INB_PIN = 5;
const uint8_t ENA_DIAG_PIN = 8;
const uint8_t ENB_DIAG_PIN = 13;

const uint8_t TEST_SPEED = 80;
const unsigned long RUN_MS = 2000;
const unsigned long STOP_MS = 2000;

void stopWheel() {
  analogWrite(PWM_PIN, 0);
  digitalWrite(INA_PIN, LOW);
  digitalWrite(INB_PIN, LOW);
}

void runWheelForward() {
  digitalWrite(INA_PIN, HIGH);
  digitalWrite(INB_PIN, LOW);

  for (uint8_t speed = 0; speed <= TEST_SPEED; speed += 5) {
    analogWrite(PWM_PIN, speed);
    delay(25);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PWM_PIN, OUTPUT);
  pinMode(INA_PIN, OUTPUT);
  pinMode(INB_PIN, OUTPUT);

  pinMode(ENA_DIAG_PIN, INPUT_PULLUP);
  pinMode(ENB_DIAG_PIN, INPUT_PULLUP);

  stopWheel();
  delay(1000);

  Serial.println(F("Minimum one-wheel test"));
  Serial.println(F("Use Drive_1, Drive_2, or Drive_3 with only one motor connected."));
  Serial.println(F("D3 is boost enable on this board, not motor enable."));
}

void loop() {
  if (digitalRead(ENA_DIAG_PIN) == LOW || digitalRead(ENB_DIAG_PIN) == LOW) {
    stopWheel();
    Serial.println(F("Driver diagnostic is LOW; check motor power, wiring, or fault condition."));
    delay(STOP_MS);
    return;
  }

  runWheelForward();
  delay(RUN_MS);

  stopWheel();
  delay(STOP_MS);
}
