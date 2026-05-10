# Power and Actuator Control Handoff

## System Overview

The rover has six drive wheels. The wheels are split into two sides, with one
motor controller driving the three wheels on the left side and one motor
controller driving the three wheels on the right side.

The final control board has four servo motor positions, but the current rover
uses only three of them. Leave the unused servo output disabled in software
unless a fourth actuator is installed later.

The rover also uses a camera for object detection and LiDAR for object
avoidance. High-level software uses those sensors to decide where the rover
goes, while the low-level firmware handles the motor and actuator outputs.

## Final Control Board Functions

| Function | Software responsibility |
| --- | --- |
| Boost enable | Drive the boost-control GPIO. |
| Left/right drive channels | Generate direction and PWM for two H-bridge channels. |
| Six wheel encoders | Count quadrature signals for per-wheel feedback. |
| Driver diagnostic pins | Read enable/fault state from the motor drivers. |
| Current sense | Read analog current feedback from the motor drivers. |
| Servo outputs | Generate servo pulses for installed actuators. |

Each rover side has one drive channel. Three wheel motors are connected to each
side's drive channel:

| Drive group | Physical motors |
| --- | --- |
| Drive 1-3 / right channel | `Drive_1`, `Drive_2`, `Drive_3` |
| Drive 4-6 / left channel | `Drive_4`, `Drive_5`, `Drive_6` |

The motors on one side receive the same H-bridge output, but each wheel still has
its own encoder input. Software can therefore command by side and monitor by
wheel.

## Boost Control

Firmware owns one boost-control signal exposed as `on/off_Boost`.

| Compute board | Boost-control pin |
| --- | --- |
| STM32 compute board | `PC10` / `BOOST_EN` / `TP15` |

## Drive Motor Control

Each rover side uses one VNH5019A-E H-bridge:

| Software channel | Board signal group | Physical drive connectors |
| --- | --- | --- |
| Right drive | `DRV1_*` signals | `Drive_1`, `Drive_2`, `Drive_3` |
| Left drive | `DRV2_*` signals | `Drive_4`, `Drive_5`, `Drive_6` |

VNH5019A-E control table from the datasheet:

| Command | `INA` | `INB` | `PWM` | Behavior |
| --- | --- | --- | --- | --- |
| Stop / brake low | `0` | `0` | `1` | Both outputs low. |
| Clockwise | `1` | `0` | duty | `OUTA` high, `OUTB` low when PWM is high. |
| Counterclockwise | `0` | `1` | duty | `OUTA` low, `OUTB` high when PWM is high. |
| Brake high | `1` | `1` | `1` | Both outputs high. |
| PWM off | any | any | `0` | Low-side switches off. |

Firmware notes:

- Use `INA` and `INB` for direction.
- Use `PWM` for speed; the datasheet allows PWM up to `20 kHz`.
- Keep `ENA/DIAGA` and `ENB/DIAGB` high for normal use. If either reads low,
  the driver is reporting a fault.
- `CS` outputs motor-current feedback when current sense is enabled.

## Servo Outputs

The final control board has four servo-style outputs.

| Header | Signal |
| --- | --- |
| `J24` / Servo 1 | `SERVO1_PWM` |
| `J25` / Servo 2 | `SERVO2_PWM` |
| `J26` / Servo 3 | `SERVO3_PWM` |
| `J27` / Servo 4 | `SERVO4_PWM` |

The current rover uses three of the four servo outputs. The fourth output is
unused.

Brushless DC ESCs use the same RC-servo-style signal: the ESC reads pulse width,
not the off-time. Typical values are `1000 us` for zero throttle, `1500 us` for
midpoint, and `2000 us` for maximum throttle.

ESC calibration is needed so the ESC learns this controller's minimum and
maximum throttle pulse widths. Calibration is not the same as arming:

- Calibration is usually done once: send `2000 us`, power the ESC, wait for the
  calibration beeps, then send `1000 us`.
- Arming happens every startup: send `1000 us` for about `2` to `5` seconds so
  the ESC accepts that throttle is safely at zero.

Software should not send a run command immediately after power-up. Keep sending
`1000 us` during the arming wait. A non-blocking `millis()` timer is preferred so
the controller can still read safety inputs while waiting.

For first fan tests, use a very low run value because current can rise quickly if
the fan spins too fast. Start near `1050 us` to `1100 us`, and only increase if
the motor does not spin smoothly.

## Bring-Up Checklist

1. Boot firmware with the rover lifted and all drive commands disabled.
2. Confirm each motor-driver diagnostic pin reads healthy when enabled.
3. Send low PWM to one drive side and verify wheel direction.
4. Repeat for the other drive side.
5. Verify each installed servo output.
6. Arm the brushless ESC at `1000 us` before sending any run command.
7. Start brushless fan tests near `1050 us` to `1100 us`.
8. Leave unused actuator outputs disabled in software.
