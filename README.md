# Microver

Integrated hardware + firmware stack for a small rover platform: power-entry protection, high-current motor drive, boost and buck converters, main rover PCB, and Arduino/Raspberry Pi control firmware. This repo packages manufacturing outputs (Gerbers/BOM/CPL), build/test notes, and firmware handoff material in one place.

## Current Status (as of 2026-04-14)
- Protection board: Rev B
- Boost converter: Rev C
- Buck converter (standalone): Rev C
- High-side OR-ing board: Rev A
- Final compute board (STM32): Rev A
- Final compute board (dual Arduino): Rev A
- Final control board: Rev A
- Archived reference boards: buck + motor driver Rev A, rover main PCB Rev C, brushless test board Rev A
- Firmware handoff docs: 2026 (`firmware/2026/docs/`)

## Repository Map (top level)
- `firmware/` — Organized by year and role (controllers, diagnostics, docs, references). See `firmware/README.md`.
- `firmware/2025/` — Primary Arduino sketches and references for bench bring-up.
- `firmware/2026/` — Handoff and integration docs for the newer motion stack.
- `hardware/` — Board projects and release organization. Start with `hardware/current/README.md`; historical revisions live under `hardware/archive/`.
- `assets/logos/` — Current logo assets; `assets/logos_legacy/` for older branding.
- `firmware/archive/2024_code/` — Legacy Arduino/Raspberry Pi experiments and reference code.
- `firmware/2026/docs/rover-software-handoff.md` — Raspberry Pi + dual Arduino Nano Every motion-stack pin maps, messaging, and validation steps.
- `LICENSE` — All rights reserved terms (permission required for any use).

## Quick Start by Role
**Fabrication / PCB assembly**
- Start in `hardware/current/` and use the latest revision folder for each board type.
- Each active board folder keeps its KiCad project in a local `Kicad_*` subdirectory; use that source tree for edits and regenerate manufacturing files in the same board folder.
- Use the provided `Gerber/` + `Gerber.zip`, `BOM.csv`, and `CPL.csv` inside each board folder when those outputs have been generated. Stack-up details are documented in each board README (common 4-layer HAL lead-free).
- For the power protection board, use `hardware/current/protection_board_manufacturing_rev_b/README.md`, then run `hardware/current/protection_board_manufacturing_rev_b/test_procedure_rev_b.md`.
- Regenerate outputs after any edits in KiCad (Gerbers, BOM, CPL, assembly drawings).

**Firmware / controls**
- Start with `firmware/2025/controllers/arduino_every1_test.ino` (DC drive + encoders) and `firmware/2025/controllers/arduino_every2_test.ino` (servos). Hardware pin maps are in `firmware/2026/docs/rover-software-handoff.md`.
- `firmware/2025/docs/motor_drivers.txt` captures driver-related notes; diagnostics helpers live under `firmware/2025/diagnostics/`.
- Raspberry Pi talks USB CDC to Every 1; Every 1 ↔ Every 2 uses SoftwareSerial @ 38 400 baud (`PING/ACK` protocol described in the handoff doc).

**Battery / power bring-up**
- Use `hardware/current/protection_board_manufacturing_rev_b/README.md` for current LM74700/LM5069 power-entry validation (reverse protection, inrush, UVLO/OVLO, current limit, and LM74700 charge-pump wiring sanity checks).
- Historical baselines are under `hardware/archive/protection_board_manufacturing_rev_a/`.
- For the boost converter (LM5122-Q1) and buck converter boards, respect the decoupling/thermal guidance in their READMEs before loading the rails.

## Hardware Navigation
**Current (start here)**
- `hardware/current/protection_board_manufacturing_rev_b/` — Latest protection board.
- `hardware/current/boost_manufacturing_rev_c/` — Latest boost converter.
- `hardware/current/buck_manufacturing_rev_c/` — Latest buck-only board.
- `hardware/current/High_Side_OR_ing_manufacturing_rev_a/` — Latest LM5050 redundant-supply OR-ing board.
- `hardware/current/final_compute_STM32_rev_a/` — STM32 compute board.
- `hardware/current/final_compute_arduinos_rev_a/` — Dual-Arduino compute/control board.
- `hardware/current/final_control_board_rev_a/` — Main control and distribution board.

**Archive (history)**
- `hardware/archive/README.md` — Archived revisions and legacy boards.
- `hardware/archive/boost_manufacturing_rev_b/` — Archived boost converter Rev B.
- `hardware/archive/buck_manufacturing_rev_b/` — Archived previous buck-only board.
- `hardware/archive/buck_motor_driver_manufacturing_rev_a/` — Archived combined buck + motor driver board.
- `hardware/archive/pcb_manufacturing_rev_c/` — Archived rover main PCB.
- `hardware/archive/brushlessmotor_testboard_manufacturing_rev_a/` — Archived brushless test board.

## How to Regenerate Manufacturing Files
1. Open the board’s KiCad project (`*.kicad_pro`) in its folder.  
2. Run DRC/ERC, then plot Gerbers and drills to the existing `Gerber/` folder (keep relative paths).  
3. Export `BOM.csv` and `CPL.csv` with the project scripts/settings already present.  
4. Update README and delta notes if values change; bump revision folder if needed.

## Testing & Validation References
- Power-entry board (current): `hardware/current/protection_board_manufacturing_rev_b/test_procedure_rev_b.md`.  
- Power-entry board (baseline history): `hardware/archive/protection_board_manufacturing_rev_a/test_procedure_rev_a.md`.  
- Motion stack software: validation loop in `firmware/2026/docs/rover-software-handoff.md` (PING/ACK link, motor spin/encoders, servo sweeps, watchdog ideas).  
- Add new test logs next to each board as `test_procedure_<rev>.md` or `validation_notes.md` for traceability.

## Naming & Organization
- Folder names use underscores (e.g., `protection_board_manufacturing_rev_a`). Keep this pattern for new hardware spins: `<function>_<stage>_rev_<letter>`.  
- Place fab outputs (`Gerber/`, `BOM.csv`, `CPL.csv`) inside each board folder; keep KiCad backups under that board’s tree.  
- Put delta-only revisions (value changes, ECOs) in a new `rev_` folder with a concise README capturing what changed and why.
- After moving a board folder, open each KiCad project and update plot/BOM/CPL output paths to match the new location under `hardware/current/` or `hardware/archive/`.

## License / Contact
All rights reserved. No permission is granted to use, copy, modify, or distribute this repository or its contents without prior written consent. See `LICENSE` for exact terms. Contact: Tim Wang — timwang007@outlook.com.
