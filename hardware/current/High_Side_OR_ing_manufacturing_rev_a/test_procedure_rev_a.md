# LM5050 Redundant Supply Board (High Side ORing) - Rev A
## Bench Test & Validation Procedure

Rev A uses the LM5050-1 Typical Redundant Supply Configuration to auto-select between an `18 V` battery rail and a `36 V` boost rail.

### 0) Equipment
- Two bench supplies with current limit:
  - Supply A (battery emulation): 0-24 V, >=5 A
  - Supply B (boost emulation): 0-40 V, >=5 A
- DMM (2 preferred for simultaneous VIN/VOUT checks).
- Oscilloscope (>=100 MHz) for switchover and transients.
- Electronic load or resistor load for expected current range.
- Clamp meter (optional) for input path current confirmation.

### 1) Visual / Continuity (Unpowered)
1. Inspect orientation and soldering of LM5050 and power MOSFETs.
2. Verify input connector polarity and output connector labeling.
3. DMM checks: `VIN_18` to GND open, `VIN_36` to GND open, `VOUT` to GND open.
4. Check for no hard short between `VIN_18`, `VIN_36`, and `VOUT`.

### 2) Single-Source Test (18 V Path)
1. Set Supply A to `18.0 V`, ILIM `0.5 A`; keep Supply B OFF.
2. Power ON and confirm `VOUT` rises and follows the active path.
3. Apply a light load (for example `0.25-0.5 A`) and verify stable output.
4. Log `VIN_18`, `VOUT`, and input current.

### 3) Single-Source Test (36 V Path)
1. Set Supply B to `36.0 V`, ILIM `0.5 A`; keep Supply A OFF.
2. Power ON and confirm `VOUT` follows the `36 V` path.
3. Apply the same light load and verify stable output.
4. Log `VIN_36`, `VOUT`, and input current.

### 4) Dual-Source Priority Check (Auto-Select)
1. Enable both sources: `VIN_18 = 18.0 V`, `VIN_36 = 36.0 V`.
2. Confirm the higher rail path (`36 V`) supplies the output.
3. Measure current from each supply:
   - `VIN_36` should carry load current.
   - `VIN_18` should be near zero (leakage only).
4. Record steady-state values under no-load and light-load.

### 5) Switchover: 36 V -> 18 V
1. Start with both sources ON and a moderate load.
2. Disable `VIN_36` while monitoring `VOUT` on scope.
3. Confirm transfer to `VIN_18` without abnormal drop or oscillation.
4. Re-enable `VIN_36` and verify return to higher-source operation.

### 6) Reverse Blocking Validation
1. Keep `VIN_18` active, set `VIN_36` OFF (or at `0 V`).
2. Confirm no significant reverse current from active output path into the inactive source.
3. Repeat with `VIN_36` active and `VIN_18` inactive.
4. Fail if measurable backfeed exceeds your design leakage expectation.

### 7) Load Sweep
1. With both supplies available, step load from light to target operating current.
2. At each step, record `VOUT`, source currents, and thermal behavior.
3. Verify stable operation through the expected continuous current range.
4. Stop if component case temperature approaches your defined limit.

### 8) Start/Stop and Disturbance Checks
1. Perform repeated ON/OFF cycles for each source independently.
2. Perform repeated ON/OFF cycles with both sources present.
3. Confirm no latch-up, no unstable oscillation, and repeatable startup.

### 9) Post-Test Inspection
- Power down and allow caps to discharge.
- Inspect for discoloration, solder reflow signs, or hot-spot damage.
- Save waveform captures and measured values for traceability.

### Pass/Fail (Quick)
- Board powers correctly from `18 V` source alone.
- Board powers correctly from `36 V` source alone.
- With both sources active, board selects the higher source path.
- Switchover between sources is stable and repeatable.
- Reverse current into inactive source remains within expected leakage limits.
