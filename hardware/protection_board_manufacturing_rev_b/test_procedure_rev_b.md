# Power Protection Board — Rev B
## Bench Test & Validation Procedure (5S-tuned version)

Rev B retunes UVLO/OVLO for a 5S pack (R3=2 kΩ, R5=24 kΩ, R7=3 kΩ). Use this procedure for boards stuffed to Rev B values.

### 0) Equipment & Setup
- Bench supply with CC limit (0–30 V, ≥5 A), sense leads ideal.
- DMM; oscilloscope for ramp/PGD timing.
- Load: start with 2–3 Ω / 50 W resistor or e-load; later real system load.
- Shorting tool for brief VOUT-to-GND short tests.
- PGD pull-up to 3.3 V or 5 V (10–47 kΩ), common ground.
- Keep VIN leads short and balanced; same gauge for VIN and GND.

### 1) Visual / Continuity (unpowered)
1. Check SOT-23 orientation, TVS polarity, and sense resistor soldering. The VIN electrolytic bulk is DNP in Rev B to avoid reverse-polarity damage; if a cap is installed, verify its polarity.
2. Continuity: VIN+ to GND open; VOUT+ to GND open; VIN+ to VOUT+ open/high (body diode only); PGD to GND open.
3. LM74700 charge-pump sanity: ANODE and VCAP must not be shorted. Verify the charge-pump capacitor is connected between ANODE and VCAP (one terminal on each pin).

### 2) Initial Power-On (no load)
1. Set VIN = 18.5 V (5S nominal), ILIM = 0.5 A. No load.
2. Power ON. Expect dv/dt ramp to VOUT ≈ VIN; current a few mA after ramp. PGD LOW during ramp, then HIGH when stable.
3. If current hits limit or VOUT stalls, power OFF and inspect.

### 3) Reverse Polarity Check
1. Power OFF. Swap supply leads, VIN = 12 V, ILIM = 0.5 A.
2. Enable briefly. Expect near-zero current, VOUT ≈ 0 V, PGD LOW. If current spikes, stop and recheck ideal diode circuit.
3. Restore correct polarity.

### 4) PGD Timing / dv/dt
1. VIN = 20 V, ILIM = 2 A. Scope VOUT and PGD.
2. Enable; record rise time (tens of ms) and PGD delay relative to VOUT reaching ~90–95% VIN. No overshoot expected.

### 5) Load Test (normal operation)
1. Connect ~3 A load at 20 V (≈7 Ω). ILIM = 5 A.
2. Verify VOUT ≈ VIN with minimal droop; PGD HIGH; monitor MOSFET temps (warm at most for short test).
3. Step VIN: 18 V → 22 V → 23 V; PGD should stay HIGH, no chatter.

### 6) Current Limit / Short Behavior
1. Remove load. VIN = 20 V, ILIM = 8 A.
2. After PGD HIGH, briefly short VOUT to GND (<0.5 s).
   - Expect LM5069 current limit then fault timeout (~320 ms), PGD LOW, output off.
3. Clear short; power-cycle VIN (or toggle EN if populated) to recover; confirm PGD HIGH and normal output.

### 7) UVLO/OVLO Verification (Rev B targets 5S)
1. No load, ILIM = 0.5 A. Start VIN at 14 V.
2. Ramp up slowly; note PGD LOW→HIGH (UVLO rising). Target ≈15.0–16.0 V.
3. Continue up; note PGD HIGH→LOW (OVLO). Target ≈22.5–23.0 V.
4. Ramp down; note falling thresholds (~0.3–0.5 V lower than rising). Log actuals.

### 8) Hot-Plug / Inrush
1. VIN preset 20 V, ILIM = 5 A, supply off. Connect board, then hot-plug ON.
2. Scope VOUT; expect controlled ramp, no overshoot. Repeat at 23 V. Abort if overshoot >1 V or audible arcing.

### 9) Dwell Test
1. Load 2–3 A at 20–22 V. Run 10 minutes. Monitor temps of MOSFETs, sense resistor, TVS, LM5069. PGD should stay HIGH; VOUT droop minimal (<150 mV typical).

### 10) Record & Sign-off
- Log measured UVLO/OVLO, rise time, PGD delay, current-limit response, load voltages, and temperatures.
- Pass if: reverse protection blocks current; controlled ramp; PGD behavior correct; holds 3 A for dwell; current limit trips and recovers; thresholds within expected 5S window.
