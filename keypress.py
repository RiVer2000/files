import tty, sys, termios, serial
from time import sleep

ser = serial.Serial('/dev/serial/by-id/usb-Arduino_Srl_Arduino_Uno_85439303333351612151-if00',115200,bytesize=8, parity='N', stopbits=1, timeout=None);

filedescriptors = termios.tcgetattr(sys.stdin)
tty.setcbreak(sys.stdin)
x = 0
while 1:
  x=sys.stdin.read(1)[0]
  ser.write(x.encode('ascii'))
  print("You pressed", x)
  if (ser.inWaiting()>0):
    #camflag=ser.read(ser.inWaiting())
    #print(camflag)
    #capture pic
    #use tensor flow function
    camflag = 1
#    if (camflag == 1):
#      x = 'm'
#      ser.write(x.encode('ascii')) #deploy arm
#      x = 'c'
#      ser.write(x.encode('ascii')) #close gripper
#      x = 'n'
#      ser.write(x.encode('ascii')) #stow arm
#      x = 'o'
#      ser.write(x.encode('ascii')) #open gripper
    print("Image Processing Complete")
    sleep(5)
