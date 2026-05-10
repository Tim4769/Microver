# Final Compute Board STM32 - Rev A

- **Owner / Contact:** Tim Wang - timwang007@outlook.com
- **Revision:** Rev A
- **Project:** Project CK

## 1) Overview
Rev A is the STM32 compute-board option for the Microver 2026 final hardware stack. The KiCad project is titled `Compute unit STM32G4RCT6` and uses the same `Left` / `Right` board-to-board header concept as the final control board.

## 2) Major interfaces
- `J14` - `Left` compute/control interconnect.
- `J15` - `Right` compute/control interconnect.
- Main MCU footprint/library target: STM32G4 control MCU in LQFP64 package.

Mate this board only after confirming `J14` and `J15` orientation against `../final_control_board_rev_a/`.

## 3) Files in this folder
- `BOM.csv` - Rev A bill of materials.
- `CPL.csv` - Rev A centroid / pick-and-place file.
- `Gerber/` and `Gerber.zip` - Rev A fabrication outputs.
- `Kicad_Microver2026_STM32_Control/` - KiCad source project and local libraries.
- `Photo.JPG` - Board photo/reference image.

## 4) Bring-up notes
- Bring up on a current-limited supply before connecting downstream loads.
- Verify the compute/control interconnect orientation before mating with the final control board.
- Regenerate BOM, CPL, Gerbers, and the zipped Gerber package after any KiCad edit.
