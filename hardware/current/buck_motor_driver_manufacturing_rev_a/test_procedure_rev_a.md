# Buck Converter on Buck + Motor Driver Board - Rev A

This is a short bench check for the buck stage only. Stay below the lowest-rated part on your build.

## Equipment
- Bench supply, up to your board rating, with current limit
- DMM and scope
- Load for 5 V, 0.5-12 A

## Quick Test
1. Unpowered: inspect the controller, bootstrap parts, inductor, and feedback network. Confirm VIN to GND, VOUT to GND, and VIN to VOUT are not shorted.
2. UVLO and startup: with no load, ramp VIN from 6 V and record where the rail turns on and off. Then test at 12 V and confirm VOUT = 5.0 V +/-1% with a soft-start around 6 ms and no meaningful overshoot.
3. Frequency: SYNC is tied to VCC on this board, so the converter should free-run at about 250 kHz.
4. Load: test 0.5 A, then step up to 2 A, 4 A, and 6 A. If stable, do short checks at 8 A, 10 A, and 12 A with 24 V input. Stop for droop above about 150 mV, instability, or case temperatures above about 80-90 C.
5. Line check: if the fitted parts are rated for it, repeat the regulation check at 24 V, 36 V, and 48 V input.
6. Optional transient: at 24 V, step 1 A to 6 A and back. Aim for less than about 100 mV deviation.

## Pass
- Clean startup and correct 5 V output
- Stable operation through the tested load range
- About 250 kHz switching with no hiccup or oscillation
- Thermals stay reasonable during short high-load runs
