# Buck Converter - Rev B

Short bench check for the 5 V buck-only board. Focus on the corrected feedback wiring and value updates.

## Equipment
- Bench supply, 0-30 V, with current limit
- DMM and scope
- Load for 5 V, 0.5-12 A

## Quick Test
1. Unpowered: confirm the Rev B part swaps are fitted, R19 is removed, the added output caps and stitching vias are present, and there is no short from VIN to GND, VOUT to GND, or VIN to VOUT.
2. Startup: no load, ramp VIN from 6 V with 0.5 A limit and record UVLO on/off. Then test at 12 V / 1 A and confirm clean soft-start with VOUT = 5.0 V +/-1%.
3. Switching: check the SW frequency. Target is about 250 kHz with SYNC tied to VCC.
4. Load: test 0.5 A, then 2 A, 4 A, and 6 A. Pass if ripple and droop stay small and case temperature stays below about 80 C.
5. Short stress: at 24 V, run 8-10 A for up to 30 s and 12 A for up to 15 s only if the board stays stable.
6. Optional transient: at 24 V, step 1 A to 6 A and back. Aim for less than about 100 mV deviation.

## Pass
- Clean UVLO and soft-start
- 5 V output stays in regulation through the tested load range
- No oscillation, instability, or obvious overheating
