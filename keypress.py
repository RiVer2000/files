import keyboard
import time

global releaseListening
keepListening = True

def key_press(key):
	print(key.name)
	if key.name == "esc":
		keepListening = False
keyboard.on_press(key_press)
while keepListening:
	time.sleep(1)
