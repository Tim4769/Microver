# PCB Testing Firmware

This folder contains Arduino sketches, diagnostics, handoff notes, and references used for PCB testing and electronics bring-up. It is not the final rover software.

## Current structure
- `2026/controllers/` - Final-stack board validation sketches.
- `2026/docs/` - Board validation handoff notes for pin maps, power control, actuators, and test flow.
- `2025/controllers/` - Earlier Arduino Nano Every testing sketches.
- `2025/diagnostics/` - Isolated bench tests grouped by subsystem:
  - `drivetrain/`
  - `link/`
  - `servos/`
- `2025/docs/` - Firmware-facing notes for PCB testing.
- `2025/references/` - Datasheets and component notes used by bring-up sketches.
- `archive/2024_code/` - Legacy Arduino and Raspberry Pi experiments kept for reference.

## Notes
- Use this folder when validating boards, pin maps, drivers, servos, or power-control behavior.
- Put future rover software in `../../software/`, not here.
- A SHA-256 content check was previously run across the testing firmware files; no duplicate file contents were found at that time.

## Path migration map
- `firmware/2025/` -> `pcb_testing_firmware/2025/`
- `firmware/2026/` -> `pcb_testing_firmware/2026/`
- `firmware/archive/2024_code/` -> `pcb_testing_firmware/archive/2024_code/`
