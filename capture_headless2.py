#!//home/litterbot/files/env/bin/python3

from picamera2 import Picamera2

camera_busy = False  # Flag to indicate whether the camera is currently in use
picam2 = Picamera2()



def capture():
    global camera_busy
    global picam2    
    # print(np_array)
    picam2.capture_file("trash.jpg")
