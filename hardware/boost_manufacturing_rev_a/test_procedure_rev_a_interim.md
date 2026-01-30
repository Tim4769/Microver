# Boost Converter — Rev A (Interim Test Plan)
## Scenario
Bench-test Rev A after removing C1 and swapping C2/C7 to higher-voltage parts (no added input caps C12/C13/C14). Goal: verify safe operation before respinning Rev B.

## 0) Prep
- Remove C1 (47 µF, 10 V). Leave pads open.
- Swap C2 and C7 to available 50 V parts (per Rev B: C13967 and C5378). Keep all other parts as Rev A.
- Tools: bench supply 0–30 V / ≥10 A with current limit, DMM, scope, 1–2 Ω / 200 W load or e-load, shorting bar for brief tests.
- Wiring: short, thick leads; sense leads on VIN if available.

## 1) Visual / Continuity
1. Inspect swapped caps for correct polarity and clearance; ensure removed C1 pads are clean (no solder balls).
2. DMM continuity: VIN+ to GND open; VOUT+ to GND open; VIN+ to VOUT+ shows body-diode path only (no hard short).

## 2) Cold Power-Up (no load)
1. Set VIN = 18 V, ILIM = 0.5 A. No load connected.
2. Enable supply. Expected: VOUT ramps to ~36 V (regulated). Input current tens of mA. No overshoot >1 V.
3. If current-limit hits or VOUT collapses, power off and inspect swaps.

## 3) Soft-Start / Waveform Capture
1. VIN = 20 V, ILIM = 2 A. Scope CH1 on VOUT, CH2 on VIN.
2. Enable. Confirm clean ramp to 36 V, minimal ringing. Record rise time and any overshoot.

## 4) Light Load
1. Apply ~1 A load at 36 V (≈36 Ω or e-load CC). ILIM = 3 A.
2. Check VOUT regulation (±2%) and ripple. MOSFETs/inductor cool to mild warm.

## 5) Moderate Load
1. Increase load to ~5 A at 36 V. ILIM = 8–10 A.
2. Monitor VOUT droop, ripple, and temperatures for 60–120 s. Acceptable: VOUT within spec, no audible instability, temps under ~80 °C case (brief touch/IR).

## 6) Line Sweep
1. Hold load at ~2–3 A. Sweep VIN: 18 V → 22 V → 25 V in steps.
2. Confirm stable regulation, no hiccup/skip. Note any audible change.

## 7) Fault / Overcurrent Check (short tap)
1. No load. VIN = 20 V, ILIM = 8–10 A.
2. Briefly tap VOUT to GND (<0.5 s). Expect current limit then controller hiccup/restart; no damage or latch-up. Allow cool-down afterward.

## 8) Extended Dwell
1. Run 3–4 A load at 36 V for 10 minutes (VIN = 20–22 V). Watch temps on FETs, diode, inductor, sense resistor. Stop if discoloration or >90 °C case.

## 9) Post-Test
- Recheck continuity, look for discoloration or vented caps.
- Log: VIN, VOUT, load currents, ripple, temps, any anomalies during sweep/short.

## Pass/Fail Quick Criteria
- Starts cleanly at 18–22 V with no load.
- Holds 36 V within tolerance at 1–5 A loads without oscillation.
- Survives brief output short without damage.
- Thermal rise acceptable under 5 A for short runs and 3–4 A for 10 min dwell.
