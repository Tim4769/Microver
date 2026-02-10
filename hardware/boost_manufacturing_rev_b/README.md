# Boost Converter (LM5122-Q1) — Rev B

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev B  
**Date:** 2026-02-08  

## 1) Scope
Delta notes from Rev A → Rev B for the LM5122-Q1 boost converter. Updated 2026-02-08 to capture additional value corrections and cost-down BOM changes. Use together with Rev A documentation for architecture and bring-up.

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

## 3) Change Summary (component-level)
### Functional / value corrections
- C1 input ceramic is **retained and upspecced**: C1618 → **C1594** (supersedes prior "remove" note).  
- C2 — **C1623 (25 V) → C13967 (50 V)** for voltage margin.  
- C3 — **C21117 → C21120**.  
- C6 — **added** (C1630) for extra decoupling.  
- C7 — **C5378 → C1622** (higher-voltage ceramic).  
- R2 — **C22980 → C23186**.  
- R3 — **deleted**.  
- R6 — **deleted**.  
- R7 — **C23172 → C23206**.  
- R8 — **C23150 → C22813**.  
- R9 — **deleted**.  
- R11 — **C23018 → C22790**.  
- R12 — **C23234 → C23206**.  
- R15 — **C23153 → C22965**.  
- Input bulk: keep C12 (470 µF) and C14 (47 µF); C13 is now DNP unless extra input ripple suppression is needed.

### Cost / availability optimizations
- C11, C14 — **C7213084 → C440198** (cost-down MLCC, same value).  
- C15, C16, C17, C18, C19, C20 (and any retained C13/C9) — **standardize to C440198** to consolidate pricing.  
- C13 and C9 — **delete (DNP)** for cost reduction; if kept, also migrate to C440198.  
- L1 — **C17398237 → C3037600** (lower-cost inductor).  

### Layout / EMI
- Added via shielding/stitching around the inductor and high di/dt switching loops (VIN, SW, PGND) to cut radiated EMI; keep the copper directly under the inductor free of vias to avoid eddy losses.

## 4) Files
- Rev B BOM/CPL/Gerbers not yet generated. Apply the above changes to the Rev A KiCad project, then regenerate outputs before fabrication.

## 5) Action Items
1) Update KiCad schematic/BOM with new/removed capacitors and MPNs.  
2) Regenerate BOM, CPL, Gerbers after updating footprints/value labels.  
3) Re-run DRC/PCBA checks for clearance with larger input caps (C12/C13).  
4) Re-validate input surge/UVLO with added bulk.
