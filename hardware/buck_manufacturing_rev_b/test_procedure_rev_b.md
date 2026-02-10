# Buck Converter — Rev B
## Bench Test Procedure

Rev B is a buck-only spin (motor driver removed from KiCad). Test focuses solely on the buck rail behavior, value corrections, and feedback rewiring fix.

### 0) Equipment
- Bench supply 0–30 V / ≥10 A with current limit (start low).
- DMM; oscilloscope for ripple/soft-start.
- Electronic load or resistors for 5 V at 0.5–10 A (2.5 Ω/25 W, 1 Ω/50 W, 0.5 Ω/50–75 W). Keep high-current runs short.

### 1) Visual / Continuity
1. Confirm Rev B MPN swaps populated (R2/R3/R4/R5/R8/R20, C8/C13/C14/C17, cost-down caps/diode) and R19 removed. Verify added output caps C19/C20/C22/C23 are fitted and via stitching present around the buck area (keep-out under inductor).
2. DMM: VIN–GND open; VOUT–GND open; VIN–VOUT open (no short).
3. Status LED check (PGOOD tied): Red LED ON means PGOOD low (power not good or still booting); LED OFF means PGOOD floating/high (power good).
4. Net sanity: RT resistor should terminate at RT pin (not SS/TRK); soft-start cap should terminate at SS/TRK; FB pin should connect to the R8/C17/R9 feedback/comp network per the Rev B schematic.

### 2) UVLO / Soft-Start (buck)
1. No load. Set VIN = 6 V, ILIM = 0.5 A. Ramp up slowly and note UVLO turn-on; then ramp down to find turn-off. Record both.
2. VIN = 12 V, ILIM = 1 A. Scope VOUT to measure soft-start (target few ms, no overshoot). Verify VOUT ≈5.0 V ±1%.

### 3) Switching Frequency
- SYNC tied to VCC (free-run). Measure SW node frequency; expect ~250 kHz (set by RRT). Verify regulation holds.

### 4) Light Load
1. Apply 0.5 A load (≈10 Ω). ILIM = 2 A.
2. Check VOUT regulation and ripple (<80 mVpp). Components should remain cool.

### 5) Mid Load
1. Step load to 2 A, 4 A, 6 A. Raise ILIM to 8 A.
2. At each step, log VOUT and ripple; stop if droop >150 mV or temps >80 °C case.

### 6) High Load (short duration)
1. VIN = 24 V. Load 8–10 A for ≤30 s, then 12 A for ≤15 s. ILIM 12–15 A.
2. Pass if VOUT stays within tolerance and no audible instability; stop if heating rises quickly.

### 7) Line Sweep
1. Hold 3–4 A load. Sweep VIN: 12 V → 18 V → 24 V → 28 V (do not exceed lowest-rated component). Confirm stable regulation and ripple.

### 8) Load Transient (if e-load supports)
1. VIN = 24 V. Program 1 A ↔ 6 A step at ~1 kHz. Capture VOUT deviation; aim for <100 mV peak and fast recovery without ringing.

### 9) Post-Test
- Power down, discharge caps, inspect for heat discoloration.
- Log UVLO, soft-start time, frequency, VOUT vs load, transient results, temps.

### Pass/Fail (quick)
- UVLO/soft-start clean; VOUT ≈5 V, no overshoot.
- Stable regulation through 0.5–6 A continuous and short 10–12 A bursts without oscillation.
- Acceptable ripple and thermals; no component damage.
- Stable buck rail only (motor driver not populated in this spin).
