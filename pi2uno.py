import serial
from time import sleep
sleep(1)
ser = serial.Serial('/dev/serial/by-id/usb-Arduino_Srl_Arduino_Uno_85439303333351612151-if00',9600);

while 1:
	charcommand = input("Type a letter:")
	ser.write(charcommand.encode('utf-8'))


