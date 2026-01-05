/*
  Arduino Every 1 PCB Test Sketch
  --------------------------------
  - D5/D6 drive the three motor drivers on one rover side (Side A).
  - D9/D10 drive the three motor drivers on the opposite side (Side B).
  - Encoders:
      * Encoder 1 -> D16 (A), D17 (B)
      * Encoder 2 -> D14 (A), D15 (B)
      * Encoder 3 -> D20 (A), D21 (B)
      * Encoder 4 -> D18 (A), D19 (B)
  Test goals:
    1. Sequentially ramp each motor group forward and backward to confirm PWM/DIR routing.
    2. Continuously report encoder transitions so spinning the wheels confirms sensing paths.
  Usage: Power the PCB, connect via Serial at 115200 baud, and watch the console output
  while the sketch runs motor tests in a loop.
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdio.h>

struct MotorGroup {
  uint8_t forwardPin;
  uint8_t reversePin;
  const char *label;
};

const MotorGroup motorGroups[] = {
  {5, 6, "Side A (pins D5/D6)"},
  {9, 10, "Side B (pins D9/D10)"}
};

struct EncoderPins {
  uint8_t pinA;
  uint8_t pinB;
  const char *label;
};

const EncoderPins encoders[] = {
  {16, 17, "Encoder 1 (D16/D17)"},
  {14, 15, "Encoder 2 (D14/D15)"},
  {20, 21, "Encoder 3 (D20/D21)"},
  {18, 19, "Encoder 4 (D18/D19)"}
};

volatile uint32_t encoderCounts[4][2] = {};

void handleEnc00() { encoderCounts[0][0]++; }
void handleEnc01() { encoderCounts[0][1]++; }
void handleEnc10() { encoderCounts[1][0]++; }
void handleEnc11() { encoderCounts[1][1]++; }
void handleEnc20() { encoderCounts[2][0]++; }
void handleEnc21() { encoderCounts[2][1]++; }
void handleEnc30() { encoderCounts[3][0]++; }
void handleEnc31() { encoderCounts[3][1]++; }

typedef void (*IsrFn)();
const IsrFn encoderIsrs[4][2] = {
  {handleEnc00, handleEnc01},
  {handleEnc10, handleEnc11},
  {handleEnc20, handleEnc21},
  {handleEnc30, handleEnc31}
};

const unsigned long dwellTimeMs = 1000;
const uint8_t pwmStep = 8;  // Larger step keeps the test brief.
const unsigned long pwmStepDelayMs = 25;

const uint8_t LINK_RX_PIN = 12;  // D12 wired to Arduino Every 2 TX
const uint8_t LINK_TX_PIN = 11;  // D11 wired to Arduino Every 2 RX
const unsigned long LINK_BAUD = 38400;
const unsigned long LINK_TIMEOUT_MS = 250;
SoftwareSerial linkSerial(LINK_RX_PIN, LINK_TX_PIN);  // RX, TX
uint8_t linkSequence = 0;
uint32_t linkErrorCount = 0;

struct LinkReport {
  bool replyReceived;
  uint8_t seqEcho;
  uint8_t servoId;
  bool servoActive;
  uint8_t payloadSent;
};

void setupMotorDrivers();
void setupEncoders();
void runMotorSequence(const MotorGroup &group);
void rampPin(uint8_t pwmPin);
void brakePins(uint8_t pinA, uint8_t pinB);
void printEncoderReport();
void setupLinkPort();
LinkReport queryServoController();
void printLinkReport(const LinkReport &report);
bool readLinkLine(char *buffer, size_t length, unsigned long timeoutMs);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println(F("Arduino Every 1 PCB test starting..."));
  setupMotorDrivers();
  setupEncoders();
  setupLinkPort();
  Serial.println(F("Motors will cycle forward/reverse while encoder counts stream every test."));
  Serial.println(F("Spin each wheel/encoder manually to confirm counts increment on the expected channel."));
  Serial.println(F("Data-link test over D11/D12: querying Arduino Every 2 for servo status each cycle."));
}

void loop() {
  for (const auto &group : motorGroups) {
    runMotorSequence(group);
    printEncoderReport();
    const LinkReport report = queryServoController();
    printLinkReport(report);
    delay(1000);
  }
}

void setupMotorDrivers() {
  for (const auto &group : motorGroups) {
    pinMode(group.forwardPin, OUTPUT);
    pinMode(group.reversePin, OUTPUT);
    digitalWrite(group.forwardPin, LOW);
    digitalWrite(group.reversePin, LOW);
  }
}

void setupEncoders() {
  for (size_t i = 0; i < (sizeof(encoders) / sizeof(encoders[0])); ++i) {
    pinMode(encoders[i].pinA, INPUT_PULLUP);
    pinMode(encoders[i].pinB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(encoders[i].pinA), encoderIsrs[i][0], CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoders[i].pinB), encoderIsrs[i][1], CHANGE);
  }
}

void runMotorSequence(const MotorGroup &group) {
  Serial.println();
  Serial.print(F("Testing "));
  Serial.println(group.label);

  Serial.println(F("  Forward ramp"));
  digitalWrite(group.reversePin, LOW);
  rampPin(group.forwardPin);
  delay(dwellTimeMs);

  Serial.println(F("  Braking"));
  brakePins(group.forwardPin, group.reversePin);
  delay(250);

  Serial.println(F("  Reverse ramp"));
  digitalWrite(group.forwardPin, LOW);
  rampPin(group.reversePin);
  delay(dwellTimeMs);

  Serial.println(F("  Braking"));
  brakePins(group.forwardPin, group.reversePin);
}

void rampPin(uint8_t pwmPin) {
  for (uint16_t duty = 0; duty <= 255; duty += pwmStep) {
    analogWrite(pwmPin, duty);
    delay(pwmStepDelayMs);
  }
  analogWrite(pwmPin, 255);
}

void brakePins(uint8_t pinA, uint8_t pinB) {
  analogWrite(pinA, 0);
  analogWrite(pinB, 0);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}

void printEncoderReport() {
  uint32_t snapshot[4][2];
  noInterrupts();
  for (size_t i = 0; i < 4; ++i) {
    snapshot[i][0] = encoderCounts[i][0];
    snapshot[i][1] = encoderCounts[i][1];
    encoderCounts[i][0] = 0;
    encoderCounts[i][1] = 0;
  }
  interrupts();

  Serial.println(F("Encoder edge counts since last report:"));
  for (size_t i = 0; i < 4; ++i) {
    Serial.print(F("  "));
    Serial.print(encoders[i].label);
    Serial.print(F(" -> A:"));
    Serial.print(snapshot[i][0]);
    Serial.print(F(" B:"));
    Serial.println(snapshot[i][1]);
  }
}

void setupLinkPort() {
  pinMode(LINK_TX_PIN, OUTPUT);
  pinMode(LINK_RX_PIN, INPUT);
  linkSerial.begin(LINK_BAUD);
  linkSerial.listen();
}

LinkReport queryServoController() {
  LinkReport report{};
  const uint8_t payload = linkSequence++;

  // Clear any stale bytes before sending a new request.
  while (linkSerial.available()) {
    linkSerial.read();
  }

  linkSerial.print(F("PING,"));
  linkSerial.print(payload);
  linkSerial.print('\n');

  char lineBuffer[40];
  if (!readLinkLine(lineBuffer, sizeof(lineBuffer), LINK_TIMEOUT_MS)) {
    ++linkErrorCount;
    report.replyReceived = false;
    report.payloadSent = payload;
    return report;
  }

  uint8_t seq = 0;
  uint8_t servoId = 0;
  uint8_t servoActive = 0;
  const int parsed = sscanf(lineBuffer, "ACK,%hhu,%hhu,%hhu", &seq, &servoId, &servoActive);
  if (parsed == 3 && seq == payload) {
    report.replyReceived = true;
    report.seqEcho = seq;
    report.servoId = servoId;
    report.servoActive = (servoActive != 0);
  } else {
    report.replyReceived = false;
    ++linkErrorCount;
  }
  report.payloadSent = payload;
  return report;
}

bool readLinkLine(char *buffer, size_t length, unsigned long timeoutMs) {
  size_t index = 0;
  const unsigned long start = millis();
  while ((millis() - start) < timeoutMs) {
    while (linkSerial.available()) {
      const char c = linkSerial.read();
      if (c == '\n') {
        buffer[index] = '\0';
        return true;
      }
      if (index < length - 1) {
        buffer[index++] = c;
      }
    }
  }
  buffer[index] = '\0';
  return false;
}

void printLinkReport(const LinkReport &report) {
  Serial.print(F("Link test -> sent seq "));
  Serial.print(report.payloadSent);

  if (!report.replyReceived) {
    Serial.print(F("; no reply (total errors "));
    Serial.print(linkErrorCount);
    Serial.println(F(")"));
    return;
  }

  Serial.print(F("; ack seq "));
  Serial.print(report.seqEcho);
  Serial.print(F(", servo "));
  Serial.print(report.servoId);
  Serial.print(report.servoActive ? F(" moving") : F(" idle"));
  Serial.println();
}
