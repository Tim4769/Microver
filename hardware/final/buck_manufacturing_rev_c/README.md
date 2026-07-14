# High-Current Buck Converter — Rev C

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev C  
**Date:** 2026-04-05  
**Project:** Project CK  

## Photos
Board photo:

<img src="Photo.JPG" alt="Buck Rev C board photo" width="600">

Thermal test result photos:

| Load | 10 min | 20 min | 30 min |
| --- | --- | --- | --- |
| 5 A | <img src="Test%20results/Thermal/5A/After%2010mins.JPG" alt="Buck Rev C thermal test at 5 A after 10 minutes" width="180"> | <img src="Test%20results/Thermal/5A/After%2020mins.JPG" alt="Buck Rev C thermal test at 5 A after 20 minutes" width="180"> | <img src="Test%20results/Thermal/5A/After%2030mins.JPG" alt="Buck Rev C thermal test at 5 A after 30 minutes" width="180"> |
| 7.5 A | <img src="Test%20results/Thermal/7.5A/After%2010mins.JPG" alt="Buck Rev C thermal test at 7.5 A after 10 minutes" width="180"> | <img src="Test%20results/Thermal/7.5A/After%2020mins.JPG" alt="Buck Rev C thermal test at 7.5 A after 20 minutes" width="180"> | <img src="Test%20results/Thermal/7.5A/After%2030mins.JPG" alt="Buck Rev C thermal test at 7.5 A after 30 minutes" width="180"> |
| 10 A | <img src="Test%20results/Thermal/10A/After%2010mins.JPG" alt="Buck Rev C thermal test at 10 A after 10 minutes" width="180"> | <img src="Test%20results/Thermal/10A/After%2020mins.JPG" alt="Buck Rev C thermal test at 10 A after 20 minutes" width="180"> | <img src="Test%20results/Thermal/10A/After%2030mins.JPG" alt="Buck Rev C thermal test at 10 A after 30 minutes" width="180"> |
| 12.5 A | <img src="Test%20results/Thermal/12.5A/After%2010mins.JPG" alt="Buck Rev C thermal test at 12.5 A after 10 minutes" width="180"> | <img src="Test%20results/Thermal/12.5A/After%2020mins.JPG" alt="Buck Rev C thermal test at 12.5 A after 20 minutes" width="180"> | <img src="Test%20results/Thermal/12.5A/After%2030mins.JPG" alt="Buck Rev C thermal test at 12.5 A after 30 minutes" width="180"> |

## 1) Scope
Rev C is the next buck-only spin. It carries forward the Rev B buck architecture and prior feedback/routing fixes, then adds output-voltage trim, higher-current MOSFET staging, gate damping, RC snubbing, and updated via details. Use the Rev A folder only for the older combined VNH5019 + buck board architecture and pinout.

## 2) PCB stack-up (applies to all Rev C boards)
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
### Carryover from Rev B
- Buck-only architecture retained; the motor driver stage remains removed from this KiCad project.
- Rev B feedback-network recovery, RT/SS_TRK routing correction, Q2 orientation fix, output-cap expansion, and prior high-current layout cleanup remain in place for Rev C.

### Output set-point adjustment
- R9: **22 kOhm -> 22.6 kOhm** to trim nominal VOUT to **5.0 V**.

### Power stage updates
- Switched all buck MOSFET positions to **BSC032N04LS** for improved switching behavior.
- Added one extra MOSFET in parallel on the high-side path and one extra MOSFET in parallel on the low-side path to better share current at higher load.
- Added MOSFET gate resistors **R14** and **R15**, each **2 Ohm**, to damp gate ringing and improve switching control.

### Snubber / switching-node damping
- Added an RC snubber on the switching node using **C24 = 1 nF** with **3 Ohm** total series resistance.
- Current implementation is **R10 = 2 Ohm** and **R11 = 1 Ohm** in series with **C24 = 1 nF** to realize the 3 Ohm + 1 nF snubber network.

### Debug / bring-up access
- Added dedicated test points for **FB**, **COMP**, **PGOOD**, **SS**, and **EN_UVLO** to simplify probing during bring-up and stability checks.

### Layout / manufacturing updates
- Stitching vias are now left **untented** to improve thermal dissipation.
- Stitching via drill size reduced from **0.40 mm -> 0.30 mm** to help reduce EMI and loop inductance.

## 4) Reference Links
- RC snubber design reference video: <https://www.youtube.com/watch?v=c8UW640WRcc>
- TI LM5146 reference design: <https://www.ti.com/lit/ug/tidt126/tidt126.pdf>
- TI gate resistor application note: <https://www.ti.com/lit/ab/slla385a/slla385a.pdf>

## 5) Files
- `Buck_3D.step` — 3D STEP model of the assembled PCB.
- Rev C BOM/CPL/Gerbers have not been regenerated yet. Regenerate all manufacturing outputs from `Buck_kicad/` before fabrication.
- This folder contains the Rev C KiCad source, local symbol/footprint libraries, calculator workbook, and Rev C bench test procedure.
