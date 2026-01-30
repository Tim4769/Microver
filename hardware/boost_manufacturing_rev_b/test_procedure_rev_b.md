# Boost Converter (LM5122-Q1) — Rev B
## Bench Test & Validation Procedure

Rev B updates: C1 removed (low rating), C2/C7 upgraded to 50 V, added input bulk C12/C13 (470 µF) and C14 (47 µF). Follow this plan before full deployment.

### 0) Equipment
- Bench supply 0–30 V / ≥15 A with CC limit; sense leads recommended.
- DMM; oscilloscope (≥100 MHz) for VOUT ripple and startup.
- Loads: electronic load or resistors capable of 36 V at 1–10 A (e.g., 3.6 Ω/150 W, 7 Ω/50 W). Start low.
- Shorting tool for brief VOUT shorts.

### 1) Visual / Continuity
1. Verify new input bulk caps (C12/C13/C14) polarity/clearance; ensure C1 pads are unpopulated/clean.
2. Check C2/C7 are 50 V parts; confirm FET/inductor orientation and solder.
3. DMM: VIN–GND open; VOUT–GND open; VIN–VOUT open/high (body diode path only).

### 2) No-Load Start
1. VIN = 18 V, ILIM = 0.5 A. No load.
2. Power ON; expect VOUT ~36 V regulated, input current tens of mA, no overshoot >1 V.
3. If current limit trips or VOUT absent, power OFF and inspect.

### 3) Startup Waveform
1. VIN = 20 V, ILIM = 2 A. Scope VOUT (CH1) and VIN (CH2).
2. Enable; record rise time and overshoot (should be minimal). Check for ringing on SW if probed.

### 4) Light Load
1. Apply ~1 A load at 36 V (≈36 Ω). ILIM = 3 A.
2. Verify regulation (±2%) and ripple within design expectations (<100–150 mVpp typical). Temps should stay cool.

### 5) Moderate Load
1. Increase load to ~5 A. ILIM = 8–10 A.
2. Run 60–120 s; monitor VOUT droop, ripple, and temps of FETs, diode, inductor, sense resistor. Stop if >80–90 °C case.

### 6) Line Sweep
1. Hold ~3 A load. Sweep VIN: 18 V → 22 V → 25 V.
2. Confirm stable regulation; note efficiency if measuring Pin/Pout. No hiccup/oscillation.

### 7) Short / Current Limit
1. No load. VIN = 20 V, ILIM = 8–10 A.
2. Briefly short VOUT to GND (<0.5 s). Expect current limit/hiccup with recovery on release. No damage or latch-up.

### 8) Extended Dwell
1. Load 3–4 A at 36 V; VIN 20–22 V. Run 10 minutes. Watch temps; VOUT droop should remain small (<200 mV typical). If stable, optionally test 5–6 A for 3–5 minutes.

### 9) Post-Test
- Power down, discharge output caps, inspect for discoloration or vented parts.
- Log VIN/VOUT, load, ripple, temps, startup behavior, and short-test result.

### Pass/Fail (quick)
- Clean start at 18–22 V, VOUT ≈36 V, no overshoot.
- Holds regulation at 1–5 A with acceptable ripple and temps.
- Survives brief short without damage.
- Stable across VIN sweep; no oscillation or excessive heating.
