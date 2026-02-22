# Brushless Motor Test Board — Rev A
Bench test procedure (ESC pass-through breakout)

## 0) Equipment
- Bench supply or flight pack matching the ESC/motor rating (start with a small pack, e.g., 3–4S).
- ESC + brushless motor + prop removed (run un-propped for safety).
- Signal source: RC receiver or microcontroller PWM (50 Hz, 1–2 ms) with ground common.
- DMM; optional clamp meter or in-line wattmeter for current.

## 1) Visual / Continuity (unpowered)
1. Inspect VIN/VOUT terminals for correct polarity markings; check 3-pin signal header orientation (signal, +5 V/BEC, GND).
2. DMM continuity: VIN to GND open; VOUT to GND open; VIN to VOUT open.

## 2) Wiring
1. Connect battery + to VIN, – to GND.
2. Connect ESC power leads: ESC + to VOUT, ESC – to GND.
3. Connect ESC servo lead to 3-pin header (signal to signal, +5 V/BEC to center, GND to GND). If your controller supplies 5 V, disable or isolate BEC as required.
4. Common ground between signal source and board.

## 3) Power-Up / Arming
1. Throttle low (1.0 ms).  
2. Apply battery. Listen for ESC arming tones. If none, power off and recheck signal orientation and ground.

## 4) Throttle Ramp (no prop)
1. Increase PWM gradually to mid (1.5 ms) then back to idle; motor should spin smoothly with no cogging/chatter.
2. Ramp briefly to 1.8–2.0 ms for a few seconds; watch current draw and board temperature. Keep runs short without prop.

## 5) BEC / 5 V Rail Check (if ESC provides BEC)
1. Measure 5 V on the center pin of the signal header relative to GND. Ensure it matches ESC spec (typically 5 V).  
2. If using external 5 V source instead, ensure BEC output is isolated or unused.

## 6) Brownout / Connector Sanity
1. Wiggle connectors lightly while motor idles; no resets or cut-outs should occur.
2. Briefly load the 5 V rail (e.g., 100 Ω) to confirm it holds voltage if BEC is in use.

## 7) Thermal Check
1. After several ramp cycles, touch-test (or IR) the board copper and terminals; should remain near ambient. ESC will warm; stop if ESC/motor overheats.

## 8) Pass/Fail
- ESC arms reliably; motor starts smoothly from idle to mid/full (unpropped).  
- No dropouts when wiggling connectors.  
- 5 V/BEC rail (if used) holds steady.  
- No excessive heating on the breakout terminals/copper during short runs.

## Notes
- This board is a passive breakout only; no added protection or filtering.  
- Always test unpropped first; add prop only after confirming smooth operation and keep clear of the prop arc.  
