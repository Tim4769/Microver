# Brushless Motor Test Board - Rev A

- **Revision:** Rev A
- **Status:** Archived reference board
- **Project:** Project CK

## 1) Overview
Rev A is a passive brushless motor / ESC breakout test board kept for historical reference and simple ESC bench checks. It is archived and should not be treated as the current Microver motor-drive architecture.

## 2) Files in this folder
- `Gerber/` and `Gerber.zip` - Rev A fabrication outputs.
- `Kicad_Brushless motor test board/` - KiCad source project.
- `test_procedure_rev_a.md` - Quick ESC breakout validation procedure.

## 3) Use notes
- Start with `test_procedure_rev_a.md` before powering the board.
- Test ESCs with the prop removed and with a current-limited or otherwise appropriate supply.
- For current rover drive electronics, use the final control-board and compute-board folders under `../../final/`.
