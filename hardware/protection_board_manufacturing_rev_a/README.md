# Power Protection Board — Rev A

> DEPRECATED REVISION: For new work, start at `../current/protection_board/README.md`.

**Project:** Power Protection Board  
**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev A  
**Date:** 2026-01-23

## 1) Overview
Primary power-entry protection board for a battery system. Originally documented for 24 V (6S), but the deployed use is a 5S pack (≈18.5 V nominal). Functions: reverse polarity protection (ideal diode), hot-plug/inrush control, adjustable current limit and circuit breaker, UVLO/OVLO, Power-Good (PGD) status, and surge/transient suppression. Targeted at robotics/rover/battery systems with high inrush loads.

## 2) Key ICs and architecture
- Power path: LM74700-Q1 (ideal diode/reverse battery) → LM5069 (hot-swap controller with dv/dt ramp, current limit, fault timer) → external pass MOSFETs in parallel.
- Protection elements: TVS on VIN; sense resistor for current limiting; dv/dt startup network; bulk + ceramic caps on VIN and VOUT.

## 3) Electrical specifications
- Input voltage: 6S battery (~18–25.2 V nominal); max transient clamped by TVS.
- Current limit: ~20 A (configurable via RSNS).
- Fault timer: ~320 ms.
- Startup: controlled dv/dt.
- MOSFETs: 2–3 devices in parallel.
- Operating temp: automotive-grade components.

## 4) PCB stackup (all boards)
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

## 5) Interfaces and signals
- J1 — VIN (input): Battery + / GND; protected by TVS + LM74700-Q1.
- J2 — VOUT (output): Protected, current-limited output to system.
- PGD (Power-Good): open-drain; pulled up to logic rail (3.3 V / 5 V). LOW = fault/startup; HIGH = power stable. Recommended for MCU enable gating, PG LED, system fault monitoring.

## 6) Key components (design intent)
- LM74700-Q1: ideal diode controller for reverse polarity, minimizes forward drop and turn-on stress.
- LM5069-2: hot-swap / inrush controller with adjustable dv/dt, current limit, and fault timer; suited for 10–80 V systems.
- Pass FETs: CSD19536KTT 100 V NexFET devices in parallel; low Rds(on) for reduced dissipation at ~20 A limits.
- TVS: SMBJ33A class (VIN → GND) for surge/transient clamping.
- Sense resistor: 5 mΩ (2512) network for setting ~20 A current limit.
- VCAP (LM74700): 1 µF X7R (mandatory).
- dv/dt cap: ~147–150 nF ceramic.
- Bulk caps: VIN electrolytic + ceramic; VOUT electrolytic bulk + ceramic bypass.
- Gate resistors: per MOSFET (~10 Ω).
- Decoupling/thermal: place ceramics tight to device pins; pour VIN/VOUT/GND on all layers and via-stitch near FETs/sense resistor/TVS to spread heat and lower impedance.

## 7) Files included
- `Gerber/` + `Gerber.zip`
- `BOM.csv`
- `CPL.csv`
- TODO: fabrication drawing/stackup, assembly drawings (top/bottom with polarity), units/origin note for PnP, DNP/variants list, schematic/layout PDF.

## 8) Build notes (important)
- Place TVS and VIN bulk caps close to the input connector.
- Keep sense resistor Kelvin connections clean.
- Match copper/thermal layout for parallel MOSFETs.
- Keep dv/dt network close to LM5069.
- Verify pin-1 orientation for all SOT-23 devices.

## 9) Bring-up / test procedure
1) Power with a current-limited bench supply.  
2) Verify no reverse-polarity conduction.  
3) Observe controlled VOUT ramp; PGD transitions LOW → HIGH when stable.  
4) Briefly short VOUT: confirm current limit and fault timeout/latch/retry behavior.  
5) Connect real load only after PGD is stable.  

## 10) Constraints / notes
- PGD requires a logic rail (3.3 V or 5 V pull-up).
- MOSFET SOA depends on ILIM, fault time, and number of parallel devices.
- Long battery leads may require higher-power TVS.
