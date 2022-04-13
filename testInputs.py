#!/usr/bin/python
# -*-coding:latin_1-*-

import sys
import usb.core
import usb.util
from math import log

import MCDU_CPT

# Connexion sp�cifique du MCDU
dev = usb.core.find(find_all=False, idVendor=0x04d8, idProduct=0x0071)

interface = 0
if dev.is_kernel_driver_active(interface) is True:
    dev.detach_kernel_driver(interface)
    usb.util.claim_interface(dev, interface)

while True:
    try:
        data = dev.read(0x82, 4, 5000)

        b = bin((data[1] & ~(1 << 6)) >> 1)
        groupe = int(b, 2)

        byte1 = ~(data[2]) & 255
        byte1 = (byte1 & -byte1)
        byte1 = 0 if byte1 == 0 else log((byte1 & -byte1), 2) + 1
        byte1 = int(byte1)

        touch = "Error"
        call = "relach�"

        if groupe == 8:
            if byte1 == 1:
                touch = "la touche PROG"
                call = "appuy�"
            elif byte1 == 2:
                touch = "la touche DIR"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche LSK2"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche LSK1"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche SECFPLN"
                call = "appuy�"
            elif byte1 == 6:
                touch = "la touche FUELPRED"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche PREF"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche INIT"
                call = "appuy�"
            else:
                touch = "button"
                call = "relach�"

        if groupe == 7:
            if byte1 == 1:
                touch = "la touche RADNAV"
                call = "appuy�"
            elif byte1 == 2:
                touch = "la touche FPLN"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche LSK3"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche DATA"
                call = "appuy�"
            elif byte1 == 5:
                touch = "Aucune touche"
                call = "attribu�"
            elif byte1 == 6:
                touch = "la touche RSK1"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche RSK3"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche RSK5"
                call = "appuy�"
            else:
                touch = "Button"
                call = "relach�"

        if groupe == 6:
            if byte1 == 1:
                touch = "la touche AIRPORT"
                call = "appuy�"
            elif byte1 == 2:
                touch = "Aucune touche"
                call = "attribu�"
            elif byte1 == 3:
                touch = "la touche LSK4"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche ATCCOMM"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche MCDUMENU"
                call = "appuy�"
            elif byte1 == 6:
                touch = "la touche RSK2"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche RSK4"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche RSK6"
            else:
                touch = "Button"
                call = "relach�"

        if groupe == 5:
            if byte1 == 1:
                touch = "la touche Larrow"
                call = "appuy�"
            elif byte1 == 2:
                touch = "la touche Uarrow"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche LSK5"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche A"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche B"
                call = "appuy�"
            elif byte1 == 6:
                touch = "La touche C"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche D"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche E"
                call = "appuy�"
            else:
                touch = "Button"
                call = "relach�"

        if groupe == 4:
            if byte1 == 1:
                touch = "la touche Rarrow"
                call = "appuy�"
            elif byte1 == 2:
                touch = "la touche Darrow"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche LSK6"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche F"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche G"
                call = "appuy�"
            elif byte1 == 6:
                touch = "la touche H"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche I"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche J"
                call = "appuy�"
            else:
                touch = "Button"
                call = "relach�"

        if groupe == 3:
            if byte1 == 1:
                touch = "la touche 1"
                call = "appuy�"
            elif byte1 == 2:
                touch = "la touche 2"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche 3"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche K"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche L"
                call = "appuy�"
            elif byte1 == 6:
                touch = "la touche M"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche N"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche O"
                call = "appuy�"
            else:
                touch = "Button"
                call = "relach�"

        if groupe == 2:
            if byte1 == 1:
                touch = "la touche 4"
                call = "appuy�"
            elif byte1 == 2:
                touch = "la touche 5"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche 6"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche P"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche Q"
                call = "appuy�"
            elif byte1 == 6:
                touch = "la touche R"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche S"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche T"
                call = "appuy�"
            else:
                touch = "Button"
                call = "relach�"

        if groupe == 1:
            if byte1 == 1:
                touch = "la touche 7"
                call = "appuy�"
            elif byte1 == 2:
                touch = "la touche 8"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche 9"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche U"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche V"
                call = "appuy�"
            elif byte1 == 6:
                touch = "la touche W"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche X"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche Y"
                call = "appuy�"
            else:
                touch = "Button"
                call = "relach�"

        if groupe == 0:
            if byte1 == 1:
                touch = "Aucun button"
                call = "attribu�"
            elif byte1 == 2:
                touch = "la touche 0"
                call = "appuy�"
            elif byte1 == 3:
                touch = "la touche plus"
                call = "appuy�"
            elif byte1 == 4:
                touch = "la touche Z"
                call = "appuy�"
            elif byte1 == 5:
                touch = "la touche Slash"
                call = "appuy�"
            elif byte1 == 6:
                touch = "la touche SP"
                call = "appuy�"
            elif byte1 == 7:
                touch = "la touche 0VFY"
                call = "appuy�"
            elif byte1 == 8:
                touch = "la touche CLR"
                call = "appuy�"
            else:
                touch = "Aucune Button"
                call = "appuy�"

        code = MCDU_CPT.test([groupe, byte1])

        print('Groupe : {}, Bit1 : {}, Code : {}'.format(groupe, byte1, code))
    except usb.core.USBError as e:
        data = None
        if e.args == ('Operation timed out',):
            continue
