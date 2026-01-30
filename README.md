# Microver

Integrated hardware + firmware stack for a small rover platform: power-entry protection, high-current motor drive, boost and buck converters, main rover PCB, and Arduino/Raspberry Pi control firmware. This repo packages manufacturing outputs (Gerbers/BOM/CPL), build/test notes, and firmware handoff material in one place.

## Repository Map (top level)
- `firmware/2025/` — Arduino sketches, diagnostics, and rover motion notes.  
  - `firmware/2025/knowledge base/` — Datasheets, design notes for drivers/LiDAR/PCBs.  
  - `firmware/2025/diagnostics/` — Bench test helpers.
- `hardware/` — KiCad projects and fabrication outputs for each board. See module summaries below.
- `assets/logos/` — Current logo assets; `assets/logos_legacy/` for older branding.
- `archive/2024_code/` — Legacy Arduino/Raspberry Pi experiments and reference code.
- `rover-software-handoff.md` — Raspberry Pi + dual Arduino Nano Every motion-stack pin maps, messaging, and validation steps.
- `LICENSE` — All rights reserved terms (permission required for any use).
- `NOTICE` — Rights/usage reminder and owner contact.

## Quick Start by Role
**Fabrication / PCB assembly**
- Pick the board + revision you need in `hardware/` (see summaries). Prefer the latest Rev unless a delta README says otherwise.
- Use the provided `Gerber/` + `Gerber.zip`, `BOM.csv`, and `CPL.csv` inside each board folder. Stack-up details are documented in each board README (common 4-layer HAL lead-free).
- For the power protection board, follow `hardware/protection_board_manufacturing_rev_a/test_procedure_rev_a.md` for bring-up; apply Rev B resistor values if building 5S-specific units.
- Regenerate outputs after any edits in KiCad (Gerbers, BOM, CPL, assembly drawings).

**Firmware / controls**
- Start with `firmware/2025/arduino_every1_test.ino` (DC drive + encoders) and `arduino_every2_test.ino` (servos). Hardware pin maps are in `rover-software-handoff.md`.
- `firmware/2025/motor_drivers.txt` captures driver-related notes; diagnostics helpers live in `firmware/2025/diagnostics/`.
- Raspberry Pi talks USB CDC to Every 1; Every 1 ↔ Every 2 uses SoftwareSerial @ 38 400 baud (`PING/ACK` protocol described in the handoff doc).

**Battery / power bring-up**
- Use `hardware/protection_board_manufacturing_rev_a/README.md` + `test_procedure_rev_a.md` for LM74700/LM5069 power-entry board tests (reverse protection, inrush, UVLO/OVLO, current limit). Rev B README lists UVLO/OVLO resistor changes for 5S.
- For the boost converter (LM5122-Q1) and motor driver buck stages, respect the decoupling/thermal guidance in their READMEs before loading the rails.

## Hardware Module Summaries (in `hardware/`)
- `protection_board_manufacturing_rev_a/` — Power-entry protection board: ideal diode (LM74700-Q1) + hot-swap/inrush/current-limit (LM5069), PGD status, TVS, parallel FETs. Includes Gerbers/BOM/CPL and step-by-step test plan.  
- `protection_board_manufacturing_rev_b/` — Same board with retuned UVLO/OVLO resistor network for 5S packs (see README for exact R3/R5/R7 values and threshold table).
- `boost_manufacturing_rev_a/` — 18–24 V → 36 V synchronous boost (LM5122-Q1), forced CCM, sized for motor bus loads; includes BOM/CPL/Gerbers and stack-up.  
- `boost_manufacturing_rev_b/` — Rev A delta notes (input cap/value corrections); regenerate outputs after applying changes.
- `buck_motor_driver_manufacturing_rev_a/` — Triple-motor H-bridge (VNH5019A-E) with integrated high-current buck stage; Arduino Nano Every control; reverse polarity FET; current sense.  
- `buck_motor_driver_manufacturing_rev_b/` — Component substitutions/cost-downs + buck feedback corrections; use Rev A README for architecture, then apply Rev B changes before fab.
- `pcb_manufacturing_rev_a/` — Rover main THT PCB for power distribution, servos (4×), LiDAR, Raspberry Pi rail; emphasizes easy hand assembly and large copper for 5 V rails.  
- `pcb_manufacturing_rev_b/` — Same board with capacitor polarity/footprint silkscreen fixes.
- `pcb_manufacturing_v1/` — Older main PCB spin kept for history; prefer Rev A/B.
- `brushlessmotor_testboard_manufacturing_rev_a/` — Brushless motor test card (see KiCad project and outputs); includes backups under `Brushless motor test board/`.

## How to Regenerate Manufacturing Files
1. Open the board’s KiCad project (`*.kicad_pro`) in its folder.  
2. Run DRC/ERC, then plot Gerbers and drills to the existing `Gerber/` folder (keep relative paths).  
3. Export `BOM.csv` and `CPL.csv` with the project scripts/settings already present.  
4. Update README and delta notes if values change; bump revision folder if needed.

## Testing & Validation References
- Power-entry board: `hardware/protection_board_manufacturing_rev_a/test_procedure_rev_a.md` (reverse polarity, PGD ramp timing, current-limit/short tests, UVLO/OVLO sweeps, hot-plug, dwell).  
- Motion stack software: validation loop in `rover-software-handoff.md` (PING/ACK link, motor spin/encoders, servo sweeps, watchdog ideas).  
- Add new test logs next to each board as `test_procedure_<rev>.md` or `validation_notes.md` for traceability.

## Naming & Organization
- Folder names use underscores (e.g., `protection_board_manufacturing_rev_a`). Keep this pattern for new hardware spins: `<function>_<stage>_rev_<letter>`.  
- Place fab outputs (`Gerber/`, `BOM.csv`, `CPL.csv`) inside each board folder; keep KiCad backups under that board’s tree.  
- Put delta-only revisions (value changes, ECOs) in a new `rev_` folder with a concise README capturing what changed and why.

## License / Contact
All rights reserved. No permission is granted to use, copy, modify, or distribute this repository or its contents without prior written consent. See `LICENSE` for exact terms. Contact: Tim Wang — timwang007@outlook.com.
