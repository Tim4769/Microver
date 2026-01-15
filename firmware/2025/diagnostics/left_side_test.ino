/*
  Left Side Drive Test (D5/D6)
  Drives the left side motor group only and reports encoder counts.
*/

#include <Arduino.h>

const uint8_t IN1_PIN = 5;
const uint8_t IN2_PIN = 6;
const uint8_t SPEED_PWM = 180;
const unsigned long RUN_MS = 2000;
const unsigned long BRAKE_MS = 500;

struct EncoderPins {
  uint8_t pinA;
  uint8_t pinB;
  const char *label;
};

const EncoderPins encoders[] = {
  {16, 17, "E1"},
  {14, 15, "E2"}
};

volatile uint32_t encoderCounts[2][2] = {};

void handleEnc00() { encoderCounts[0][0]++; }
void handleEnc01() { encoderCounts[0][1]++; }
void handleEnc10() { encoderCounts[1][0]++; }
void handleEnc11() { encoderCounts[1][1]++; }

typedef void (*IsrFn)();
const IsrFn encoderIsrs[2][2] = {
  {handleEnc00, handleEnc01},
  {handleEnc10, handleEnc11}
};

struct EncoderSnapshot {
  uint32_t counts[2][2];
};

void setupEncoders();
EncoderSnapshot captureEncoderSnapshot();
void printEncoderSnapshot(const char *tag, const EncoderSnapshot &snapshot);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  setupEncoders();
  Serial.println(F("Left side test"));
}

void loop() {
  digitalWrite(IN2_PIN, LOW);
  analogWrite(IN1_PIN, SPEED_PWM);
  delay(RUN_MS);
  printEncoderSnapshot("Left FWD", captureEncoderSnapshot());

  analogWrite(IN1_PIN, 0);
  analogWrite(IN2_PIN, 0);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  delay(BRAKE_MS);

  digitalWrite(IN1_PIN, LOW);
  analogWrite(IN2_PIN, SPEED_PWM);
  delay(RUN_MS);
  printEncoderSnapshot("Left REV", captureEncoderSnapshot());

  analogWrite(IN1_PIN, 0);
  analogWrite(IN2_PIN, 0);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  delay(1000);
}

void setupEncoders() {
  for (size_t i = 0; i < (sizeof(encoders) / sizeof(encoders[0])); ++i) {
    pinMode(encoders[i].pinA, INPUT_PULLUP);
    pinMode(encoders[i].pinB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(encoders[i].pinA), encoderIsrs[i][0], CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoders[i].pinB), encoderIsrs[i][1], CHANGE);
  }
}

EncoderSnapshot captureEncoderSnapshot() {
  EncoderSnapshot snapshot{};
  noInterrupts();
  for (size_t i = 0; i < 2; ++i) {
    snapshot.counts[i][0] = encoderCounts[i][0];
    snapshot.counts[i][1] = encoderCounts[i][1];
    encoderCounts[i][0] = 0;
    encoderCounts[i][1] = 0;
  }
  interrupts();
  return snapshot;
}

void printEncoderSnapshot(const char *tag, const EncoderSnapshot &snapshot) {
  Serial.print(tag);
  for (size_t i = 0; i < 2; ++i) {
    Serial.print(' ');
    Serial.print(encoders[i].label);
    Serial.print(':');
    Serial.print(snapshot.counts[i][0]);
    Serial.print('/');
    Serial.print(snapshot.counts[i][1]);
  }
  Serial.println();
}
