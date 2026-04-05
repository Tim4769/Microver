# LM5050 Redundant Supply Board - Rev A

Short validation for the high-side OR-ing board that picks between 18 V and 36 V inputs.

## Equipment
- Two current-limited bench supplies
- DMM, and a scope if you want switchover captures
- Light to moderate load

## Quick Test
1. Unpowered: inspect the LM5050, MOSFETs, and connector polarity. Confirm VIN_18, VIN_36, and VOUT are not shorted to GND or to each other.
2. Single-source check: power the 18 V input alone, then the 36 V input alone. In both cases VOUT should follow the active source and hold a light load.
3. Priority check: turn both sources on at 18 V and 36 V. The 36 V path should carry the load and the 18 V path should sit near zero current.
4. Switchover: with both sources active and a moderate load, turn 36 V off and back on. VOUT should transfer cleanly to 18 V and then back to 36 V.
5. Reverse blocking: with only one input active, confirm the inactive input does not get back-fed beyond normal leakage.
6. Load sweep: step the load upward until the expected operating current. Stop for thermal issues or unstable output.

## Pass
- Both inputs work by themselves
- The higher rail wins when both are present
- Switchover is repeatable and clean
- Reverse current into the inactive source stays low
