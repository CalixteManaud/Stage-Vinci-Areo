#Importation des bibliothèques
import sys
import usb.core
import usb.util
import time
import RPi.GPIO as IOe

#Importation des fichiers
import FCU

# Connexion spécifique du FCU
dev = usb.core.find(find_all=False, idVendor=0x04d8, idProduct=0x0050)

interface = 0
if dev.is_kernel_driver_active(interface) is True:
    dev.detach_kernel_driver(interface)
    usb.util.claim_interface(dev, interface)

IOe.setwarnings(False)    
IOe.setmode(IOe.BOARD)

for segment in FCU.digits:
	IOe.setup(segment, IOe.OUT)
	IOe.output(segment, 0)
	
for digit in FCU.digitsHex:
	IOe.setup(digit, IOe.OUT)
	IOe.output(digit, 1)
	
num = {' ':(0,0,0,0,0,0,0),
	'0':(1,1,1,1,1,1,0),
	'1':(0,1,1,0,0,0,0),
	'2':(1,1,0,1,1,0,1),
	'3':(1,1,1,1,0,0,1),
	'4':(0,1,1,0,0,1,1),
	'5':(1,0,1,1,0,1,1),
	'6':(1,0,1,1,1,1,1),
	'7':(1,1,1,0,0,0,0),
	'8':(1,1,1,1,1,1,1),
	'9':(1,1,1,1,0,1,1)}
	
try:
	while True:
		n = time.ctime()[11:13]+time.ctime()[14:16]
		s = str(n).rjust(4)
		for digit in range (4):
			for loop in range (0.7):
				IOe.output(FCU.digits[loop], num[s[digit]][loop])
				if (int(time.ctime()[18:19])%2 == 0) and (digit == 1):
					IOe.output(25, 1)
				else:
					IOe.output(25, 0)
			IOe.output(FCU.digitsHex[digit], IOe.HIGH)
			time.sleep(0.001)
			IOe.output(FCU.digitsHex[digit], IOe.LOW)
finally:
	IOe.cleanup()
