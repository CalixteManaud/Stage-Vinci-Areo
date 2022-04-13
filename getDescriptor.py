#!/usr/bin/python
#-*-coding:latin_1-*-

import sys
import usb.core
import usb.util

#Connexion spécifique du MCDU
dev = usb.core.find(find_all=False, idVendor=0x04d8, idProduct=0x0050)

for cfg in dev:
    print(cfg._get_full_descriptor_str())
    for i in cfg:
        for e in i:
            print(e.__str__())

print(dev._get_full_descriptor_str())
         
