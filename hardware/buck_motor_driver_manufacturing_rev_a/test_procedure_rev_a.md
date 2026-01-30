# Buck Converter (on Buck + Motor Driver Board) — Rev A
Bench test plan focused on the **buck stage** only. Topology matches the LM5146 5 V / 12 A reference design (300 kHz sync, UVLO 8 V on / 7 V off, ~6 ms soft-start). Validate against installed component voltage/current ratings on your Rev A build (caps/FETs/inductor); do not exceed the lowest-rated part.

## 0) Equipment
- Bench supply 0–60 V / ≥15 A, current limit adjustable (start low). Use sense leads.
- Signal generator (square) 300 kHz, 0–5 V for SYNC (optional free-run test with generator removed).
- DMM; oscilloscope (≥100 MHz) for ripple, soft-start, and transient capture; differential probe recommended for SW if probed.
- Electronic load capable of 0–12 A at 5 V, transient mode up to 5 A steps; or resistors sized for 5 V 2–12 A (2.5 Ω/25 W, 1 Ω/50 W, 0.42 Ω/75 W).
- Thermometer/IR or quick touch (brief) for FET/inductor/caps temps.

## 1) Visual & Continuity (unpowered)
1. Verify component voltage ratings: input ceramics/electrolytics, MOSFETs, inductor, diode. Ensure they meet planned VIN (up to the lowest rated part).
2. Inspect controller pin solder, SYNC pin access, CS/FB network, bootstrap cap, and inductor seating.
3. DMM continuity (beep):
   - VIN–GND: open.
   - VOUT–GND: open.
   - VIN–VOUT: open (no hard short).

## 2) UVLO Check (targets 8 V on / 7 V off)
1. No load. Set VIN = 6 V, ILIM = 0.5 A. Slowly ramp up while watching VOUT/PG (if available).
2. Record VIN where VOUT first rises (UVLO ON ≈ 8 V). Ramp down and note VIN where VOUT turns off (UVLO OFF ≈ 7 V). If thresholds differ, log actuals.

## 3) No-Load Power-Up (soft-start)
1. VIN = 12 V, ILIM = 1 A. No load.
2. Scope VOUT; measure soft-start time (target ~6 ms). Check overshoot (<50 mV) and steady VOUT ≈ 5.0 V ±1%.
3. Repeat at VIN = 24 V and (if component ratings allow) VIN = 48 V to observe consistency.

## 4) Switching Frequency (SYNC tied to VCC)
Since SYNC is hard-wired to VCC on your build, the controller free-runs at the RRT-set frequency (target ~250 kHz). There is no external sync input available.
1. Measure switching frequency at SW with scope/FFT; confirm ≈250 kHz.
2. Verify VOUT remains in regulation at this frequency across VIN and load steps.

## 5) Light Load
1. Apply 0.5 A load (≈10 Ω). ILIM = 2 A.
2. Verify VOUT within ±1%; ripple <50–80 mVpp. Components should stay cool.

## 6) Mid Load (2–6 A)
1. Increase load in 1 A steps to 6 A. ILIM = 8 A.
2. At each step, log VOUT and ripple (<80–100 mVpp). Watch temps; stop if >80 °C case or audible instability.

## 7) High Load (up to design 12 A, short duration)
1. Set load to 8 A, then 10 A, then **12 A for ≤30 s** each. ILIM = 15 A.
2. VIN = 24 V. If component ratings allow, repeat at VIN = 36 V and 48 V. Abort if VOUT droop >150 mV, switching noise surges, or temps climb rapidly.

## 8) Line Sweep (design targets)
1. Hold load at 4 A. Sweep VIN: 12 V → 24 V → 36 V → (optional, if rated) 48 V.
2. Confirm regulation ±1%, no jitter/hiccup. Note efficiency points if measuring Pin/Pout (targets ~94% at 24 V, ~92% at 48 V for the reference design).

## 9) Load Transient (spec: <100 mV deviation)
1. VIN = 24 V. Program e-load for 1 A ↔ 6 A step at ~1 kHz (or fastest reliable on your load).
2. Capture VOUT deviation; target peak sag/overshoot <100 mV. Note recovery time and any ringing.
3. Repeat at VIN = 48 V if components are rated.

## 10) Extended Dwell
1. VIN = 24 V, load 4–5 A; run 10 min. If stable and thermals acceptable, optionally run 6–8 A for 5 min.
2. Abort if VOUT droop >150–200 mV, ripple spikes, or temps exceed ~90 °C case.

## 11) Post-Test
- Power down; discharge output caps; inspect for discoloration/odor.
- Log UVLO thresholds, soft-start time, free-run and sync frequencies, VOUT/ripple vs load, transient deviation, and max temps.

## Pass/Fail (quick checklist)
- UVLO near 8 V on / 7 V off (record actual).  
- Soft-start clean, ~6 ms, no overshoot.  
- Free-run ≈250 kHz; locks to 300 kHz SYNC.  
- VOUT within ±1% through 0.5–10 A; transient deviation <100 mV on 1 A↔6 A step.  
- Stable regulation across tested VIN (not exceeding lowest-rated part); no hiccup/oscillation.  
- Thermals acceptable during 10 min dwell at 4–5 A and short 12 A burst; no component damage.  
