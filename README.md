# Microver

![Microver rover](photos/2025-2026/IMG_1173.JPG)

Microver is a small rover project organized around three equally important parts: electronics, mechanical design, and software. The project was built for the Swiss Rover Challenge, Switzerland's high-school robotics championship where teams design, build, and operate Mars rover prototypes.

This repository keeps the project work together: final board files, mechanical handoff material, future rover software space, PCB testing firmware, documentation, and shared project assets.

## Competition Context
**Swiss Rover Challenge**
- Format: teams of 3-4 high-school students build and operate Mars rover prototypes.
- 2025 edition: Institut Le Rosey, Rolle, Switzerland, Saturday, May 31, 2025.
- 2026 edition: College Alpin Beau Soleil, Villars-sur-Ollon, Switzerland, Sunday, May 3, 2026.

**Microver results**
- 2025 Swiss Rover Challenge: 3rd place.
- 2026 Swiss Rover Challenge: 1st place.
- These results are project context only; folder names stay organized by engineering function.

**microver.ch context**
- microver.ch is an educational robotics initiative focused on project-based learning.
- The wider project teaches students to design, produce, assemble, and program their own robots.
- The kit and learning path are built around practical robotics skills including Arduino microcontrollers, Raspberry Pi computers, and 3D printing.

## Project Parts
**Electronics**
- Purpose: power entry, conversion, motor drive, compute interconnects, and final rover control boards.
- Start here: `hardware/final/README.md`.
- Supporting material: `flow charts/README.md` for power-system diagrams.
- Completed status: active board work lives under `hardware/final/`; older spins remain under `hardware/archive/`.

**Mechanical**
- Purpose: CAD, mounting, chassis, packaging, and physical integration for the rover.
- Start here: `mechanical/README.md`.
- Supporting material: board photos and physical reference files inside the hardware folders.
- Completed status: mechanical handoff area is tracked and ready for final CAD, drawings, assembly notes, and mount details.

**Software**
- Purpose: Arduino/Raspberry Pi control firmware, diagnostics, pin maps, messaging, and handoff documentation.
- Start here: `firmware/README.md`.
- Supporting material: `pcb_testing_firmware/README.md` for electronics bring-up and PCB validation sketches.
- Current status: `firmware/` is reserved for the rover software lead to update later; existing Arduino test code lives in `pcb_testing_firmware/` and is not the competition software.

## Current Snapshot
**Electronics**
- Protection board: Rev B.
- Boost converter: Rev C.
- Buck converter: Rev C.
- High-side OR-ing board: Rev A.
- Final compute boards: STM32 Rev A and dual-Arduino Rev A.
- Final control board: Rev A.

**Mechanical**
- Mechanical folder is tracked and documented.
- `mechanical/placeholder.rtf` is present until final CAD or drawing files are added.
- Future mechanical files should keep source CAD, exported drawings, assembly notes, and mounting references together.
- Mechanical integration should stay aligned with board footprints, connector access, and software sensor/actuator assumptions.

**Software**
- `firmware/` is a placeholder for the future rover software maintained by the software lead.
- `pcb_testing_firmware/` contains PCB testing, electronics bring-up sketches, diagnostics, and references.
- `pcb_testing_firmware/archive/2024_code/` contains older experiments for historical reference.
- Existing test sketches should be treated as board validation tools, not as the final competition software stack.

## Repository Map
**Electronics**
- `hardware/` - Board projects and release organization.
- `hardware/final/` - Latest board revisions for the completed 2026 rover.
- `hardware/archive/` - Historical board revisions and rollback references.
- `flow charts/` - Exported power-system flow-chart PNGs.

**Mechanical**
- `mechanical/` - Mechanical handoff area for CAD, drawings, mounts, and assembly notes.

**Software**
- `firmware/` - Future rover software folder for the software lead.
- `pcb_testing_firmware/` - PCB testing and electronics bring-up firmware.
- `pcb_testing_firmware/2026/` - Final-stack board validation sketches and handoff notes.
- `pcb_testing_firmware/2025/` - Earlier Arduino testing sketches, diagnostics, docs, and references.
- `pcb_testing_firmware/archive/` - Legacy experiments and older code snapshots.

