# Arduino Rover Main PCB — Rev A
Bring-up & Functional Test Guide (using existing firmware sketches)

## 0) Equipment
- Bench supply, 18–25 V, current limit 1–5 A (XT30 input).
- DMM; optional oscilloscope for ripple.
- Loads: a few servos, the six DC motor driver harnesses, Raspberry Pi (optional later), and a small 5 V load (e.g., USB tester or 5 Ω/10 W resistor).
- USB cables for two Arduino Nano Every boards.
- Firmware sketches from `firmware/2025/`:
  - Drive/encoders/link: `arduino_every1_test.ino`
  - Servos/link: `arduino_every2_test.ino`
  - Quick isolates: `left_side_test.ino`, `right_side_test.ino`, `servo1_test.ino` … etc. in `firmware/2025/diagnostics/`.

## 1) Visual / Continuity (unpowered)
1. Inspect XT30 polarity, buck regulator orientation, electrolytic capacitor polarity, header silks for servos/LiDAR/Pi.
2. DMM continuity:
   - Main VIN to GND: open.
   - Each 5 V rail to GND: open.
   - Check fuse continuity.

## 2) Rail Bring-Up (no loads)
1. Set supply 18 V, limit 0.5 A. Leave Arduinos, servos, Pi disconnected.
2. Power ON. Measure the three 5 V rails (servo, LiDAR/Every2, Pi). Expected 4.9–5.1 V, no appreciable ripple.
3. If OK, raise current limit to 2 A and retest rails.

## 3) Add Arduinos Only
1. Plug in both Nano Every boards; keep motor drivers/servos disconnected.
2. Power the main board from bench supply (still ~18–20 V, limit 2 A).
3. Verify 5 V rails stay within spec; boards enumerate over USB.

## 4) Servo Rail Check
1. Connect one servo to Servo1 header.
2. Upload `servo1_test.ino` (Every 2). Run for 1–2 minutes; watch rail droop and noise. Repeat for other channels as needed.
3. If stable, connect up to four servos and run `arduino_every2_test.ino` to sweep sequentially. Monitor total supply current and any brownout of logic rails.

## 5) Motor/Encoder Side
1. Connect motor driver harnesses and encoders to Every 1 side.
2. Upload `left_side_test.ino` and `right_side_test.ino` individually to verify each side drives and encoders count.
3. Then load `arduino_every1_test.ino` to exercise both sides with ramp/brake and capture encoder snapshots. Expect encoder counts to rise when wheels spin and link pings to Every 2 if connected.

## 6) Inter-Arduino Link
1. With both sketches (`arduino_every1_test.ino` on Every 1, `arduino_every2_test.ino` on Every 2), verify periodic `PING/ACK` at 38 400 baud over D11/D12.
2. Check that Every 1 reports servo ID and active flag in the ACK summary; no link timeouts should accumulate.

## 7) Full Stack (optional Pi)
1. Connect Raspberry Pi to the Pi 5 V rail; keep servos connected.
2. Power from bench supply at 20–22 V, limit 5 A. Confirm Pi boots and rails hold >4.9 V under servo sweeps and motor ramps at low duty.

## 8) Fault/Protection Checks
1. Brownout simulation: temporarily add a 1–2 Ω load to the servo rail during a sweep; confirm Arduinos stay powered and no resets occur.
2. Fuse/overcurrent sanity: briefly exceed normal load (e.g., stall one motor at low PWM) while watching supply current. Stop if the fuse runs hot or rails sag hard.

## 9) Pass/Fail Notes
- All three 5 V rails within 4.9–5.1 V no-load and under typical servo/motor test loads.
- No Arduino resets during servo sweeps or motor ramps.
- Encoders count correctly; link PING/ACK shows no errors.
- No excessive heating on bucks or headers during 5–10 minute mixed actuator exercise.

## If Issues Arise
- Rail droop/noise: add temporary bulk on the affected rail; check connector seating.
- Link errors: re-seat D11/D12 wires; confirm baud at 38 400.
- Encoder miscounts: verify A/B wiring and pull-ups; swap A/B if counts decrease in forward.

