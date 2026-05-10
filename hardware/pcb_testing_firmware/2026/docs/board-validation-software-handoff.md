# PCB Testing Software Handoff - 2026

Software-facing notes for validating the Microver 2026 final compute and control boards. These sketches are for PCB testing and electronics bring-up, not the final rover software stack.

## Control stack
- High-level control can run on the Raspberry Pi.
- Low-level drive and actuator bring-up uses Arduino Nano Every sketches in `../controllers/`.
- The final dual-Arduino compute board mates to the final control board through the `Left` and `Right` interconnects.
- Power and actuator details live in `power-and-actuator-control-handoff.md`.

## Final control-board drive pin map
The 2026 both-sides drive test uses this Arduino Nano Every pin map.

| Drive side | PWM | INA | INB | ENA/DIAGA | ENB/DIAGB | CS |
| --- | --- | --- | --- | --- | --- | --- |
| Left, Drive 4-6 | D10 | D6 | D7 | A6 | A7 | A0 |
| Right, Drive 1-3 | D9 | D4 | D5 | D8 | D13 | A1 |

## Bring-up sketches
- `../controllers/simple_motor_test/simple_motor_test.ino` - Minimal single-driver motor test.
- `../controllers/minimum_one_wheel_test/minimum_one_wheel_test.ino` - Minimal one-wheel test.
- `../controllers/one_side_spin_test/one_side_spin_test.ino` - One-side drivetrain spin test.
- `../controllers/both_sides_drive_test/both_sides_drive_test.ino` - Both-sides drive test.

## Serial controls
The both-sides drive test uses `115200` baud.

| Command | Behavior |
| --- | --- |
| `f` | Run both sides forward for the configured test duration. |
| `r` | Run both sides reverse for the configured test duration. |
| `s` | Stop immediately. |
| `d` | Print driver diagnostics and current-sense ADC values. |
| `+` | Increase test speed. |
| `-` | Decrease test speed. |

## Validation flow
1. Lift or unload the rover before first motor tests.
2. Confirm the final compute board is oriented correctly on the final control board.
3. Start with `simple_motor_test`, then move to one-wheel and one-side tests.
4. Use `both_sides_drive_test` only after each side has been validated independently.
5. Watch `ENA/DIAGA`, `ENB/DIAGB`, and current-sense readings during every drive test.
6. Keep unused actuator outputs disabled unless hardware is installed.
