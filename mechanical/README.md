# Hardware — Mechanical

## Overview

Microver is a compact competition rover built for the [Swiss Rover Challenge](../Documentation/Swiss-Rover-Challenge-Rulebook-2026-v1.pdf). The mechanical design prioritises modularity — the wheel pod system supports both 4-wheel and 6-wheel drive configurations by sliding in and out of aluminium extrusion rails, making field reconfiguration straightforward. All structural parts are custom 3D printed, with the complete assembly designed in Autodesk Fusion 360.

---

## Folder Structure

```
hardware/
├── assemblies/                  # Full and sub-assembly STEP files
│   ├── Microver assembly.step   # Top-level full rover assembly
│   └── Wheel pod assembly.step  # Modular wheel pod sub-assembly
└── components/
    ├── Chassis/                 # Base plate and aluminium extrusions
    ├── body/                    # Hood, mechanisms, servo mounts, and body parts
    ├── drivetrain/              # Wheel pod internal components
    └── electronics/             # PCBs, mounts, and power components
```

---

## Assemblies

### Full Rover — `assemblies/Microver assembly.step`

Top-level assembly of the complete rover, combining all sub-assemblies and components.

---

### Wheel Pod Assembly — `assemblies/Wheel pod assembly.step`

A modular drivetrain unit that slides in and out of the aluminium extrusion rails, enabling 4WD or 6WD configurations without structural modification. One assembly is used per wheel.

| File | Type | Description |
|---|---|---|
| `drivetrain/hub.step` | Custom | Wheel hub |
| `drivetrain/Motor Coupler.step` | Custom | Couples DC motor shaft to wheel hub |
| `drivetrain/motor holder.step` | Custom | Holds DC motor within the pod |
| `drivetrain/wheel covers with hole in the middle.step` | Custom | Wheel cap/cover |
| `drivetrain/dc-motor-encoder.step` | Manufacturer | DC motor with integrated encoder |
| `drivetrain/Ball bearing.step` | Off-the-shelf | Standard ball bearing |
| `body/extrusion connector component.step` | Custom | Interfaces wheel pod to aluminium extrusion rail |

---

### Chassis

The structural frame of the rover. The base plate mounts onto aluminium extrusion rails via L-brackets, which also act as the sliding rails for the wheel pod assemblies.

| File | Type | Description |
|---|---|---|
| `Chassis/base plate final.step` | Custom | Main structural plate — 30×15.8 cm (overall width 34×19.5 cm) |
| `Chassis/aluminium extrusion.step` | Off-the-shelf | Aluminium extrusion rails |
| `body/L-bracket.step` | Off-the-shelf | HBLBS5 L-bracket, connects extrusions to base plate |

---

### Hook Mechanism

A large MG996R servo drives a hook arm used to grab small payloads and deliver them to a stash location.

| File | Type | Description |
|---|---|---|
| `body/hook microver.step` | Custom | Hook arm |
| `body/servo motor v4 continuation.step` | Custom | Custom MG996R servo mount/bracket |
| `body/Servo+MG996R.step` | Manufacturer | MG996R servo |

---

### Trap Box Assembly

A servo-operated mechanism that releases small pellets from beneath the rover. The pellets are dropped behind the rover to cause competing rovers to slip.

| File | Type | Description |
|---|---|---|
| `body/Trap box.step` | Custom | Pellet container housing |
| `body/MG90S_motorholder.step` | Custom | MG90S servo mount |
| `body/MG90S servo.step` | Manufacturer | MG90S servo (trap door actuation) |

---

### Flag Mechanism

A small MG90S servo raises a flag on the side of the rover.

| File | Type | Description |
|---|---|---|
| `body/Flag holder.step` | Custom | Flag arm/holder |
| `body/MG90S_motorholder.step` | Custom | MG90S servo mount |
| `body/MG90S servo.step` | Manufacturer | MG90S servo (flag actuation) |

---

### Hood Assembly

A 3-part protective cover for the rover's internal components. Also serves as the mounting platform for the camera, LIDAR, and WiFi antenna.

