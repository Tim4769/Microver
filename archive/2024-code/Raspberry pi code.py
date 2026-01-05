#!/usr/bin/env python3
import serial
import time
import threading

# Open the serial connection to the Arduino
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1.0)  # Adjust the port as needed
time.sleep(3)  # Wait for the connection to establish
ser.reset_input_buffer()

print("Serial OK")


def interrupt_listener():
    """Continuously checks for incoming serial messages from Arduino."""
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(f"Message from Arduino: {line}")  # Display message immediately


def motor_control():
    """Starts motor, then sends stop command after 3 seconds."""
    print("Motor started!")
    ser.write(b'w')  # Send start command to Arduino
    time.sleep(3)  # Keep motor running for 3 seconds
    print("Motor stopped!")
    ser.write(b'stop')  # Send stop command to Arduino


# Start the interrupt listener in a separate thread
interrupt_thread = threading.Thread(target=interrupt_listener, daemon=True)
interrupt_thread.start()

try:
    while True:
        code = input("Insert key (or type 'exit' to quit): ").strip().lower()

        if code == 'exit':
            break  # Exit the loop and stop the program

        if code == 'w':  
            # Start motor and stop it after 3 seconds in a separate thread
            motor_thread = threading.Thread(target=motor_control)
            motor_thread.start()

        print(f"Sending: {code}")

        # Send the input to Arduino
        ser.write(code.encode())  # Send the input as bytes
        time.sleep(1)
        print("Message sent to Arduino")

except KeyboardInterrupt:
    print("\nClosing Serial communication.")
    ser.close()


