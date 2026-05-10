# Firmware

Future rover software lives here.

This folder is intentionally separate from `../pcb_testing_firmware/`. The existing Arduino sketches in `pcb_testing_firmware/` are for PCB testing and electronics bring-up, not the final rover software stack.

## Status
- Reserved for the software lead to update later.
- Add final rover control, autonomy, perception, navigation, or integration code here when ready.
- Keep docs for the final software stack in this folder or in clearly named subfolders.

## Suggested structure
- `controllers/` - Low-level rover control code.
- `navigation/` - Autonomy, path planning, or mission logic.
- `perception/` - Camera, LiDAR, and detection code.
- `docs/` - Software architecture, setup, and operating notes.
