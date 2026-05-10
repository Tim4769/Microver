# Boost Converter - Rev B

Short bench check for the 36 V LM5122-Q1 boost board. Rev B adds higher-voltage caps, extra input bulk, and an SS pull-down for on/off control.

## Equipment
- Bench supply, 0-30 V, with current limit
- DMM and scope
- Load for 36 V, about 1-10 A

## Quick Test
1. Unpowered: confirm C1 is not fitted, C2/C7 are 50 V parts, the new bulk caps are installed correctly, the SS pull-down MOSFET is oriented correctly, and there is no short on VIN, VOUT, or VIN-to-VOUT.
2. Start with no load at 18 V / 0.5 A. VOUT should rise to about 36 V with no big overshoot and only light input current after startup.
3. At 20 V, capture startup on the scope. The ramp should be clean. Then toggle the SS control: the converter should shut down cleanly and restart with a fresh soft-start.
4. Load test at about 1 A, then about 5 A. Regulation should stay within about +/-2%, ripple should stay reasonable, and hot parts should stay below about 80-90 C.
5. Sweep VIN through 18 V, 22 V, and 25 V while holding a moderate load. The output should stay stable.
6. Brief short check: at 20 V, momentarily short VOUT to GND for less than 0.5 s. The board should current-limit or hiccup and recover after the short is removed.

## Pass
- Clean startup to about 36 V
- SS control can stop and restart the converter
- Stable output through the normal load range
- No damage after the short test
