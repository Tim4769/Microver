# Microver

Microver is a hardware/firmware project with PCB manufacturing outputs, Arduino/Raspberry Pi code, and brand assets. This repo is organized so current work lives in the 2025 folder and older experiments live in the archive.

## Repository layout

- `firmware/2025/` - Current Arduino code and notes for the 2025 build.
- `firmware/2025/knowledge base/` - Datasheets and build notes for drivers, lidar, and PCB work.
- `hardware/pcb-manufacturing-v1/` - Gerber and drill files for the v1 board.
- `hardware/pcb-manufacturing-rev-b/` - Gerber and drill files for Rev B.
- `archive/2024-code/` - Older Arduino/Raspberry Pi code and documentation.
- `assets/logos/` and `assets/logos-legacy/` - Current and legacy logo assets.

## Getting started

1. If you are fabricating a board, use the Gerber and drill files in the appropriate manufacturing folder.
2. If you are working on firmware, start in `firmware/2025/` and review the notes in `firmware/2025/knowledge base/` for required hardware and driver details.
3. For older experiments and reference code, check `archive/2024-code/`.

## Notes

- Manufacturing outputs are provided as Gerber and drill files (ready to upload to most PCB fabs).
- Documentation and component notes are included alongside the firmware.

## License

No license has been specified yet. If you plan to share or redistribute, add a license file.
