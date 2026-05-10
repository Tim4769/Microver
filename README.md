# Microver

![Microver rover](photos/2025-2026/IMG_1173.JPG)

Microver is a compact rover built for the Swiss Rover Challenge. This repository collects the project's electronics, mechanical CAD, software scaffold, PCB test firmware, photos, and shared assets in one place.

## Project

- **Competition:** Swiss Rover Challenge, Switzerland's rover competition for teams of 5 high school students.
- **2025 result:** 3rd place.
- **2026 result:** 1st place.
- **Main disciplines:** electronics, mechanical design, and software.

## Start Here

| Area | Path | Contents |
|---|---|---|
| Electronics | `hardware/final/README.md` | Active PCB revisions, KiCad projects, manufacturing outputs, and validation notes. |
| Mechanical | `mechanical/README.md` | Rover assemblies, wheel pods, chassis parts, mechanisms, mounts, and STEP exports. |
| Software | `software/` | Python rover-control scaffold with camera and control services. |
| PCB test firmware | `hardware/pcb_testing_firmware/README.md` | Arduino sketches and docs for board bring-up and electronics validation. |
| Power diagrams | `hardware/flow_charts/README.md` | Power-system flow charts and supporting diagrams. |

## Current Snapshot

**Electronics**
- Manufacturing-ready PCB work is under `hardware/final/`; archived board spins live under `hardware/archive/`.
- The active stack covers protection Rev B, boost Rev C, buck Rev C, high-side OR-ing Rev A, compute Rev A, and final control Rev A.

**Mechanical**
- Modular CAD lives in `mechanical/assemblies/` and `mechanical/components/`.
- The rover uses field-serviceable wheel pods, aluminium extrusion rails, custom 3D-printed parts, and integrated mounts for electronics, sensors, and mechanisms.

**Software**
- `software/` is the autonomy-ready rover software workspace for control, camera, perception, navigation, and system integration.
- `hardware/pcb_testing_firmware/` contains electronics bring-up and validation sketches only; it is separate from the final software stack.

## Repository Map

- `hardware/` - PCB designs, manufacturing files, archived board revisions, power diagrams, and PCB validation firmware.
- `mechanical/` - CAD assemblies, exported STEP components, manufacturing notes, and mechanical integration references.
- `software/` - Raspberry Pi control software scaffold and future rover software workspace.
- `photos/` - Build, test, and competition photos.
- `logo/` - Current and legacy logo assets.
- `jingle/` - Project audio assets.
- `Microver_presentation_final.pdf` - Final presentation and system overview.

## Maintenance Notes

- Keep generated PCB outputs inside the relevant board revision folder.
- Update CAD references when board dimensions, connector orientation, sensor placement, or mounting details change.
- Keep editable CAD, exported review files, and assembly notes together.
- Keep PCB validation sketches separate from final rover software.
- Update this README when top-level folders move or new subsystem entry points are added.

## License / Contact

All rights reserved. No permission is granted to use, copy, modify, or distribute this repository or its contents without prior written consent. See `LICENSE` for exact terms.

Contact: Tim Wang - timwang007@outlook.com.
