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
                camflag=ser.read(ser.inWaiting())
                print(camflag)
                print("take pic and do stuff")
                sleep(5)
