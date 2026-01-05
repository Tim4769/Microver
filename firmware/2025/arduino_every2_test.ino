/*
  Arduino Every 2 Servo Harness Test
  ----------------------------------
  Pin map (per design notes):
    - D10 -> Servo 4 (e.g., sabotage mechanism)
    - D9  -> Servo 3 (flag raiser)
    - D6  -> Servo 2 (broom support #2)
    - D5  -> Servo 1 (broom support #1)
  Test goals:
    1. Verify the buck regulator, headers, and signal routing for each servo channel.
    2. Exercise the servos sequentially so only one moves at a time, simplifying troubleshooting.
  Usage: Upload, power the PCB, and monitor Serial (115200 baud) for which servo is
  being driven. Each servo sweeps between two angles twice before the next servo runs.
*/

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <stdio.h>

struct ServoChannel {
  uint8_t pin;
  const char *label;
  uint8_t minAngle;
  uint8_t maxAngle;
};

ServoChannel servoMap[] = {
  {5,  "Servo 1 (D5)", 40, 140},
  {6,  "Servo 2 (D6)", 40, 140},
  {9,  "Servo 3 (D9)", 40, 140},
  {10, "Servo 4 (D10)", 40, 140}
};

Servo servoObjs[sizeof(servoMap) / sizeof(servoMap[0])];
const unsigned long dwellMs = 400;
const uint8_t stepSize = 5;

const uint8_t LINK_RX_PIN = 11;  // Receives data from Arduino Every 1
const uint8_t LINK_TX_PIN = 12;  // Sends data back to Arduino Every 1
const unsigned long LINK_BAUD = 38400;
SoftwareSerial linkSerial(LINK_RX_PIN, LINK_TX_PIN);

uint8_t currentServoIndex = 0;
bool servoMotionActive = false;

char linkBuffer[40];
size_t linkIndex = 0;
uint32_t linkPackets = 0;
uint32_t linkParseErrors = 0;
uint8_t lastPingSeq = 0;

void setupLinkPort();
void serviceLink();
void handleLinkLine(const char *line);
void sendAck(uint8_t seq);
void logLinkStats();
void waitWithService(unsigned long durationMs);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println(F("Arduino Every 2 servo test starting..."));
  Serial.println(F("Ensure 5V servo supply is active before connecting servos."));
  setupLinkPort();

  for (size_t i = 0; i < (sizeof(servoMap) / sizeof(servoMap[0])); ++i) {
    servoObjs[i].attach(servoMap[i].pin);
    servoObjs[i].write(90);
    waitWithService(250);
  }
}

void loop() {
  for (size_t i = 0; i < (sizeof(servoMap) / sizeof(servoMap[0])); ++i) {
    exerciseServo(i);
    logLinkStats();
  }
}

void exerciseServo(size_t index) {
  Servo &servo = servoObjs[index];
  const ServoChannel &channel = servoMap[index];

  Serial.println();
  Serial.print(F("Exercising "));
  Serial.println(channel.label);
  currentServoIndex = static_cast<uint8_t>(index);
  servoMotionActive = true;

  for (uint8_t repeats = 0; repeats < 2; ++repeats) {
    sweepServo(servo, channel.minAngle, channel.maxAngle);
    sweepServo(servo, channel.maxAngle, channel.minAngle);
  }

  servo.write(90);
  servoMotionActive = false;
  waitWithService(dwellMs * 2);
}

void sweepServo(Servo &servo, uint8_t start, uint8_t stop) {
  if (start < stop) {
    for (uint8_t angle = start; angle <= stop; angle += stepSize) {
      servo.write(angle);
      waitWithService(40);
    }
  } else {
    for (int angle = start; angle >= stop; angle -= stepSize) {
      servo.write(angle);
      waitWithService(40);
    }
  }
  waitWithService(dwellMs);
}

void setupLinkPort() {
  pinMode(LINK_TX_PIN, OUTPUT);
  pinMode(LINK_RX_PIN, INPUT);
  linkSerial.begin(LINK_BAUD);
  linkSerial.listen();
}

void serviceLink() {
  while (linkSerial.available()) {
    const char c = linkSerial.read();
    if (c == '\n') {
      linkBuffer[linkIndex] = '\0';
      handleLinkLine(linkBuffer);
      linkIndex = 0;
    } else {
      if (linkIndex < sizeof(linkBuffer) - 1) {
        linkBuffer[linkIndex++] = c;
      }
    }
  }
}

void handleLinkLine(const char *line) {
  uint8_t seq = 0;
  if (sscanf(line, "PING,%hhu", &seq) == 1) {
    lastPingSeq = seq;
    sendAck(seq);
    ++linkPackets;
  } else {
    ++linkParseErrors;
  }
}

void sendAck(uint8_t seq) {
  const uint8_t servoId = currentServoIndex + 1;
  const uint8_t active = servoMotionActive ? 1 : 0;
  linkSerial.print(F("ACK,"));
  linkSerial.print(seq);
  linkSerial.print(',');
  linkSerial.print(servoId);
  linkSerial.print(',');
  linkSerial.print(active);
  linkSerial.print('\n');
}

void logLinkStats() {
  static unsigned long lastLog = 0;
  const unsigned long now = millis();
  if (now - lastLog < 2000) {
    return;
  }
  lastLog = now;

  Serial.print(F("Link status -> packets: "));
  Serial.print(linkPackets);
  Serial.print(F(", parse errors: "));
  Serial.print(linkParseErrors);
  Serial.print(F(", last seq "));
  Serial.print(lastPingSeq);
  Serial.print(F(", servo "));
  Serial.print(currentServoIndex + 1);
  Serial.print(servoMotionActive ? F(" moving") : F(" idle"));
  Serial.println();
}

void waitWithService(unsigned long durationMs) {
  const unsigned long start = millis();
  while ((millis() - start) < durationMs) {
    serviceLink();
    delay(2);
  }
}
