import sys
import usb.core
import usb.util
import os
import can
import time
from math import log
from gpiozero import LED, Button

import MCDU_CPT

button = Button(4, pull_up=False)
led = LED(17)
led.off()

os.system('sudo ip link set can0 type can bitrate 250000')
os.system('sudo ifconfig can0 up')
can0 = can.interface.Bus(channel = 'can0', bustype = 'socketcan_ctypes')# socketcan_native
timest = 0
timest2 = 0
lastCode = None
pressed = False

dev = usb.core.find(find_all=False, idVendor=MCDU_CPT.idVendor, idProduct=MCDU_CPT.idProduct)
interface = 0
if dev.is_kernel_driver_active(interface) is True:
    dev.detach_kernel_driver(interface)
    usb.util.claim_interface(dev, interface)

#help(usb.util)

while True:
    msg = can0.recv(0.1)
    #print(dev.write(0x82, 4, 1))
    
    #can0.send(msg)
    #time.sleep(1)
    if msg is None:
        try:
            data = dev.read(0x82, 4, 1)
            
            if(data is not None):
                print(data)
                led.on()
                time.sleep(0.1)
                led.off()

                b = bin((data[1]  & ~(1 << 6)) >> 1)
                groupe = int( b, 2)

                byte1 =  ~(data[2]) & 255
                byte1 = (byte1 & -byte1)
                byte1 = 0 if byte1 == 0 else log((byte1 & -byte1), 2) +1
                byte1 = int(byte1)
                
                code = MCDU_CPT.codeOf([groupe, byte1])
                codeArray = code.to_bytes(2, byteorder='big')

                print(round(time.time() * 1000))
                #print(codeArray)
                                
                #print 'Groupe : {}, Bit1 : {}, Code : {}, Char : {}'.format(groupe, byte1, code, char)
  
                #msg = can.Message(arbitration_id=0x123, data=[data[0],data[1], data[2], data[3]], extended_id=False)
                if codeArray[0] == 0 and codeArray[1] == 0 and pressed == True:
                    codeArray = lastCode.to_bytes(2, byteorder='big')
                    msg = can.Message(arbitration_id=0x123, data=[codeArray[0], codeArray[1], 0, 2, 0, 0, 0, 0], extended_id=False)
                    can0.send(msg)
                    pressed = False
                elif (codeArray[0] != 0 or codeArray[1] != 0) and pressed == False:
                    msg = can.Message(arbitration_id=0x123, data=[codeArray[0], codeArray[1], 0, 1, 0, 0, 0, 0], extended_id=False)
                    can0.send(msg)
                    lastCode = code
                    pressed = True
                    #print("Sent {} bits : {} {} = Code : {} ".format(msg.dlc, codeArray[0], codeArray[1], code))
        except usb.core.USBError as e:
            data = None
            if e.args == ('Operation timed out',):
                continue
    else:
        print(msg.data)
