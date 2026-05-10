# Final Control Board - Rev B (Not Produced)

**Revision:** Rev B  
**Production status:** Not produced / not fabricated  
**Project:** Project CK

## 1) Overview
This folder contains the KiCad source for an unproduced Rev B update of the Microver 2026 final control board.

The main correction in this KiCad project is that the second motor-driver output net issue from Rev A has been resolved: the connection intended for `OUTA` is no longer tied to the `OUTB` net.

## 2) Important compatibility note
Rev B keeps the same motor-driver stage as Rev A. Because of that, this design is still not compatible with connecting the motor-driver supply directly to the 36 V output from the boost converter.

Do not fabricate or use this design as-is for a 36 V boosted motor rail. If this design is used as the starting point for a future control board, the motor-driver stage should be redesigned with a driver/controller that is suitable for the intended boosted motor voltage. Possible examples include:

- `MP6613`
- `DRV8840`

The final driver selection should be checked against the required motor voltage, current, thermal limits, package, PCB layout constraints, and control-interface requirements before production.

## 3) Files in this folder
- `Kicad_Microver2026_Modular_Final/` - KiCad source project for the unproduced Rev B control board.

Regenerate and review all manufacturing outputs, BOM, CPL, and design-rule checks before considering any future fabrication.
