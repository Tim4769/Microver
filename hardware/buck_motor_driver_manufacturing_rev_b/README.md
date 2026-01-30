# High-Current DC Motor Driver + Buck — Rev B

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev B  
**Date:** 2026-01-29  
**Project:** Project CK  

## 1) Scope
Component deltas from Rev A → Rev B for the combined buck converter + triple-motor driver board. Use Rev A README for architecture, stackup, and bring-up.

## 2) Change Summary
### Motor driver stage
- No schematic/PCB/BOM changes vs Rev A. VNH5019A-E power stage, connectors, and signals are unchanged; reuse Rev A logic truth table and bring-up steps.

### Buck stage
### Functional/value corrections (based on TI calculator vs Rev A datasheet example)
- R3: **C25803 → C23184**.  
- R4: **C2933161 → C23162**.  
- R2: **C31850 → C4216**.  
- R5: **C23018 → C23159**.  
- R8: **C22843 → C23170**.  
- C8: **C307434 → C15849**.  
- C13: **C107097 → C53987**.  
- C14: **C1594 → C28262**.  
- C17: **C1632 → C1609**.  
- R20: removed (previous value) and **re‑added as C23260** with corrected value.  
- R19: **deleted** (no replacement).

### Cost/availability optimizations (value unchanged unless noted)
- C2, C3, C4, C6, C7, C9: **C51205 → C29823**.  
- C11: **C1845716 → C1634**.  
- R9: **C23346 → C31850**.  
- R6: **C23065 → C23193**.  
- C5: **C43922 → C377773** (cost down).  
- D1: **C510301 → C2286** (cost down).  
- C15, C16, C18: **C5440143 → C96123** (cost down).  
- C19, C20: **removed** to cut cost.

## 3) Files
- Rev B BOM/CPL/Gerbers not yet generated. Apply the above substitutions/additions/removals in KiCad, then regenerate outputs.

## 4) Action Items
1) Update schematic/BOM with new MPNs, removal of R19, removal of C19/C20, and R20 re-added as C23260.  
2) Regenerate BOM, CPL, and Gerbers after value/footprint updates.  
3) Recompute buck feedback network after R2/R3/R4/R5/R20 changes; confirm target VOUT.  
4) Run DRC/ERC and spot-check placement/clearance for revised resistors and swapped capacitors/diode.
