#!/usr/bin/python
#-*-coding:latin_1-*-

import sys
import usb.core
import usb.util
from math import log

import MCDU_CPT

#Connexion spécifique du MCDU
dev = usb.core.find(find_all=False, idVendor=0x04d8, idProduct=0x0071)

interface = 0
if dev.is_kernel_driver_active(interface) is True:
    dev.detach_kernel_driver(interface)
    usb.util.claim_interface(dev, interface)

while True:
    try:
        data = dev.read(0x82, 4, 5000)
        
        b = bin((data[1]  & ~(1 << 6)) >> 1)
        groupe = int( b, 2)

        byte1 =  ~(data[2]) & 255
        byte1 = (byte1 & -byte1)
        byte1 = 0 if byte1 == 0 else log((byte1 & -byte1), 2) +1
        byte1 = int(byte1)
        
        code = MCDU_CPT.test([groupe, byte1])
        
        print 'Groupe : {}, Bit1 : {}, Code : {}'.format(groupe, byte1, code)
    except usb.core.USBError as e:
        data = None
        if e.args == ('Operation timed out',):
            continue
