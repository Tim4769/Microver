import json

import pygame
import serial


class ControlService:
    def __init__(self, port="/dev/ttyACM0"):
        pygame.init()
        pygame.joystick.init()

        self.ser = serial.Serial(port, 115200, timeout=3)
        self.joystick = pygame.joystick.Joystick(0)
        self.joystick.init()

    def _serial_data(self):
        x = self.joystick.get_axis(0)
        y = self.joystick.get_axis(1)

        x = 0 if abs(x) < 0.05 else x
        y = 0 if abs(y) < 0.05 else y

        left = y - x
        right = y + x

        max_val = max(abs(left), abs(right), 1.0)
        left /= max_val
        right /= max_val

        left = int(left * 255)
        right = int(right * 255)

        return {
            "motors": {"left": left, "right": right},
            "servos": {
                "trap": self.joystick.get_button(1),
                "flag": self.joystick.get_button(0),
            },
        }

    def start(self):
        print(f"Control service started with serial {self.ser.port}")
        while True:
            pygame.event.pump()
            data = self._serial_data()
            self.ser.write((json.dumps(data) + "\n").encode("utf-8"))
