# Final Control Board — Rev A

**Owner / Contact:** Tim Wang — timwang007@outlook.com  
**Revision:** Rev A  
**Date:** 2026-04-12  
**Project:** Project CK

## 1) Overview
Rev A is the modular control and distribution board for the Microver 2026 final hardware stack. It mates to the `Left` / `Right` 2x10 headers used by the final compute boards, carries two integrated motor-driver channels, provides local 3.3 V regulation and rail indicators, and breaks out the rover harnesses for six drive connectors, four servos, LiDAR, Raspberry Pi UART/power, and board-level power-control signals. The board also includes mounting holes for attaching the buck, boost, OR-ing, and protection boards, plus board-to-board power pads / wire points so those auxiliary PCBs can connect back into the main control board.

## 2) Major interfaces
- Compute-board interconnect:
  - `J14` — `Left`
  - `J15` — `Right`
  - These headers match the naming used in `final_compute_STM32_rev_a/` and `final_compute_arduinos_rev_a/`.
- Drive harnesses:
  - `J10` to `J13`, `J16`, `J17` — `Drive_1` to `Drive_6`
  - JST-PH 6-pin vertical connectors for the six rover drive harnesses.
- Sensor / host / expansion:
  - `J18` — `Lidar pins`
  - `J20` — `Spare pins`
  - `J29` — `Pi 5 TX and RX UART0 (PL011)`
  - `J30` — `Pi power pins`
- Actuator / control breakouts:
  - `J24` to `J27` — `Servo 1` to `Servo 4`
  - `J21` — `on/off_Boost`
  - `J22` — `PGD_Prot`
  - `J23` — `fan_control`
- Power entry / distribution:
  - `J19` — `VIN_5V`
  - `J31` — `VIN_Pre`
  - `J32` — `VOUT_Pre`
  - `J28` — `VOUT_Higher`
  - These pads / wire-connection points are intended for board-to-board links from the auxiliary power PCBs back to the main control board.

## 3) Mechanical integration
- The board includes multiple M3 mounting holes for mechanical attachment and stacking.
- BOM callouts `H2` and `H3` indicate dedicated mounting locations associated with the auxiliary power-board side of the assembly (`Boost/Prot` and `Prot`).
- Additional mounting holes (`H4`, `H5`, `H6`, `H8`, `H9`, `H10`, `H11`, `H12`, `H13`, `H14`) provide attachment points for the overall board stack and attached buck, boost, OR-ing, and protection boards.

## 4) Major populated devices
- `U1`, `U2` — **VNH5019A-E** integrated H-bridge motor drivers.
- `U3`, `U4` — **CSD18543Q3A** power MOSFETs in the board power / drive path.
- `U5` — **MIC5365-3.3YD5** local 3.3 V regulator.
- `F1` — input fuse.
- `D1`, `D2`, `D3` — rail indicator LEDs for **3.3 V**, **5 V**, and **18 V**.
- `TP1`, `TP2`, `TP3`, `TP4` — bring-up test access for **+5 V**, **+3.3 V**, and **Compute/ENCO_PWR**.
- `TH1` is marked as an excluded NTC thermistor footprint in the BOM.

## 5) PCB stack-up
- Use the standard Microver 2026 final-board 4-layer stack for regenerated manufacturing outputs:
  - F.Silkscreen (top silk screen)
  - F.Paste (top solder paste)
  - F.Mask (top solder mask), thickness 0.01 mm
  - F.Cu 0.035 mm
  - Dielectric 1 (prepreg) 0.10 mm FR4
  - In1.Cu 0.017 mm
  - Dielectric 2 (core) 1.25 mm FR4
  - In2.Cu 0.017 mm
  - Dielectric 3 (prepreg) 0.10 mm FR4
  - B.Cu 0.035 mm
  - B.Mask (bottom solder mask) 0.035 mm
  - B.Paste (bottom solder paste)
  - B.Silkscreen (bottom silk screen)
  - Finish: HAL lead-free

## 6) Assembly and bring-up notes
- Verify `J14` / `J15` orientation against the specific compute board before mating the stack.
- Confirm the exact pin order of each `Drive_*` harness before plugging motors or encoders; the checked-in files here identify connector names and placement, not the full netlist.
- Bring the board up on a current-limited bench supply first.
- Check `TP1` (+5 V) and `TP2` (+3.3 V) before connecting the compute board, Raspberry Pi, LiDAR, or servos.
- Verify board-to-board wiring at `VIN_5V`, `VIN_Pre`, `VOUT_Pre`, and `VOUT_Higher` before attaching the buck, boost, OR-ing, or protection boards.
- Verify `on/off_Boost`, `PGD_Prot`, and `fan_control` behavior at their headers before enabling downstream loads.
- Monitor thermals on `U1` to `U4` under motor load.

## 7) Files in this folder
- `BOM.csv` — Rev A bill of materials.
- `CPL.csv` — Rev A centroid / pick-and-place file.
- Gerbers and KiCad source are not currently checked into this folder. Add or regenerate them before fabrication.
