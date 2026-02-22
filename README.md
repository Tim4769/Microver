# Microver

Integrated hardware + firmware stack for a small rover platform: power-entry protection, high-current motor drive, boost and buck converters, main rover PCB, and Arduino/Raspberry Pi control firmware. This repo packages manufacturing outputs (Gerbers/BOM/CPL), build/test notes, and firmware handoff material in one place.

## Current Status (as of 2026-02-21)
- Power protection Rev B docs now capture both the original Rev B value changes and the latest LM74700 charge-pump wiring fix (`ANODE`/`VCAP` capacitor placement), including test checks to prevent recurrence.
- Buck + motor driver Rev A docs now call out the Q2 orientation errata (source tied to `VOUT` in Rev A); buck-only Rev B documents the orientation correction.
- Main rover PCB Rev C folder has been added as the planned next spin (not yet fabricated) and carries forward Rev B fixes.
- LM5050 redundant-supply ORing board Rev A is now included for 18 V / 36 V source switchover.
- Firmware folder has been reorganized by function under each year (`controllers`, `diagnostics`, `docs`, `references`) with an index at `firmware/README.md`.
- Hardware now uses a `current/` and `archive/` navigation split so contributors default to latest boards.

## Repository Map (top level)
- `firmware/` — Organized by year and role (controllers, diagnostics, docs, references). See `firmware/README.md`.
- `firmware/2025/` — Primary Arduino sketches and references for bench bring-up.
- `firmware/2026/` — Handoff and integration docs for the newer motion stack.
- `hardware/` — Board projects and release organization. Start with `hardware/current/README.md`; historical revisions are listed in `hardware/archive/README.md`.
- `assets/logos/` — Current logo assets; `assets/logos_legacy/` for older branding.
- `archive/2024_code/` — Legacy Arduino/Raspberry Pi experiments and reference code.
- `firmware/2026/docs/rover-software-handoff.md` — Raspberry Pi + dual Arduino Nano Every motion-stack pin maps, messaging, and validation steps.
- `LICENSE` — All rights reserved terms (permission required for any use).
- `NOTICE` — Rights/usage reminder and owner contact.

## Quick Start by Role
**Fabrication / PCB assembly**
- Start in `hardware/current/` and pick the board function first. Each current entry points to the latest revision folder.
- Use the provided `Gerber/` + `Gerber.zip`, `BOM.csv`, and `CPL.csv` inside each board folder. Stack-up details are documented in each board README (common 4-layer HAL lead-free).
- For the power protection board, start from `hardware/current/protection_board/README.md`, then run the linked Rev B test procedure.
- Regenerate outputs after any edits in KiCad (Gerbers, BOM, CPL, assembly drawings).

**Firmware / controls**
- Start with `firmware/2025/controllers/arduino_every1_test.ino` (DC drive + encoders) and `firmware/2025/controllers/arduino_every2_test.ino` (servos). Hardware pin maps are in `firmware/2026/docs/rover-software-handoff.md`.
- `firmware/2025/docs/motor_drivers.txt` captures driver-related notes; diagnostics helpers live under `firmware/2025/diagnostics/`.
- Raspberry Pi talks USB CDC to Every 1; Every 1 ↔ Every 2 uses SoftwareSerial @ 38 400 baud (`PING/ACK` protocol described in the handoff doc).

**Battery / power bring-up**
- Use `hardware/current/protection_board/README.md` for current LM74700/LM5069 power-entry validation (reverse protection, inrush, UVLO/OVLO, current limit, and LM74700 charge-pump wiring sanity checks).
- Historical baselines are indexed under `hardware/archive/protection_board/README.md`.
- For the boost converter (LM5122-Q1) and buck converter boards, respect the decoupling/thermal guidance in their READMEs before loading the rails.

## Hardware Navigation
**Current (start here)**
- `hardware/current/protection_board/` — Latest protection board (currently Rev B).
- `hardware/current/boost_converter/` — Latest boost converter (currently Rev B).
- `hardware/current/buck_converter/` — Latest buck-only board (currently Rev B).
- `hardware/current/buck_motor_driver/` — Latest combined buck + motor driver board (currently Rev A).
- `hardware/current/main_pcb/` — Latest rover main PCB (currently Rev C; planned).
- `hardware/current/brushless_testboard/` — Latest brushless test board (currently Rev A).
- `hardware/current/redundant_supply_oring/` — Latest LM5050 ORing board (currently Rev A).

**Archive (history)**
- `hardware/archive/README.md` — Archived revisions by board function (Rev A/B and legacy `v1` folders).

## How to Regenerate Manufacturing Files
1. Open the board’s KiCad project (`*.kicad_pro`) in its folder.  
2. Run DRC/ERC, then plot Gerbers and drills to the existing `Gerber/` folder (keep relative paths).  
3. Export `BOM.csv` and `CPL.csv` with the project scripts/settings already present.  
4. Update README and delta notes if values change; bump revision folder if needed.

## Testing & Validation References
- Power-entry board (current): `hardware/current/protection_board/README.md` (links to the active Rev B test procedure and docs).  
- Power-entry board (baseline history): `hardware/archive/protection_board/README.md`.  
- Motion stack software: validation loop in `firmware/2026/docs/rover-software-handoff.md` (PING/ACK link, motor spin/encoders, servo sweeps, watchdog ideas).  
- Add new test logs next to each board as `test_procedure_<rev>.md` or `validation_notes.md` for traceability.

## Naming & Organization
- Folder names use underscores (e.g., `protection_board_manufacturing_rev_a`). Keep this pattern for new hardware spins: `<function>_<stage>_rev_<letter>`.  
- Place fab outputs (`Gerber/`, `BOM.csv`, `CPL.csv`) inside each board folder; keep KiCad backups under that board’s tree.  
- Put delta-only revisions (value changes, ECOs) in a new `rev_` folder with a concise README capturing what changed and why.
- When releasing a new hardware revision, update the corresponding `hardware/current/<board>/README.md` pointer and move older revisions into the `hardware/archive` index.

## License / Contact
All rights reserved. No permission is granted to use, copy, modify, or distribute this repository or its contents without prior written consent. See `LICENSE` for exact terms. Contact: Tim Wang — timwang007@outlook.com.
