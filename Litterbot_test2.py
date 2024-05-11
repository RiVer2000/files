import tty, sys, termios, serial
from time import sleep
import imagedetect_color
import capture_headless

ser = serial.Serial('/dev/serial/by-id/usb-Arduino_Srl_Arduino_Uno_85439303333351612151-if00',115200,bytesize=8, parity='N', stopbits=1, timeout=None);

filedescriptors = termios.tcgetattr(sys.stdin)
tty.setcbreak(sys.stdin)
x = 0
rxmsg = ser.readline()
print(rxmsg.decode('ascii'))

while 1:
  x=sys.stdin.read(1)[0]
  ser.write(x.encode('ascii'))
  print("You pressed", x)
  if (ser.inWaiting()>0):
    rx=ser.read(ser.inWaiting())
    ser.flushInput()
    ser.flushOutput()
    #capture pic
    capture_headless.capture()
    camflag = imagedetect_color.color_detect()
    ser.write('m'.encode('ascii')) #deploy arm
    sleep(3)
    ser.write('c'.encode('ascii')) #close gripper

    if (camflag == 1):
      ser.write('n'.encode('ascii')) #stow arm
      sleep(2)
      ser.write('o'.encode('ascii')) #open gripper
    else:
      ser.write('b'.encode('ascii')) #stow arm right
      sleep(2)
      ser.write('o'.encode('ascii')) #open gripper

    sleep(5)
    print("Image Processing Complete")
    ser.flushInput()
    ser.flushOutput()
    ser.write('z'.encode('ascii'))
