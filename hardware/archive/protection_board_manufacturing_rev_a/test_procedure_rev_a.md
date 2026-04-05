# Power Protection Board - Rev A

Short validation for the original protection board. Use Rev B values and the Rev B procedure if you are testing a 5S retuned board.

## Equipment
- Bench supply, 0-30 V, with current limit
- DMM and optional scope
- 2-3 A load
- PGD pull-up to 3.3 V or 5 V

## Quick Test
1. Unpowered: inspect polarity-sensitive parts and confirm VIN+, VOUT+, and PGD are not shorted to GND.
2. Normal startup: at 22.2 V / 0.5 A with no load, VOUT should ramp smoothly to VIN and PGD should go high once stable.
3. Reverse polarity: briefly apply 12 V with reversed leads. Current should stay near zero, VOUT should stay near 0 V, and PGD should stay low.
4. Load test: at 20 V, apply about 2-3 A. VOUT should stay close to VIN, PGD should stay high, and the board should only get mildly warm.
5. Fault test: at 20 V, briefly short VOUT to GND for less than 0.5 s. The board should current-limit, fault, and recover after a power cycle.
6. Threshold check: slowly sweep VIN and record the actual UVLO and OVLO points for the as-built Rev A resistor values.
7. Optional hot-plug and dwell: hot-plug at 20-25 V and run 2-3 A for 10 minutes. The ramp should stay controlled and PGD should not chatter.

## Pass
- Reverse polarity is blocked
- Startup and PGD behavior are clean
- Board carries the test load without excessive heat
- Short-circuit protection works and the board recovers
