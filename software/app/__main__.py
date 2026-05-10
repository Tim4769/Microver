import os
import threading

os.environ["PYGAME_HIDE_SUPPORT_PROMPT"] = "1"

from ..app import services

if __name__ == "__main__":
    services = {
        "camera": services.CameraService(),
        "control": services.ControlService(),
    }

    threading.Thread(
        target=services["camera"].start,
        daemon=True,
    ).start()

    services["control"].start()