**Shared Assets**
- `logo/` - Current and legacy logo assets.
- `jingle/` - Microver jingle audio files.
- `photos/` - Project photos from design, build, testing, and competition seasons.
- `LICENSE` - All rights reserved terms.

## Quick Start
**Electronics**
- Start in `hardware/final/` and choose the latest revision folder for the board you are building, reviewing, or documenting.
- Use each board's local `Kicad_*` folder for schematic/layout changes.
- Use `Gerber/`, `Gerber.zip`, `BOM.csv`, and `CPL.csv` when generated manufacturing outputs are available.
- For protection-board validation, use `hardware/final/protection_board_manufacturing_rev_b/test_procedure_rev_b.md`.

**Mechanical**
- Start in `mechanical/` and replace the placeholder with source CAD, exported drawings, or assembly notes when available.
- Keep mechanical files organized by rover subsystem or assembly if the folder grows.
- Check board dimensions, mounting holes, connector access, and cable paths against the active electronics folders.
- Add assembly notes next to the related CAD/drawing files so the physical build is traceable.

**Software**
- Start in `firmware/` when adding the future rover software.
- Use `pcb_testing_firmware/2026/docs/board-validation-software-handoff.md` only for board validation pin maps and test flow.
- Use `pcb_testing_firmware/2026/docs/power-and-actuator-control-handoff.md` for power-control and actuator bring-up notes.
- Run focused test sketches from `pcb_testing_firmware/2026/controllers/` when validating PCBs or electronics.

## Detailed Navigation
**Electronics**
- `hardware/final/protection_board_manufacturing_rev_b/` - Latest protection board.
- `hardware/final/boost_manufacturing_rev_c/` - Latest boost converter.
- `hardware/final/buck_manufacturing_rev_c/` - Latest buck converter.
- `hardware/final/High_Side_OR_ing_manufacturing_rev_a/` - Latest high-side OR-ing board.
- `hardware/final/final_compute_STM32_rev_a/` - STM32 compute board.
- `hardware/final/final_compute_arduinos_rev_a/` - Dual-Arduino compute board.
- `hardware/final/final_control_board_rev_a/` - Main control and distribution board.

**Mechanical**
- `mechanical/README.md` - Mechanical folder guide.
- `mechanical/placeholder.rtf` - Temporary tracked placeholder.
- Board photos in `hardware/final/*/Photo.JPG` are useful physical references for mechanical integration.

**Software**
- `firmware/README.md` - Future rover software folder guide.
- `pcb_testing_firmware/2026/controllers/` - Final-stack PCB testing sketches.
- `pcb_testing_firmware/2026/docs/board-validation-software-handoff.md` - Board validation pin maps, serial commands, and test flow.
- `pcb_testing_firmware/2026/docs/power-and-actuator-control-handoff.md` - Power and actuator bring-up notes.
- `pcb_testing_firmware/2025/diagnostics/` - Earlier focused subsystem checks.

## Maintenance Notes
**Electronics**
- After KiCad edits, regenerate Gerbers, drill files, BOM, CPL, and assembly drawings as needed.
- Keep generated outputs inside the relevant board folder.
- Add test logs as `test_procedure_<rev>.md` or `validation_notes.md`.

**Mechanical**
- Keep editable source files and exported review files together.
- Record fit, clearance, mounting, and assembly changes in README or notes files near the CAD.
- When electronics move or connector orientation changes, update mechanical references at the same time.

**Software**
- Keep future rover software under `firmware/`.
- Keep PCB validation sketches under `pcb_testing_firmware/`.
- Keep pin-map changes synchronized with the hardware and mechanical layout.
- Document PCB test protocol, baud-rate, actuator, and watchdog changes in `pcb_testing_firmware/2026/docs/`.

## License / Contact
All rights reserved. No permission is granted to use, copy, modify, or distribute this repository or its contents without prior written consent. See `LICENSE` for exact terms. Contact: Tim Wang - timwang007@outlook.com.
