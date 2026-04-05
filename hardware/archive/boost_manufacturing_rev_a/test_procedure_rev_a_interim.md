# Boost Converter - Rev A Interim

Short bench check for Rev A after removing C1 and replacing C2/C7 with 50 V parts. Use this only for the interim Rev A build.

## Equipment
- Bench supply, 0-30 V, with current limit
- DMM and scope
- Load for 36 V, about 1-5 A

## Quick Test
1. Prep: C1 should be removed and C2/C7 should be 50 V parts. Inspect the board and confirm there is no short on VIN, VOUT, or VIN-to-VOUT.
2. Start with no load at 18 V / 0.5 A. VOUT should rise to about 36 V with no big overshoot.
3. At 20 V, capture startup on the scope. The ramp should be clean and controlled.
4. Load test at about 1 A, then about 5 A. Output should stay within about +/-2%, with no audible instability or fast heating.
5. Sweep VIN through 18 V, 22 V, and 25 V while holding a moderate load. Regulation should stay stable.
6. Brief short check: at 20 V, momentarily short VOUT to GND for less than 0.5 s. The board should current-limit or hiccup and recover.

## Pass
- Clean startup to about 36 V
- Stable output through the tested load range
- No damage after the short test
