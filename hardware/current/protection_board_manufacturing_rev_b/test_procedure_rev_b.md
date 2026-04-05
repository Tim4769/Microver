# Power Protection Board - Rev B

Short validation for the 5S-tuned protection board. Rev B targets a 5S pack with UVLO around 15-16 V and OVLO around 22.5-23.0 V.

## Equipment
- Bench supply, 0-30 V, with current limit
- DMM and scope
- 3 A load or electronic load
- PGD pull-up to 3.3 V or 5 V

## Quick Test
1. Unpowered: inspect the SOT-23 parts, TVS, sense resistor, and charge-pump capacitor. Confirm ANODE and VCAP are not shorted, and there is no short on VIN+, VOUT+, or PGD.
2. Normal startup: at 18.5 V / 0.5 A with no load, VOUT should ramp up to VIN and PGD should go high once stable.
3. Reverse polarity: briefly apply 12 V with reversed leads. Current should stay near zero, VOUT should stay near 0 V, and PGD should stay low.
4. Load test: at 20 V, apply about 3 A. VOUT should stay close to VIN, PGD should stay high, and temperatures should stay reasonable.
5. Fault test: at 20 V, briefly short VOUT to GND for less than 0.5 s. The board should current-limit, fault, and recover after a power cycle or EN toggle.
6. Threshold check: slowly sweep VIN and record UVLO and OVLO. Targets are about 15-16 V rising for UVLO and about 22.5-23.0 V for OVLO, with a little hysteresis.
7. Optional hot-plug and dwell: hot-plug at 20-23 V and run 2-3 A for 10 minutes. The ramp should stay controlled and PGD should not chatter.

## Pass
- Reverse polarity is blocked
- Startup ramp is clean and PGD behaves correctly
- Board carries about 3 A without excessive droop or heat
- Current limit trips and the board recovers normally
