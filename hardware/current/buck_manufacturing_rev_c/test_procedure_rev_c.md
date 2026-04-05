# Buck Converter - Rev C

Short bench check for the 5 V buck-only board. Focus on the corrected 5.0 V trim, parallel MOSFETs, gate resistors, and snubber.

## Equipment
- Bench supply, 0-30 V, with current limit
- DMM and scope
- Load for 5 V, 0.5-12 A

## Quick Test
1. Unpowered: verify R9 = 22.6 kOhm, R10 = 2 Ohm, R11 = 1 Ohm, C24 = 1 nF, R14/R15 = 2 Ohm, the extra MOSFETs are fitted correctly, and there is no short from VIN to GND, VOUT to GND, or VIN to VOUT.
2. Startup: no load, ramp VIN from 6 V with 0.5 A limit and note UVLO on/off. Then test at 12 V / 1 A and confirm clean soft-start with VOUT = 5.00 V +/-1%.
3. Switching: check the SW frequency. Target is about 250 kHz. The red LED should be on while power is bad or starting, and off once power-good is reached.
4. Load: test 0.5 A, then 2 A, 4 A, and 6 A. Pass if VOUT stays in spec, ripple stays reasonable, and case temperature stays below about 80 C.
5. Short stress: at 24 V, run 8-10 A for up to 30 s and 12 A for up to 15 s only if thermals look safe. Stop for fast heating, large droop, or audible instability.
6. Optional sweep: hold 3-4 A and sweep VIN through 12 V, 18 V, 24 V, and 28 V. Regulation should stay stable.

## Pass
- Clean UVLO and soft-start
- VOUT stays near 5 V through normal load
- No oscillation, severe ringing, or obvious MOSFET current-sharing imbalance
- No visible damage or overheating after test
