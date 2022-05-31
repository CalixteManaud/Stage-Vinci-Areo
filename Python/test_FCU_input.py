#!/usr/bin/python
# -*-coding:latin_1-*-

import sys
import usb.core
import usb.util
from math import log

import FCU_descriptor

# Connexion spécifique du FCU
dev = usb.core.find(find_all=False, idVendor=0x04d8, idProduct=0x0050)

interface = 0
if dev.is_kernel_driver_active(interface) is True:
    dev.detach_kernel_driver(interface)
    usb.util.claim_interface(dev, interface)

inputsData = []
RotateSwitchBits = [[[1, 1, 5], [1, 1, 6]], [[2, 1, 0], [2, 1, 1]],
                    [[2, 1, 4], [2, 1, 5]], [[3, 0, 4], [3, 0, 5]],
                    [[3, 1, 4], [3, 1, 5]], [[5, 1, 2], [5, 1, 3]]]
for i in range(6):
    arr = [0x36, 0x41 + i * 2, 0x00, 0x00]
    dev.write(0x1, arr)
    data = dev.read(0x81, 64, 10)
    inputsData.append([data[2], data[3]])
while True:
    try:
        print(inputsData)
        data = dev.read(0x82, 4, 5000)
        print(bin(data[2]))
        print(bin(data[3]))

        # Représentation décimale des 6 bits intérieurs de l'octet
        b = bin((data[1] & ~(1 << 6)) >> 1)
        groupe = int(b, 2)
        print(groupe)

        # Numéro du bit à 0
        # byte1 =  ~(data[2]) & 255
        # byte1 = (byte1 & -byte1)
        # byte1 = 0 if byte1 == 0 else log((byte1 & -byte1), 2) +1
        # byte1 = int(byte1)

        # Numéro du bit qui a changé
        for i in range(8):
            old = bin(inputsData[groupe][0])[2:].zfill(8)
            new = bin(data[2])[2:].zfill(8)
            endloop = 0
            for j in range(6):
                # print(RotateSwitchBits[j].count([groupe, 1, 7-i]) > 0)
                # print([groupe, 1, 7-i])
                # print(RotateSwitchBits[j])
                if RotateSwitchBits[j].count([groupe, 0, 7 - i]) > 0:
                    endloop = 1
            if endloop == 1:
                continue;
            if old[i] == "1" and new[i] == "0":
                # can send ON
                code = FCU_descriptor.codeOfInput([groupe, 0, 7 - i])
                print(code)
                print("on")
            if old[i] == "0" and new[i] == "1":
                # can send OFF
                code = FCU_descriptor.codeOfInput([groupe, 0, 7 - i])
                print(code)
                print("off")

        for i in range(8):
            old = bin(inputsData[groupe][1])[2:].zfill(8)
            new = bin(data[3])[2:].zfill(8)
            endloop = 0
            for j in range(6):
                if RotateSwitchBits[j].count([groupe, 1, 7 - i]) > 0:
                    endloop = 1
                    break
            if endloop == 1:
                continue
            if old[i] == "1" and new[i] == "0":
                # can send ON
                code = FCU_descriptor.codeOfInput([groupe, 1, 7 - i])
                print(code)
                print("on")
            if old[i] == "0" and new[i] == "1":
                # can send OFF
                code = FCU_descriptor.codeOfInput([groupe, 1, 7 - i])
                print(code)
                print("off")

        for i in range(6):
            for j in range(2):
                if (groupe != RotateSwitchBits[i][j][0]):
                    continue
                old = bin(inputsData[groupe][RotateSwitchBits[i][j][1]])[2:].zfill(8)
                oldbit = old[7 - RotateSwitchBits[i][j][2]]
                new = bin(data[RotateSwitchBits[i][j][1] + 2])[2:].zfill(8)
                newbit = new[7 - RotateSwitchBits[i][j][2]]
                if oldbit != newbit:
                    k = 1 if j == 0 else 0
                    old2 = bin(inputsData[groupe][RotateSwitchBits[i][k][1]])[2:].zfill(8)
                    oldbit2 = old[7 - RotateSwitchBits[i][k][2]]
                    new2 = bin(data[RotateSwitchBits[i][k][1] + 2])[2:].zfill(8)
                    newbit2 = new[7 - RotateSwitchBits[i][k][2]]
                    if oldbit2 != newbit2:
                        print("ERROR SPEED")
                        break
                    if oldbit == oldbit2:
                        if j == 0:
                            # can send LEFT ON
                            print(code)
                            print("LEFT ON")
                        else:
                            # can send RIGHT ON
                            print(code)
                            print("RIGHT ON")
                    else:
                        if k == 0:
                            # can send LEFT ON
                            print(code)
                            print("LEFT ON")
                        else:
                            # can send RIGHT ON
                            print(code)
                            print("RIGHT ON")

        # code = MCDU_CPT.test([groupe, byte1])
        inputsData[groupe] = [data[2], data[3]]

        # print 'Groupe : {}, Bit1 : {}, Code : '.format(groupe, byte1)
        print("a")
    except usb.core.USBError as e:
        data = None
        if e.args == ('Operation timed out',):
            continue
