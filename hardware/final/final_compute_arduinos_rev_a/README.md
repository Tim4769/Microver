# Final Compute Board Dual Arduino - Rev A

- **Owner / Contact:** Tim Wang - timwang007@outlook.com
- **Revision:** Rev A
- **Project:** Project CK

## 1) Overview
Rev A is the dual-Arduino compute/control board for the Microver 2026 final hardware stack. It carries `Main_Arduino_Nano_Every` and `Sub_Arduino_Nano_Every` modules and mates to the final control board through the shared `Left` / `Right` interconnects.

## 2) Major interfaces
- `J14` - `Left` compute/control interconnect.
- `J15` - `Right` compute/control interconnect.
- Main controller: Arduino Nano Every.
- Sub controller: Arduino Nano Every.

Use this board with the PCB testing pin maps documented in `../../../pcb_testing_firmware/2026/docs/board-validation-software-handoff.md`.

## 3) Files in this folder
- `BOM.csv` - Rev A bill of materials.
- `CPL.csv` - Rev A centroid / pick-and-place file.
- `Gerber/` and `Gerber.zip` - Rev A fabrication outputs.
- `Kicad_Microver2026_Control_Final/` - KiCad source project and local project files.
- `Photo.JPG` - Board photo/reference image.

## 4) Bring-up notes
- Confirm `J14` and `J15` orientation against `../final_control_board_rev_a/` before mating boards.
- Start with the test sketches in `../../../pcb_testing_firmware/2026/controllers/`.
- Regenerate BOM, CPL, Gerbers, and the zipped Gerber package after any KiCad edit.
