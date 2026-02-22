# High-Current Buck Converter — Rev B

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev B  
**Date:** 2026-01-29  
**Project:** Project CK  

## 1) Scope
Rev B is now a buck-only spin. The motor driver section was removed from the KiCad project; use the Rev A folder for the combined VNH5019 + buck board architecture and pinout. This README captures the buck changes and fixes.

## 2) PCB stack-up (applies to all Rev B boards)
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

## 3) Change Summary
### Motor driver stage
- Removed in this spin (buck-only). For the VNH5019 power stage and connectors, refer to `buck_motor_driver_manufacturing_rev_a/`.

### Buck stage
### Functional/value corrections (based on TI calculator vs Rev A datasheet example)
- R3: **C25803 → C23184**.  
- R4: **C2933161 → C23162**.  
- R2: **C31850 → C4216**.  
- R5: **C23018 → C23159**.  
- R8: **C22843 → C23170**.  
- C8: **C307434 (16V)→ C15849**.  
- C13: **C107097 → C53987**.  
- C14: **C1594 → C28262**.  
- C17: **C1632 → C1609**.  
- R20: removed (previous value) and **re‑added as C23260** with corrected value.  
- R19: **deleted** (no replacement).
- **Rev A feedback wiring bug fixed:** The TI feedback network is restored in Rev B — R8 (150 Ω) routes VOUT → intermediate node, C17 (820 pF) connects intermediate → FB, and R9 (23.2 kΩ) goes directly from VOUT → FB. Rev A incorrectly placed both R8 and R9 from VOUT → intermediate with only C17 to FB, leaving FB capacitor-only and causing runaway VOUT and audible whine. Rev B rewires to the TI topology so FB now sees VOUT through a DC path (R9) while keeping the compensation network on the intermediate node.
- **Q2 orientation corrected:** Rev A buck MOSFET Q2 had its source tied to VOUT (body diode forward-biased to VIN). Rev B flips the footprint so the drain connects to VOUT as intended.
- Routing fixes: corrected RT and SS_TRK nets so the RT resistor now lands on RT and the soft-start capacitor lands on SS/TRK; fixed an FB trace error so the FB pin ties to the intended feedback/comp network.

### Cost/availability optimizations (value unchanged unless noted)
- C2, C3, C4, C6, C7, C9: **C51205 → C29823**.  
- C11: **C1845716 (16V) → C1634**.  
- R9: **C23346 → C31850**.  
- R6: **C23065 → C23193**.  
- C5: **C43922 (16V) → C377773** (cost down).  
- D1: **C510301 → C2286** (cost down).  
- C15, C16, C18: **C5440143 (16V) → C96123** (cost down).  
- Output caps expanded for stability: C19, C20, C22, C23 added at VOUT.  
- Added via shielding/stitching around the inductor and high di/dt switching loops (VIN, SW, PGND); keep the area directly under the inductor clear to minimize eddy losses.

### Bench evidence of the Rev A issue (for traceability)
- The miswired Rev A feedback caused FB to be driven only through C17. Bench measurements on 2026-02-05 showed VOUT rising with VIN instead of regulating near 5.3 V:

  | VIN (V) | VOUT observed (V) |
  | --- | --- |
  | 9  | 4.8–5.8 |
  | 10 | 5.3–6.4 |
  | 11 | 5.3–6.8 |
  | 12 | 5.4–7.5 |
  | 13 | 5.3–7.7 |
  | 14 | 5.3–8.2 |
  | 15 | 5.3–8.8 |
  | 16 | 5.3–9.0 |

- Additional observations (Rev A): converter did not start below 9 V VIN; audible switching noise decreased in frequency as VIN increased; tested with R8 = 150 Ω. These symptoms align with FB being AC-coupled only. Rev B rework above addresses this.

## 4) Files
- Rev B BOM/CPL/Gerbers not yet generated. Apply the above substitutions/additions/removals in KiCad, then regenerate outputs.