| File | Type | Description |
|---|---|---|
| `body/Microver hood.step` | Custom | Hood (front, main, and back sections) |
| `body/LIDAR.step` | Manufacturer | Slamtec C1M1 LIDAR — used for autonomous navigation |
| `body/RPi_Camera_V2.1.step` | Manufacturer | Raspberry Pi Camera V2.1 |

---

## Component Catalogue

### Custom Designed Parts

| Component | File | Description |
|---|---|---|
| Base plate | `Chassis/base plate final.step` | Main structural plate, 30×15.8 cm |
| Aluminium extrusion connector | `body/extrusion connector component.step` | Wheel pod–to–extrusion rail interface |
| Wheel hub | `drivetrain/hub.step` | Wheel hub |
| Motor coupler | `drivetrain/Motor Coupler.step` | Shaft-to-hub coupling |
| Motor holder | `drivetrain/motor holder.step` | DC motor mount within wheel pod |
| Wheel cover | `drivetrain/wheel covers with hole in the middle.step` | Wheel cap |
| Hood | `body/Microver hood.step` | 3-part protective body cover |
| Hook arm | `body/hook microver.step` | Payload hook arm |
| MG996R servo mount | `body/servo motor v4 continuation.step` | Large servo bracket |
| MG90S servo holder | `body/MG90S_motorholder.step` | Small servo mount (shared by trap & flag) |
| Trap box | `body/Trap box.step` | Pellet dispenser housing |
| Flag holder | `body/Flag holder.step` | Flag arm |
| Fan mount | `body/Fan microver.step` | Electronics cooling fan mount |
| Fan holder | `body/fan holder.step` | Secondary fan bracket |
| PCB mount | `electronics/PCB mount.step` | PCB mounting bracket |
| Raspberry Pi 5 holder | `electronics/Pi5_holder.step` | Raspberry Pi 5 mount |
| PCB spacer | `electronics/Spacer PCB.step` | PCB standoff spacer |
| Logo model | `body/CK Project model.step` | Project CK logo |

### Manufacturer / Off-the-Shelf Models

| Component | File | Source |
|---|---|---|
| Aluminium extrusion | `Chassis/aluminium extrusion.step` | microver.ch competition |
| L-bracket (HBLBS5) | `body/L-bracket.step` | microver.ch competition |
| MG996R servo | `body/Servo+MG996R.step` | microver.ch competition |
| MG90S servo | `body/MG90S servo.step` | microver.ch competition |
| DC motor w/ encoder | `drivetrain/dc-motor-encoder.step` | microver.ch competition |
| Ball bearing | `drivetrain/Ball bearing.step` | microver.ch competition |
| LIDAR (Slamtec C1M1) | `body/LIDAR.step` | microver.ch competition |
| Raspberry Pi Camera V2.1 | `body/RPi_Camera_V2.1.step` | microver.ch competition |
| Raspberry Pi 5 | `electronics/Raspberry Pi.step` | Electronics supplier |
| Einhell 2.5Ah battery | `electronics/Battery/einhell-2.5Ah.step` | microver.ch competition |
| Power receiver | `electronics/Battery/power-receiver-public-document.step` | microver.ch competition |
| E-stop | `electronics/e-stop.step` | microver.ch competition |
| Boost converter PCB | `electronics/Boost converter_3D.step` | Custom PCB manufacturer |
| Buck converter PCB | `electronics/Buck_3D.step` | Custom PCB manufacturer |
| High Side OR-ing PCB | `electronics/High Side OR ing_3D.step` | Custom PCB manufacturer |
| Modular board PCB | `electronics/Microver2026_Modular_Final_3D.step` | Custom PCB manufacturer |
| STM32 control PCB | `electronics/Microver2026_STM32_Control_3D.step` | Custom PCB manufacturer |

---

## Manufacturing

All custom parts were designed in Autodesk Fusion 360 and 3D printed in-house.

**Printers:** Bambu Lab H2D and X1C

**Materials:**
- **PLA Basic** — all structural parts
- **TPU** — tyres (for maximum grip and elasticity)

**Sourcing:** Off-the-shelf hardware components (brackets, extrusions, motors, sensors) were sourced from the microver.ch competition. Electronics were sourced separately.

---

## Status

All parts are finalised as of the 2026 competition season.
