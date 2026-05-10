# Arduino Rover Main PCB — Rev A

> DEPRECATED REVISION: For new work, start at `../../current/pcb_manufacturing_rev_c/README.md`.

**Scope:** Rationale, constraints, and implementation notes for the Arduino-based rover PCB that distributes power/signals to motors, servos, LiDAR, sensors, and a Raspberry Pi rail.

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev A  
**Date:** 2025-12-14

## 1) Overview
Through-hole, module-friendly PCB that routes power (including high-current 5 V rails), breaks out signals via headers, and supports multiple actuators/sensors. Built around off-the-shelf parts to keep first-time assembly reliable and repairable without a reflow oven.

## 2) Design goals and constraints
- Easy assembly with basic soldering (THT-only).
- Robust 5 V power delivery for multiple servos and a Raspberry Pi rail.
- Low-noise returns via continuous ground planes.
- Modular pin headers for expansion and quick swaps.
- Tradeoff: larger board area because of THT and modules; SMD could shrink size but increases assembly complexity.

## 3) System architecture
- 2x Arduino boards (servo pin count is high; first Arduino already heavily used).
- 4x servo motors: two for broom, one for flag, one for optional mechanism.
- LiDAR and other sensors (logic-level domain).
- Raspberry Pi 5 V rail (high-current domain).

## 4) Component choices
- THT everywhere for hand assembly/rework.
- Servo motor: MG996R (stall torque ~9.4 kg·cm @ 4.8 V).
- Three 5 A buck converters:
  - Servo rail
  - LiDAR + second Arduino rail
  - Raspberry Pi rail  
  Note: “5 A” is regulator rating; usable current depends on VIN, thermals, airflow, and copper area.
- Decoupling/bulk: 0.1 µF at device pins; 220 µF + 2200 µF on rails to handle servo/Pi transients; place close to loads.
- Thermal strategy: pour rails on all layers where possible and via-stitch near connectors/bucks to spread heat and reduce drop.

## 5) Power architecture
- Bulk storage: 2200 µF near the source for low-frequency ripple/large steps.
- Per-rail decoupling: 220 µF + 0.1 µF at loads to handle transients and high-frequency noise.
- Servo spikes can brown out logic: place bulk caps close to servo rail and Pi rail; keep sensor/logic decoupling close to modules.

## 6) PCB stack-up and grounding
- Layer stack (applies to all boards):
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
- Grounding guidance: avoid splitting planes unless justified; keep high-current motor returns away from sensitive sensor returns.

## 7) Routing rules (tracks, vias, current intent)
- Track widths: signals at 1.0 mm; power at 2.0 mm.
- Vias: signals 1.2/0.6 mm; power 1.6/0.8 mm.
- Apply wider copper, shorter runs, and multiple vias in parallel on high-current rails (servo, Pi).

## 8) Decoupling, bulk capacitance, noise control
- 0.1 µF as close as possible to device power pins.
- 220/2200 µF near rail entry points and high-transient loads.
- Servo noise containment: short high-current paths, tight return loops, and avoid routing servo returns under sensitive sensor lines.
- Optional: extra bulk caps on servo rail; ferrite bead or LC filtering for sensor rail.

## 9) Protection and safety
- Fuse on main input for overcurrent protection.
- Reverse-polarity protection evaluated but not stuffed (XT30 connector reduces risk); consider an optional footprint/jumper to enable later without a respin.

## 10) Connectors, headers, expandability
- Pin headers for servos, LiDAR, sensors, and Pi power. Label with signal, voltage, ground, and pin-1 orientation where possible for assembly clarity.

## 11) Assembly and bring-up checklist
- Before soldering: run ERC/DRC with fab rules; confirm connector footprints/orientation (XT30, headers).
- Power-up sequence (recommended):
  1) Current-limited bench supply.
  2) Verify each buck rail with no load.
  3) Add loads gradually: Arduino → sensors → servos → Pi rail.
  4) Watch droop/ripple during servo movement.
- Quick checks: fuse rating vs peak currents; no unexpected heating on bucks, high-current pours, and connectors.

## 12) Known issues and documentation notes
- Schematic digital nets were mislabeled (all “DIGI”). Should be unique (DIGI1, DIGI2, ...). Correct labels in schematic/PCB before next spin.

## 14) Design rationale (summary)
THT + modules maximize assembly success and reworkability. A 4-layer stack with continuous ground planes lowers return-path impedance and noise. Routing uses 1.0 mm / 2.0 mm tracks and 1.2/0.6 mm / 1.6/0.8 mm vias, with wider copper, shorter runs, and via arrays on high-current paths. Bulk and decoupling capacitance supports transient-heavy loads; a fuse provides basic overcurrent safety. Known net-label issues are flagged for correction.

## 15) Post-manufacture testing / revisions
- Rev A: +18 V rail short caused by rotated polarized capacitors (positive pads tied to GND, negative to power). Fixes applied: rotated affected capacitors; updated footprints so pad numbering/polarity match nets; verified routing; corrected silkscreen polarity. Result: +18 V and GND are no longer shorted; polarity markings now match the schematic.
- Rev B: incorporates the capacitor polarity/footprint/silkscreen corrections from Rev A; no additional errata noted yet. Use the same bring-up sequence and monitor rails for any remaining issues.
