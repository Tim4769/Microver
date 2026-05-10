# Arduino Rover Main PCB - Rev A

Short bring-up guide for the main board using the existing firmware test sketches.

## Equipment
- Bench supply, 18-25 V, with current limit
- DMM
- Two Arduino Nano Every boards and USB cables
- A few servos, motor-driver wiring, and optional Raspberry Pi

## Quick Test
1. Unpowered: inspect XT30 polarity, buck parts, capacitor polarity, and headers. Confirm VIN and each 5 V rail are not shorted to GND.
2. Rails first: with no loads fitted, power the board at 18 V / 0.5 A and check the three 5 V rails. They should all read about 4.9-5.1 V.
3. Add the two Arduinos and confirm the rails still hold and both boards enumerate over USB.
4. Servo side: run the servo test sketches, starting with one servo and then more. The servo rail should stay stable and the Arduinos should not brown out.
5. Motor side: run the left/right drivetrain tests, then the main Every1 test. Motors should respond and encoder counts should change as expected.
6. Link check: with both main sketches loaded, confirm the Every1 and Every2 boards exchange PING/ACK messages without timeouts.
7. Optional full-stack check: add the Raspberry Pi and rerun low-duty motor and servo tests. The 5 V rails should stay in range.

## Pass
- All 5 V rails stay within 4.9-5.1 V
- No Arduino resets during servo or motor tests
- Encoders count correctly and the inter-board link is stable
- No excessive heating on regulators or headers
