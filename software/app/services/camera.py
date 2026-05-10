import io
import os
import threading

import uvicorn
from fastapi import FastAPI
from fastapi.responses import FileResponse, StreamingResponse
from fastapi.staticfiles import StaticFiles
from picamera2 import Picamera2
from picamera2.encoders import JpegEncoder
from picamera2.outputs import FileOutput


class StreamingOutput(io.BufferedIOBase):
    def __init__(self):
        super().__init__()
        self.frame = None
        self.condition = threading.Condition()

    def write(self, buf):
        with self.condition:
            self.frame = buf
            self.condition.notify_all()
        return len(buf)


class CameraService:
    def __init__(self, size=(800, 600)):
        os.environ["LIBCAMERA_LOG_LEVELS"] = "*:ERROR"
        self.app = FastAPI()

        self.picam2 = Picamera2()
        self.config = self.picam2.create_video_configuration(main={"size": size})
        self.picam2.configure(self.config)

        self.output = StreamingOutput()
        self.encoder = JpegEncoder()

        self.picam2.start_recording(self.encoder, FileOutput(self.output))

        self.app.mount(
            "/static", StaticFiles(directory="static", html=True), name="static"
        )
        self._setup_routes()

    def _setup_routes(self):
        @self.app.get("/")
        def index():
            return FileResponse("static/index.html")

        @self.app.get("/stream")
        def stream():
            return StreamingResponse(
                self._frame_generator(),
                media_type="multipart/x-mixed-replace; boundary=frame",
            )

    def _frame_generator(self):
        while True:
            with self.output.condition:
                self.output.condition.wait()
                frame = self.output.frame
            if frame:
                yield (b"--frame\r\nContent-Type: image/jpeg\r\n\r\n" + frame + b"\r\n")

    def start(self, port=8000):
        print(f"Camera service started at http://raspberrypi.local:{port}")
        uvicorn.run(
            self.app,
            host="0.0.0.0",
            port=port,
            reload=False,
            workers=1,
        )
