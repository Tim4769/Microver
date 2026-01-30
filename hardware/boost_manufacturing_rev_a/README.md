# Boost Converter (LM5122-Q1) — Rev A

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev A  
**Date:** 2026-01-20

## 1) Overview
High-power synchronous boost converter based on LM5122-Q1, boosting a 24 V class supply to a regulated 36 V DC bus for motor/power electronics. Forced CCM for stable motor loads.

## 2) Electrical specifications
**Input**  
- VIN range: 18–24 V DC  
- Input connector: board edge power input  
- Input current: high (designed for tens of amps on PCB copper)

**Output**  
- VOUT: 36 V nominal  
- Load type: motor bus / dynamic loads  
- Operation mode: forced CCM (MODE = GND)

## 3) PCB stackup (all boards)
- F.Silkscreen (top)
- F.Paste
- F.Mask (top solder mask), thickness ~0.01 mm, Er ~3.3
- F.Cu 0.035 mm
- Dielectric 1 (prepreg) 0.10 mm FR4, Er ~4.5
- In1.Cu 0.017 mm
- Dielectric 2 (core) 1.19 mm FR4, Er ~4.5
- In2.Cu 0.017 mm
- Dielectric 3 (prepreg) 0.10 mm FR4, Er ~4.5
- B.Cu 0.070 mm
- B.Mask (bottom solder mask) 0.035 mm, Er ~3.3
- B.Paste
- B.Silkscreen (bottom)
- Finish: HAL lead-free

## 4) Key components (why chosen)
- Controller: LM5122-Q1 synchronous boost controller, automotive-grade, wide VIN, forced-CCM option for stable motor loads.
- Primary FETs: CSD18540Q5B 60 V NexFET, low Rds(on) (~3.3 mΩ typ) for high current and efficiency.
- Inductor: SER2918H 22 µH power inductor with low DCR, sized for the 10 A, 36 V target.
- Sense resistor: 2 mΩ (2512) to set current limit and monitor power stage stress.
- Output bulk: multiple 470 µF electrolytics plus polymer/tantalum to manage surge and ripple on the 36 V bus.
- Decoupling: ceramic caps at VIN/VCC/CS pins to keep loop impedance low; place tight to pins to control switching edges.
- Thermal/conducted heat: pour VOUT/SW/VIN on all layers and stitch with vias near FETs/diodes/inductor to spread loss; keep short, wide planes for SW to control ringing.

## 5) Interfaces and connectors
- Input power connector.
- Output power connector.
- Sense/enable/test as per schematic.

## 6) Files included
- Gerbers (RS-274X)  
- NC drill files  
- `BOM.csv` — JLCPCB-compatible  
- `CPL.csv` — pick-and-place (top side only)

## 7) Design reference (WEBENCH®, approximate simulation values)
- Tool: TI WEBENCH; device LM5122QMH/NOPB; target 18–24 V in → 36 V @ 10 A; created 2026-01-17.
- Major simulated values (approximate; some resistors may be split series/parallel; mΩ values are rough):
  - L1: 22 µH, ~2.95 mΩ
  - Cin: ~39 µF, ~30 mΩ
  - Cout: ~56 µF each, ~30 mΩ, Qty 10
  - Coutx: 47 µF, ~16.6 mΩ
  - Rsense: ~2 mΩ, 1 W
  - Rfbt/Rfbb: ~46.4 kΩ / ~1.6 kΩ
  - UVLO: Ruvt ~49.9 kΩ / Ruvb ~4.22 kΩ
  - Timing/comp: Rt ~43.2 kΩ, Rslope ~392 kΩ, Ccomp ~220 nF, Ccomp2 ~3.9 nF, Cvcc ~10 µF, Css ~27 nF, Cbst ~1 µF, Cres ~470 nF, Dbst VF@Io ~950 mV, VRRM ~150 V
  - MOSFETs: M1/M2 ~60 V, ~200 A class (Qty 2 each per simulation)
- Note: verify divider/sense and mΩ parts against actual BOM and any series/parallel splits before ordering/assembling.

## 8) Assembly notes (important)
- High-current copper pours — do not reduce copper weight.
- Through-hole polymer capacitors used for bulk output filtering.
- Ensure polarity for input/output bulk capacitors and bootstrap diode.
- Inductor is magnetically shielded; GND plane under inductor is intentional.
- Cleaning: remove flux residue, especially around FB, COMP, CSP/CSN, VIN pins; avoid conductive residue near SW node.

## 9) Bring-up procedure
1) Current-limited power-up: bench supply 0.5–1.0 A limit; VIN = 18 V; no load on VOUT.  
2) Idle check: VOUT to ~36 V; input current in tens of mA; no audible noise/heating.  
3) Increase input current limit gradually: 2 A → 5 A → 10 A; monitor VOUT stability, MOSFET/inductor temperature, ripple/oscillation.  
4) Apply load: start resistive/e-load; avoid motors first power-up; verify regulation before dynamic loads.

## 10) Expected idle measurements (no load)
- VIN current: ~20–60 mA (depends on switching frequency).
- VOUT ripple: low, stable.
- Thermals: no hotspots.

## 11) Warnings / limits
- Board can source very high current — treat as a power device.
- Do not hot-plug loads during early testing.
- Ensure adequate airflow during high-power operation.

## 12) Notes
- Layout relies on tight SW loops and proper ground referencing.
- Any change to FB divider or compensation requires re-validation.
