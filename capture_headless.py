#!//home/litterbot/files/env/bin/python3

from picamera2 import Picamera2

def capture():

  picam2 = Picamera2()
  config = picam2.create_still_configuration()
  picam2.configure(config)
  
  picam2.start()
  
  # np_array = picam2.capture_array()
  # print(np_array)
  picam2.capture_file("trash.jpg")
  picam2.stop()
  
