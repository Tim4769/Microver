# Power Protection Board — Rev A
## Bench Test & Validation Procedure (Step-by-Step)

### 0) Equipment & Setup
- Bench supply with CC limit (0–30 V, ≥5 A), sense leads if available.
- DMM (voltage + continuity); optional oscilloscope for ramp/PGD timing.
- Known load: start with 1–2 Ω / 50 W resistor (or electronic load), later real system load.
- Shorting tool: momentary-rated jumper or toggle to briefly short VOUT to GND.
- Logic pull-up for PGD: 3.3 V or 5 V through 10–47 kΩ; logic reference ground common with board.
- Cables: keep VIN leads short; use same gauge for GND and VIN.

### 1) Visual & Continuity Checks (unpowered)
1. Inspect for solder bridges, rotated parts (pay attention to SOT-23 orientation, TVS polarity, electrolytic caps polarity).
2. Verify pass FET pads wetted and no debris between pins.
3. Continuity with DMM (beeper):
   - VIN+ to VIN- (GND): open (>100 kΩ).
   - VOUT+ to VOUT- (GND): open.
   - VIN+ to VOUT+: ~>100 kΩ (through MOSFET body diode, may read mega-ohms forward-blocking).
   - PGD pad to GND: open.

### 2) Initial Power-On (no load) — 6S validation first
1. Bench supply to VIN, current limit = 0.5 A, set VIN = 22.2 V (6S nominal). Do **not** connect load.
2. Enable supply. Expected:
   - Inrush dv/dt ramp; VOUT rises smoothly to VIN (small delay from LM5069 soft-start).
   - Supply current: a few mA after ramp.
   - PGD: LOW during ramp, then HIGH when VOUT within window (use pull-up and DMM/scope).
3. If current hits limit or VOUT stalls, power off and inspect.

### 3) Reverse Polarity Check
1. Turn supply off. Swap leads (VIN– to +, VIN+ to –). Set current limit 0.5 A, VIN = 12 V.
2. Enable. Expected: almost zero current (< a few mA), VOUT ≈ 0 V, PGD LOW. Turn off immediately if current spikes.
3. Restore correct polarity before continuing.

### 4) PGD Timing & dv/dt Ramp
1. Correct polarity; VIN = 20 V, current limit 2 A.
2. Scope channels: CH1 on VOUT, CH2 on PGD (with pull-up). Trigger on VIN enable.
3. Enable supply. Measure:
   - VOUT rise time (controlled by dv/dt cap ~150 nF). Expect smooth ramp (tens of ms range, no overshoot).
   - PGD goes HIGH after VOUT is stable; note delay vs VOUT reaching ~90–95% VIN.
4. Record rise time and PGD delay for log.

### 5) Load Test — Normal Operation
1. Connect resistive load that draws ~2–3 A at 20 V (e.g., 7–10 Ω / 50 W). Current limit 5 A.
2. Power on. Expected: VOUT ≈ VIN with minimal droop, PGD HIGH, supply current ≈ load current.
3. Monitor MOSFET temperature (touch/IR) — should be warm at most for short test.
4. Step VIN from 18 V → 22 V → 25 V while watching PGD stays HIGH and no audible chatter.

### 6) Current Limit / Short-Circuit Behavior
1. Remove resistive load. Current limit 5–8 A.
2. Power on at 20 V, wait for PGD HIGH.
3. Briefly short VOUT to GND (≤0.5 s) with momentary jumper.
   - Expected: LM5069 enforces current limit then times out (~320 ms) and latches OFF; PGD goes LOW.
   - Supply current should not exceed limit; no damage or excessive heating.
4. Clear short, power-cycle VIN (or toggle EN if available) to recover. Confirm PGD returns HIGH and VOUT normal.

### 7) UVLO/OVLO Window Check (Rev A as-built, then optional 5S retune)
1. No load. Start VIN at 18 V (lower bound for 6S), limit 0.5 A.
2. Increase VIN slowly and note PGD transition LOW→HIGH (UVLO upper threshold). Record value.
3. Continue raising VIN and note PGD HIGH→LOW (OVLO) if present; for 6S expect window near 22–25 V depending on stuffing.
4. Decrease VIN and capture hysteresis points (PGD drops slightly below the rising thresholds).
5. **If 6S results pass and you want 5S operation:** power down, replace R3→2 kΩ, R5→24 kΩ, R7→3 kΩ (Rev B values), then repeat Steps 2–7 with VIN sweep 14–23 V; expect UVLO ~15–16 V and OVLO ~22–23 V for 5S.

### 8) Hot-Plug / Inrush Observation
1. Set supply to 20 V, limit 5 A, output OFF.
2. Connect board first, then hot-plug supply ON. Watch VOUT with scope for overshoot and current spike shape (should show controlled ramp, no large overshoot).
3. Repeat with 25 V, same limit. Abort if overshoot >1 V above VIN or audible clicks/arcs.

### 9) Long Dwell at Moderate Load
1. Attach 2–3 A load at 20–22 V.
2. Run for 10 minutes; monitor MOSFETs, sense resistor, TVS, and LM5069 temperature (finger/IR).
3. PGD should remain HIGH; VOUT droop minimal (<100–150 mV typical). No smell/discoloration.

### 10) Documentation & Sign-off
- Log all measured thresholds: UVLO/OVLO up/down, ramp time, PGD delay, current-limit response.
- Record ambient temperature and load used.
- Note any anomalies (PGD chatter, audible buzz, overheating). If present, recheck sense resistor value, dv/dt capacitor, and gate resistors.

### Pass/Fail Criteria (quick checklist)
- Reverse protection blocks current; no heat or damage.
- Controlled VOUT ramp; PGD behaves: LOW during ramp/fault, HIGH when stable.
- Carries 3 A continuous for short dwell without excessive heating.
- Current limit engages and recovers after short; no latch-up/damage.
- UVLO/OVLO thresholds within expected band for Rev A resistor values.
