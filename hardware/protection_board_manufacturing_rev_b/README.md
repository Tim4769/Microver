# Power Protection Board — Rev B

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev B  
**Date:** 2026-01-26  

## Overview
Power-entry protection board for a 5S battery (≈18.5 V nominal) with ideal-diode reverse protection, inrush/hot-swap control, UVLO/OVLO, current limit, and PGD output.

## PCB stack-up (applies to all Rev B boards)
- Layer stack:
  - F.Silkscreen (top silk screen), color/material not specified
  - F.Paste (top solder paste)
  - F.Mask (top solder mask), thickness 0.01 mm, color not specified, material not specified, Er 3.3, LossTg 0
  - F.Cu 0.035 mm
  - Dielectric 1 (prepreg) 0.10 mm FR4, Er 4.5, LossTg 0.02
  - In1.Cu 0.017 mm
  - Dielectric 2 (core) 1.25 mm FR4, Er 4.5, LossTg 0.02
  - In2.Cu 0.017 mm
  - Dielectric 3 (prepreg) 0.10 mm FR4, Er 4.5, LossTg 0.02
  - B.Cu 0.035 mm
  - B.Mask (bottom solder mask) 0.035 mm, color not specified, material not specified, Er 3.3, LossTg 0
  - B.Paste (bottom solder paste)
  - B.Silkscreen (bottom silk screen), color/material not specified
  - Finish: HAL lead-free

## Change summary vs Rev A
- R3 changed from 180 Ω (C22828) to **2 kΩ (C22975)**.
- R5 changed from 47 kΩ (C25819) to **24 kΩ (C23352)**.
- R7 changed from 4.3 kΩ (C23159) to **3 kΩ (C4211)**.
- Input electrolytic bulk at VIN is **removed / DNP**. Reverse hookups were blowing this cap; rely on downstream bulk after the ideal-diode/hot-swap path instead.

## Rationale
- The new values adjust the LM5069 resistor network to set UVLO/OVLO thresholds for the actual 5S battery deployment as follows (V):
  - Upper UVLO: 15.30 (min) / 16.03 (typ) / 16.76 (max)
  - Lower UVLO: 14.73 / 15.03 / 15.33
  - Upper OVLO: 22.54 / 23.00 / 23.46
  - Lower OVLO: 21.80 / 22.48 / 23.16
  These align the protection window with the desired battery range while avoiding nuisance trips on startup.
- Removing the VIN electrolytic prevents reverse-polarity events from stressing the aluminum can. Bulk capacitance now lives downstream of the ideal diode/hot-swap FETs or externally at the load.

## Files in this folder
- `BOM.csv` — updated resistor values and MPNs for Rev B.
- (Gerbers, CPL, drawings) — not regenerated yet for Rev B; reuse Rev A outputs only after validating against these value changes.

## Action items before release
- Regenerate schematic/layout PDFs and Gerbers once the new values are reflected in the KiCad project.
- Update pick-and-place and assembly drawings to ensure R3/R5/R7 designators match the new values/MPNs.
