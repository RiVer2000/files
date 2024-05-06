import serial
from time import sleep
sleep(1)
ser = serial.Serial('/dev/serial/by-id/usb-Arduino_Srl_Arduino_Uno_85439303333351612151-if00',115200);
camflag = 0

rxmsg = ser.readline()
print(rxmsg)

while 1:
	charcommand = input("Type a letter:")
	ser.write(charcommand.encode('utf-8'))
	camflag = ser.readline()
	#print(camflag)
	sleep(0.5)
	if (camflag.strip):
		print("take pic and do stuff")
		sleep(5)
		camflag = 0

