# High-Current DC Motor Driver (Triple Motor, Unified Control) — Rev A

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev A  
**Date:** 2025-01-16  
**Project:** Project CK

## 1) Overview
Single high-current full H-bridge drives three DC motors in parallel (same direction and speed) with PWM speed control and bidirectional rotation from an Arduino-class MCU. Board also carries an integrated high-current buck converter stage for logic/peripheral power. Intended for robotics/rover drive subsystems, prototyping, and educational use at 24 V nominal. Key features: VNH5019A-E class monolithic H-bridge; forward/reverse/brake/coast; parallel motors as one load; logic-level control; reverse-polarity protection via external NMOS; current sense output; SMD-first design suitable for automated assembly (some hand-soldered options).

## 2) Revision / ownership
- Board revision: Rev A
- Date: 2025-01-16
- Designer / owner: Tim Wang
- Contact: timwang007@outlook.com
- Project: Project CK
- Warning: modifying the power stage, MOSFET, or copper thickness requires a new board revision.

## 3) Electrical specifications
### Power domains
- VBAT / VCC_M: main motor supply (raw battery input) routed through U3 (CSD18543Q3A) for reverse-polarity protection before the driver VCC_M pins.
- VCC: logic/internal driver supply (from Arduino Nano Every 5 V rail).
- GNDB: power ground (motor currents).
- GNDA: logic/sense ground.

### Voltage ratings
- Motor supply (VBAT): nominal 24 V DC; recommended 18–28 V; absolute max per driver datasheet (do not exceed).
- Logic supply (VCC): 5 V regulated; must be present and stable before enabling motor drive.

### Current capability
- Three DC motors in parallel; peak current sized for startup/stall. Continuous current limited by copper weight/area, thermal dissipation, and duty cycle. Motors in parallel do not share current perfectly; a stalled motor can draw disproportionate current.

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

## 5) Key components (why chosen)
- U2 VNH5019A-E: integrated high-current H-bridge with current sense and fault flags, supports motor supply up to ~24–41 V with robust protection—fits triple-motor parallel drive without separate FET gate drive design.
- U3 CSD18543Q3A: low-Rds(on) 40 V class NexFET used for reverse-polarity protection on VBAT to keep losses low.
- A1 Arduino Nano Every: ATmega4809-based MCU with native 5 V logic, plenty of PWM/GPIO to drive the H-bridge and diagnostics.
- Terminal blocks (MX126 5.00 mm): screw terminals for reliable field wiring of motors and power.
- Decoupling: 4.7 µF + 0.1 µF ceramics near the driver supply pins and logic rails to keep transients local; add local bulk at VBAT if space allows.
- Thermal/heat spreading: use pours on all layers for VBAT/VOUT/GND around U2/U3 and stitch with via arrays near pads to share heat and reduce voltage drop.
- Buck stage: uses low-Rds(on) MOSFETs/diode sized for high-current step-down; bulk electrolytic/polymer caps on VIN/VOUT and ceramics at switch/controller pins; low-DCR inductor sized for ripple/efficiency trade.

## 6) Integrated buck converter stage (on-board)
- Purpose: high-current buck converter to derive regulated logic/peripheral rail from the motor supply; suitable for MCU/sensor/aux loads.
- Input: VBAT from J4; reverse-polarity protected via U3; voltage range set by BOM/controller (document exact min/max once final).
- Output: regulated DC rail (set by feedback network); route to logic/peripheral headers; keep wiring short and sized for current.
- Connectors: shares VBAT input with the motor stage; output routed to on-board headers (document exact connector IDs once finalized).
- Decoupling/thermal: place ceramics at controller/switch pins; bulk at VIN/VOUT; pour VIN/VOUT/GND on all layers and via-stitch near FETs/diode/inductor to spread heat and lower impedance.
- Bring-up (buck section): check VIN/VOUT shorts unpowered; power with current limit low; verify VOUT rises cleanly; step load gradually while watching thermals/ripple.

## 7) Motor and connector interface
### Power/logic connectors (per schematic)
- J4 `Conn_01x02_Socket`: VBAT (in) and GND feeding U3 (reverse polarity NMOS) then VCC_M to the driver. Confirm pin order before wiring.
- J3 `Conn_01x02_Socket` labeled `VIN_A`: logic VIN/GND feed to the Arduino Nano Every (A1). Confirm whether this is 5 V regulated or upstream battery before use.
- Arduino Nano Every (A1) provides VCC (5 V) and control signals to U2.

### Motor outputs
- U2 (VNH5019A-E) OUTA / OUTB pins brought to J5 `Conn_01x02_Socket` for motor terminals. All motors connect in parallel: Motor1+, Motor2+, Motor3+ to OUTA; Motor1-, Motor2-, Motor3- to OUTB.
- All OUTA pins on the IC are internally common; all OUTB pins are internally common.

### Control interface (Microcontroller)
| Signal | Direction | Description |
| --- | --- | --- |
| PWM | MCU -> Board | Speed control (duty cycle) |
| INA | MCU -> Board | Direction control A |
| INB | MCU -> Board | Direction control B |
| ENA / DIAGA | MCU <-> Board | Enable + fault reporting |
| ENB / DIAGB | MCU <-> Board | Enable + fault reporting |
| CS | Board -> MCU | Analog current sense output |
| GND | — | Common ground with MCU (must tie MCU ground to board ground) |

## 6) Logic truth table (simplified)
| INA | INB | PWM | Motor state |
| --- | --- | --- | --- |
| 0 | 0 | X | Coast |
| 1 | 0 | PWM | Forward (speed via PWM) |
| 0 | 1 | PWM | Reverse (speed via PWM) |
| 1 | 1 | PWM | Brake (use cautiously) |
Recommendations: set PWM = 0 before changing direction; avoid instantaneous forward/reverse switching at high duty.

## 8) Files included
- Gerbers + NC drill (in `Gerber/` and `Gerber.zip`)
- `BOM.csv`
- `Buck-top-pos.csv` (pick-and-place)

## 9) Assembly notes
- Verify IC and MOSFET orientation; check for bridges on OUTA/OUTB pins.
- Reverse-protection NMOS (U3) sits in the VBAT path — confirm thermal/footprint fit.
- Tie MCU ground to board ground to ensure valid DIAG/CS readings.
- Buck errata (Q2): The buck-stage MOSFET Q2 footprint is flipped in Rev A — the source is tied to VOUT but should be the drain. Keep this in mind for rework/analysis; Rev B fixes the orientation.

## 10) Bring-Up Procedure (first power-on)
1) Visual inspection: IC orientation, MOSFET orientation, no solder bridges on OUTA/OUTB pins.  
2) Power without motors: apply VBAT (24 V) with current limit; apply 5 V VCC; verify no excessive current draw, VCC stable, DIAG pins not asserting fault.  
3) Logic test: MCU connected, PWM = 0; toggle INA/INB; ensure no motor output switching with PWM = 0.  
4) Single motor test: connect one motor; run at low PWM (10–20%); verify forward and reverse.  
5) Full load: connect all three motors; gradually increase PWM; monitor board temperature, supply current, and CS output. Stop and debug if anything overheats or faults.

## 11) Known assumptions / limitations
- Motors assumed identical/similar; no per-motor current balancing.
- Not safety-rated or for human-critical systems.

## 12) Notes for future revisions
- For independent motor control, a new architecture is required.
- If higher continuous current is needed, revisit copper thickness, MOSFET selection, and bulk capacitance.
- Consider per-motor fuses/PTCs and a hardware overcurrent latch.
