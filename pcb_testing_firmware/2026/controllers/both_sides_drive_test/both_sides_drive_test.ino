/*
  Microver 2026 Both-Sides Drive Test

  Target board:
  - Arduino Nano Every A1 / Main_Arduino_Nano_Every on final_compute_arduinos_rev_a
  - final_control_board_rev_a with two VNH5019A-E H-bridge channels

  KiCad-derived pin map:
  - Left drive, Drive_4 to Drive_6, final control J14:
      PWM       -> D10
      INA       -> D6
      INB       -> D7
      ENA/DIAGA -> A6
      ENB/DIAGB -> A7
      CS        -> A0
  - Right drive, Drive_1 to Drive_3, final control J15:
      PWM       -> D9
      INA       -> D4
      INB       -> D5
      ENA/DIAGA -> D8
      ENB/DIAGB -> D13
      CS        -> A1

  Serial commands at 115200 baud:
  - f: run both sides forward for TEST_RUN_MS
  - r: run both sides reverse for TEST_RUN_MS
  - s: stop immediately
  - d: print driver diagnostics and current-sense ADC values
  - +: increase test speed
  - -: decrease test speed

  For first tests, lift the rover so the wheels are off the ground.
*/

#include <Arduino.h>

struct DriveChannel {
  const char *name;
  uint8_t pwmPin;
  uint8_t inaPin;
  uint8_t inbPin;
  uint8_t enaDiagPin;
  uint8_t enbDiagPin;
  uint8_t currentSensePin;
  bool invertForward;
};

DriveChannel leftDrive = {
  "Left Drive_4-Drive_6",
  10,
  6,
  7,
  A6,
  A7,
  A0,
  false
};

DriveChannel rightDrive = {
  "Right Drive_1-Drive_3",
  9,
  4,
  5,
  8,
  13,
  A1,
  false
};

const unsigned long TEST_RUN_MS = 3000;
const unsigned long STATUS_INTERVAL_MS = 500;
const uint8_t MIN_TEST_SPEED = 40;
const uint8_t MAX_TEST_SPEED = 180;
const uint8_t SPEED_STEP = 10;

uint8_t testSpeed = 80;
bool driveActive = false;
unsigned long stopAtMs = 0;
unsigned long lastStatusMs = 0;

void setupChannel(const DriveChannel &channel);
void setChannelSpeed(const DriveChannel &channel, int speed);
void stopChannel(const DriveChannel &channel);
void stopAll();
void beginTimedRun(int speed);
bool channelHealthy(const DriveChannel &channel);
bool allDriversHealthy();
void printChannelStatus(const DriveChannel &channel);
void printStatus();
void printMenu();
void handleSerialCommand(char command);

void setup() {
  Serial.begin(115200);

  setupChannel(leftDrive);
  setupChannel(rightDrive);
  stopAll();

  delay(250);
  printMenu();
}

void loop() {
  while (Serial.available() > 0) {
    const char command = Serial.read();
    handleSerialCommand(command);
  }

  if (driveActive && millis() >= stopAtMs) {
    stopAll();
    Serial.println(F("Timed run complete. Motors stopped."));
  }

  if (driveActive && (millis() - lastStatusMs >= STATUS_INTERVAL_MS)) {
    lastStatusMs = millis();
    printStatus();
    if (!allDriversHealthy()) {
      stopAll();
      Serial.println(F("Driver diagnostic went low. Motors stopped."));
    }
  }
}

void setupChannel(const DriveChannel &channel) {
  pinMode(channel.pwmPin, OUTPUT);
  pinMode(channel.inaPin, OUTPUT);
  pinMode(channel.inbPin, OUTPUT);

  /*
    VNH5019 ENA/DIAGA and ENB/DIAGB are enable/fault lines.
    INPUT_PULLUP lets the driver run normally and still allows a fault to pull
    the line low.
  */
  pinMode(channel.enaDiagPin, INPUT_PULLUP);
  pinMode(channel.enbDiagPin, INPUT_PULLUP);
  pinMode(channel.currentSensePin, INPUT);

  stopChannel(channel);
}

