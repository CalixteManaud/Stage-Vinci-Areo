#!/usr/bin/python
#-*-coding:latin_1-*-
import usb
import sys
import usb.core
import usb.util

#Liste les connexions
devices = list(usb.core.find(find_all=True))
print(devices)
