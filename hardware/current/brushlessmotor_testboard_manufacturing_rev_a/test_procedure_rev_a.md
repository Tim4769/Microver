# Brushless Motor Test Board - Rev A

Passive ESC breakout check. Test with the prop removed.

## Equipment
- Battery or bench supply that matches the ESC
- ESC, brushless motor, and PWM signal source
- DMM

## Quick Test
1. Unpowered: check connector orientation and confirm VIN to GND, VOUT to GND, and VIN to VOUT are not shorted.
2. Wire it up: battery to VIN/GND, ESC power to VOUT/GND, and the ESC servo lead to the 3-pin header with a common ground.
3. Power-up: start at low throttle, power on, and confirm the ESC arms normally.
4. Motor check: ramp from idle to mid throttle, then briefly near full throttle. The motor should spin smoothly with no cogging or cutout.
5. If the ESC provides BEC, measure the 5 V pin and make sure it stays steady. Lightly wiggle connectors while idling to catch bad connections.

## Pass
- ESC arms every time
- Motor runs smoothly without dropouts
- 5 V/BEC rail is stable if used
- Breakout board stays near ambient during short runs
