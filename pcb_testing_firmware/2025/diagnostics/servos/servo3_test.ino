/*
  Servo 3 Test (D9)
  Drives only this servo and prints exact angle changes.
*/

#include <Arduino.h>
#include <Servo.h>

const uint8_t SERVO_PIN = 9;
const uint8_t CENTER_ANGLE = 90;
const uint8_t MIN_ANGLE = 40;
const uint8_t MAX_ANGLE = 140;
const uint8_t STEP = 5;
const unsigned long STEP_DELAY_MS = 40;
const unsigned long PAUSE_MS = 400;

Servo servo;
uint8_t currentAngle = CENTER_ANGLE;

void moveToAngle(uint8_t target) {
  if (currentAngle == target) {
    return;
  }
  if (currentAngle < target) {
    for (uint8_t angle = currentAngle; angle <= target; angle += STEP) {
      servo.write(angle);
      delay(STEP_DELAY_MS);
      if (angle + STEP < angle) {
        break;
      }
    }
  } else {
    for (int angle = currentAngle; angle >= target; angle -= STEP) {
      servo.write(angle);
      delay(STEP_DELAY_MS);
    }
  }
  currentAngle = target;
}

void printMove(const char *label, uint8_t from, uint8_t to) {
  const uint8_t delta = (from > to) ? (from - to) : (to - from);
  Serial.print(label);
  Serial.print(' ');
  Serial.print(from);
  Serial.print(F("->"));
  Serial.print(to);
  Serial.print(F(" ("));
  Serial.print(delta);
  Serial.println(F(" deg)"));
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  servo.attach(SERVO_PIN);
  servo.write(CENTER_ANGLE);
  Serial.println(F("Servo 3 test"));
}

void loop() {
  printMove("Move", currentAngle, MIN_ANGLE);
  moveToAngle(MIN_ANGLE);

  printMove("Sweep", MIN_ANGLE, MAX_ANGLE);
  for (uint8_t angle = MIN_ANGLE; angle <= MAX_ANGLE; angle += STEP) {
    servo.write(angle);
    delay(STEP_DELAY_MS);
    currentAngle = angle;
  }

  printMove("Sweep", MAX_ANGLE, MIN_ANGLE);
  for (int angle = MAX_ANGLE; angle >= MIN_ANGLE; angle -= STEP) {
    servo.write(angle);
    delay(STEP_DELAY_MS);
    currentAngle = static_cast<uint8_t>(angle);
  }

  printMove("Move", currentAngle, CENTER_ANGLE);
  moveToAngle(CENTER_ANGLE);
  delay(PAUSE_MS);
}