void setChannelSpeed(const DriveChannel &channel, int speed) {
  const uint8_t duty = constrain(abs(speed), 0, 255);

  if (duty == 0) {
    stopChannel(channel);
    return;
  }

  bool forward = (speed > 0);
  if (channel.invertForward) {
    forward = !forward;
  }

  digitalWrite(channel.inaPin, forward ? HIGH : LOW);
  digitalWrite(channel.inbPin, forward ? LOW : HIGH);
  analogWrite(channel.pwmPin, duty);
}

void stopChannel(const DriveChannel &channel) {
  analogWrite(channel.pwmPin, 0);
  digitalWrite(channel.inaPin, LOW);
  digitalWrite(channel.inbPin, LOW);
}

void stopAll() {
  stopChannel(leftDrive);
  stopChannel(rightDrive);
  driveActive = false;
}

void beginTimedRun(int speed) {
  if (!allDriversHealthy()) {
    Serial.println(F("Not starting: at least one driver diagnostic line is low."));
    printStatus();
    return;
  }

  setChannelSpeed(leftDrive, speed);
  setChannelSpeed(rightDrive, speed);

  driveActive = true;
  stopAtMs = millis() + TEST_RUN_MS;
  lastStatusMs = 0;

  Serial.print(F("Running both sides at PWM "));
  Serial.print(abs(speed));
  Serial.print(speed >= 0 ? F(" forward") : F(" reverse"));
  Serial.print(F(" for "));
  Serial.print(TEST_RUN_MS);
  Serial.println(F(" ms."));
}

bool channelHealthy(const DriveChannel &channel) {
  return digitalRead(channel.enaDiagPin) == HIGH && digitalRead(channel.enbDiagPin) == HIGH;
}

bool allDriversHealthy() {
  return channelHealthy(leftDrive) && channelHealthy(rightDrive);
}

void printChannelStatus(const DriveChannel &channel) {
  Serial.print(channel.name);
  Serial.print(F(" diagA="));
  Serial.print(digitalRead(channel.enaDiagPin) == HIGH ? F("HIGH") : F("LOW"));
  Serial.print(F(" diagB="));
  Serial.print(digitalRead(channel.enbDiagPin) == HIGH ? F("HIGH") : F("LOW"));
  Serial.print(F(" csRaw="));
  Serial.println(analogRead(channel.currentSensePin));
}

void printStatus() {
  printChannelStatus(leftDrive);
  printChannelStatus(rightDrive);
}

void printMenu() {
  Serial.println(F("Microver 2026 both-sides drive test"));
  Serial.println(F("Commands: f=forward, r=reverse, s=stop, d=diagnostics, +=faster, -=slower"));
  Serial.print(F("Initial test speed PWM="));
  Serial.println(testSpeed);
  printStatus();
}

void handleSerialCommand(char command) {
  switch (command) {
    case 'f':
    case 'F':
      beginTimedRun(testSpeed);
      break;

    case 'r':
    case 'R':
      beginTimedRun(-testSpeed);
      break;

    case 's':
    case 'S':
      stopAll();
      Serial.println(F("Motors stopped."));
      break;

    case 'd':
    case 'D':
      printStatus();
      break;

    case '+':
      testSpeed = constrain(testSpeed + SPEED_STEP, MIN_TEST_SPEED, MAX_TEST_SPEED);
      Serial.print(F("Test speed PWM="));
      Serial.println(testSpeed);
      break;

    case '-':
      testSpeed = constrain(testSpeed - SPEED_STEP, MIN_TEST_SPEED, MAX_TEST_SPEED);
      Serial.print(F("Test speed PWM="));
      Serial.println(testSpeed);
      break;

    case '\n':
    case '\r':
    case ' ':
      break;

    default:
      Serial.println(F("Unknown command."));
      printMenu();
      break;
  }
}
