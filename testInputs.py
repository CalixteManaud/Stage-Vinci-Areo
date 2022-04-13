#!/usr/bin/python
# -*-coding:latin_1-*-

import sys
import usb.core
import usb.util
from math import log

import MCDU_CPT

# Connexion spécifique du MCDU
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
        call = "relaché"

        if groupe == 8:
            if byte1 == 1:
                touch = "la touche PROG"
                call = "appuyé"
            elif byte1 == 2:
                touch = "la touche DIR"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche LSK2"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche LSK1"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche SECFPLN"
                call = "appuyé"
            elif byte1 == 6:
                touch = "la touche FUELPRED"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche PREF"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche INIT"
                call = "appuyé"
            else:
                touch = "button"
                call = "relaché"

        if groupe == 7:
            if byte1 == 1:
                touch = "la touche RADNAV"
                call = "appuyé"
            elif byte1 == 2:
                touch = "la touche FPLN"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche LSK3"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche DATA"
                call = "appuyé"
            elif byte1 == 5:
                touch = "Aucune touche"
                call = "attribué"
            elif byte1 == 6:
                touch = "la touche RSK1"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche RSK3"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche RSK5"
                call = "appuyé"
            else:
                touch = "Button"
                call = "relaché"

        if groupe == 6:
            if byte1 == 1:
                touch = "la touche AIRPORT"
                call = "appuyé"
            elif byte1 == 2:
                touch = "Aucune touche"
                call = "attribué"
            elif byte1 == 3:
                touch = "la touche LSK4"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche ATCCOMM"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche MCDUMENU"
                call = "appuyé"
            elif byte1 == 6:
                touch = "la touche RSK2"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche RSK4"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche RSK6"
            else:
                touch = "Button"
                call = "relaché"

        if groupe == 5:
            if byte1 == 1:
                touch = "la touche Larrow"
                call = "appuyé"
            elif byte1 == 2:
                touch = "la touche Uarrow"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche LSK5"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche A"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche B"
                call = "appuyé"
            elif byte1 == 6:
                touch = "La touche C"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche D"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche E"
                call = "appuyé"
            else:
                touch = "Button"
                call = "relaché"

        if groupe == 4:
            if byte1 == 1:
                touch = "la touche Rarrow"
                call = "appuyé"
            elif byte1 == 2:
                touch = "la touche Darrow"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche LSK6"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche F"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche G"
                call = "appuyé"
            elif byte1 == 6:
                touch = "la touche H"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche I"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche J"
                call = "appuyé"
            else:
                touch = "Button"
                call = "relaché"

        if groupe == 3:
            if byte1 == 1:
                touch = "la touche 1"
                call = "appuyé"
            elif byte1 == 2:
                touch = "la touche 2"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche 3"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche K"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche L"
                call = "appuyé"
            elif byte1 == 6:
                touch = "la touche M"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche N"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche O"
                call = "appuyé"
            else:
                touch = "Button"
                call = "relaché"

        if groupe == 2:
            if byte1 == 1:
                touch = "la touche 4"
                call = "appuyé"
            elif byte1 == 2:
                touch = "la touche 5"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche 6"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche P"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche Q"
                call = "appuyé"
            elif byte1 == 6:
                touch = "la touche R"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche S"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche T"
                call = "appuyé"
            else:
                touch = "Button"
                call = "relaché"

        if groupe == 1:
            if byte1 == 1:
                touch = "la touche 7"
                call = "appuyé"
            elif byte1 == 2:
                touch = "la touche 8"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche 9"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche U"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche V"
                call = "appuyé"
            elif byte1 == 6:
                touch = "la touche W"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche X"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche Y"
                call = "appuyé"
            else:
                touch = "Button"
                call = "relaché"

        if groupe == 0:
            if byte1 == 1:
                touch = "Aucun button"
                call = "attribué"
            elif byte1 == 2:
                touch = "la touche 0"
                call = "appuyé"
            elif byte1 == 3:
                touch = "la touche plus"
                call = "appuyé"
            elif byte1 == 4:
                touch = "la touche Z"
                call = "appuyé"
            elif byte1 == 5:
                touch = "la touche Slash"
                call = "appuyé"
            elif byte1 == 6:
                touch = "la touche SP"
                call = "appuyé"
            elif byte1 == 7:
                touch = "la touche 0VFY"
                call = "appuyé"
            elif byte1 == 8:
                touch = "la touche CLR"
                call = "appuyé"
            else:
                touch = "Aucune Button"
                call = "appuyé"

        code = MCDU_CPT.test([groupe, byte1])

        print('Groupe : {}, Bit1 : {}, Code : {}'.format(groupe, byte1, code))
    except usb.core.USBError as e:
        data = None
        if e.args == ('Operation timed out',):
            continue
