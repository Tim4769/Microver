# Firmware Folder Layout

This folder is organized by year, then by function (controllers, diagnostics, docs, references).

## Current structure
- `2025/controllers/` - Main Arduino Nano Every sketches used for integrated bring-up.
- `2025/diagnostics/` - Isolated bench tests grouped by subsystem:
  - `drivetrain/`
  - `link/`
  - `servos/`
- `2025/docs/` - Firmware-facing notes.
- `2025/references/` - Datasheets and component notes used by firmware bring-up.
- `2026/docs/` - System handoff documentation.

## Duplicate check
- A SHA-256 content check was run across all files under `firmware/`.
- No duplicate file contents were found inside this folder.

## Path migration map
- `2025/arduino_every1_test.ino` -> `2025/controllers/arduino_every1_test.ino`
- `2025/arduino_every2_test.ino` -> `2025/controllers/arduino_every2_test.ino`
- `2025/motor_drivers.txt` -> `2025/docs/motor_drivers.txt`
- `2025/diagnostics/left_side_test.ino` -> `2025/diagnostics/drivetrain/left_side_test.ino`
- `2025/diagnostics/right_side_test.ino` -> `2025/diagnostics/drivetrain/right_side_test.ino`
- `2025/diagnostics/link_test_every1.ino` -> `2025/diagnostics/link/link_test_every1.ino`
- `2025/diagnostics/link_test_every2.ino` -> `2025/diagnostics/link/link_test_every2.ino`
- `2025/diagnostics/servo1_test.ino` -> `2025/diagnostics/servos/servo1_test.ino`
- `2025/diagnostics/servo2_test.ino` -> `2025/diagnostics/servos/servo2_test.ino`
- `2025/diagnostics/servo3_test.ino` -> `2025/diagnostics/servos/servo3_test.ino`
- `2025/diagnostics/servo4_test.ino` -> `2025/diagnostics/servos/servo4_test.ino`
- `2025/knowledge base/PCB (arduino) documentation v1.pdf` -> `2025/references/pcb_arduino_documentation_v1.pdf`
- `2025/knowledge base/SLAMTEC_rplidar_datasheet_C1_v1.0_en (1).pdf` -> `2025/references/slamtec_rplidar_datasheet_c1_v1.0_en.pdf`
- `2025/knowledge base/adafruit-drv8871-brushed-dc-motor-driver-breakout.pdf` -> `2025/references/adafruit_drv8871_brushed_dc_motor_driver_breakout.pdf`
- `2025/knowledge base/drv8871_notes.txt` -> `2025/references/drv8871_notes.txt`
- `2025/knowledge base/pcb_arduino_notes.txt` -> `2025/references/pcb_arduino_notes.txt`
- `2025/knowledge base/rplidar_c1_notes.txt` -> `2025/references/rplidar_c1_notes.txt`
- `2026/rover-software-handoff.md` -> `2026/docs/rover-software-handoff.md`
