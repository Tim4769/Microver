int counter = 0;
// Define motor control pins
const int Motorinput1 = 10; // Motor input 1 (PWM pin)
const int Motorinput2 = 9;  // Motor input 2 (PWM pin)
const int opticinputPin = 3; // Interrupt pin

volatile bool interruptFlag = false; // Flag to indicate an interrupt
unsigned long motorStartTime = 0;    // Timer for motor run duration
bool motorRunning = false;           // Track motor state

// Interrupt Service Routine (ISR)
void handleInterrupt() {
    interruptFlag = true; // Set the flag on interrupt
}

void setup() {
    pinMode(Motorinput1, OUTPUT);
    pinMode(Motorinput2, OUTPUT);

    pinMode(opticinputPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(opticinputPin), handleInterrupt, CHANGE);

    Serial.begin(9600);
}

void loop() {
    // Read serial input
    if (Serial.available() > 0) {
        char receivedChar = Serial.read();
        Serial.print("Received: ");
        Serial.println(receivedChar); // Debugging line

        if (receivedChar == 'w') {
            motorRunning = true;  // Set motor state
            motorStartTime = millis();  // Record start time
            spinMotor();
            Serial.println("Motor is spinning for 3 seconds.");
        }
    }

    // Check if 3 seconds have passed since motor started
    if (motorRunning && (millis() - motorStartTime >= 3000)) {
        stopMotor();
        Serial.println("Motor stopped after 3 seconds.");
        motorRunning = false;  // Reset motor state
    }

    // Handle interrupt flag
    if (interruptFlag) {
        interruptFlag = false; // Clear the flag
        Serial.println("Interrupt detected!");
    }
}

// Function to spin the motor forward
void spinMotor() {
    digitalWrite(Motorinput1, HIGH);
    digitalWrite(Motorinput2, LOW);
}

// Function to stop the motor
void stopMotor() {
    digitalWrite(Motorinput1, LOW);
    digitalWrite(Motorinput2, LOW);
}
