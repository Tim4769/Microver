# Boost Converter (LM5122-Q1) — Rev B

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev B  
**Date:** 2026-01-29  

## 1) Scope
Delta notes from Rev A → Rev B for the LM5122-Q1 boost converter. Use together with Rev A documentation for architecture, stackup, and bring-up.

## 2) Change Summary (component-level)
- **C1 (47 µF)** — *Removed* (was C96123, 10 V rating too low for VIN).  
- **Added input bulk caps:** C12 (470 µF), C13 (470 µF), C14 (47 µF) to improve input filtering.  
- **C2** — MPN C1623 (25 V) → **C13967 (50 V)** for adequate voltage margin.  
- **C7** — MPN C21120 (25 V) → **C5378 (50 V)** for adequate voltage margin.

## 3) Files
- Rev B BOM/CPL/Gerbers not yet generated. Apply the above changes to the Rev A KiCad project, then regenerate outputs before fabrication.

## 4) Action Items
1) Update KiCad schematic/BOM with new/removed capacitors and MPNs.  
2) Regenerate BOM, CPL, Gerbers after updating footprints/value labels.  
3) Re-run DRC/PCBA checks for clearance with larger input caps (C12/C13).  
4) Re-validate input surge/UVLO with added bulk.

