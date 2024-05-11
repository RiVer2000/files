#!//home/litterbot/files/env/bin/python3

from picamera2 import Picamera2

camera_busy = False  # Flag to indicate whether the camera is currently in use

def capture():
    global camera_busy
    
    if camera_busy:
        print("Camera is currently busy. Skipping capture.")
        return
    
    camera_busy = True
    
    try:
        picam2 = Picamera2()
        config = picam2.create_still_configuration()
        picam2.configure(config)

        picam2.start()

        # np_array = picam2.capture_array()
        # print(np_array)
        picam2.capture_file("trash.jpg")
        picam2.stop()
    finally:
        camera_busy = False
