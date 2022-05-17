#!/usr/bin/python
# -*-coding:latin_1-*-

import usb.util
import time

import FCU

# Connexion spécifique du FCU
dev = usb.core.find(find_all=False, idVendor=0x04d8, idProduct=0x0050)

interface = 0

outs = []
outs.append([0x37, 0x40, 0x00, 0x00])
outs.append([0x37, 0x42, 0x00, 0x00])
outs.append([0x37, 0x44, 0x4A, 0xBD])
outs.append([0x37, 0x46, 0x00, 0x00])
outs.append([0x37, 0x48, 0x00, 0x00])
outs.append([0x37, 0x4A, 0x00, 0x80])

out = FCU.outputsOfCode(326)
digits = [0x39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

if dev.is_kernel_driver_active(interface) is True:
    dev.detach_kernel_driver(interface)
    usb.util.claim_interface(dev, interface)

text_present = "Bonjour, ce programme teste les afficheurs du FCU v0.1"
text_info = "Pour vérifier un afficheur, si vous mettez 1 l'afficheur s'allume, en revanche si c'est 0, cela sera " \
            "éteint"
text3 = "Certaines valeurs ne marchent pas nous allons le régler dans la prochaine version"
text_reponse = "Regarder votre FCU un bouton vient d'être allumé"

print(text_present, end="")
print(" ")
print(text_info)
print(" ")
print(text3)
print(" ")

info = [313, 315, 316, 317, 318, 319, 320, 321, 339]

digits = FCU.digitsOfCode(-2, 230, digits)


def test(on):
    code = 300
    for i in range(39):
        print("Code ", i)
        validCode = True
        for l in range(len(info)):
            if code == info[l]:
                validCode = False

        if not validCode:
            print("discard")
            code += 1
            continue

        out = FCU.outputsOfCode(code)
        code += 1

        for j in range(len(out)):
            byte = 2 ** out[j][2]

            if on == True:
                if out[j][1] == 0:
                    outs[out[j][0]][2] |= byte
                else:
                    outs[out[j][0]][3] |= byte
            else:
                byte = ~byte
                if out[j][1] == 0:
                    outs[out[j][0]][2] &= byte
                else:
                    outs[out[j][0]][3] &= byte

            dev.write(0x1, outs[out[j][0]])
        time.sleep(0.7)


test(True)

while True:
    try:
        arr = [0x47, 0x00, 0x00, 0x00]
        # dev.write(0x1, arr)
        # Inverse la valeur des bits envoyés
        arr = [0x43, 0x09, 0x00]
        dev.write(0x1, arr)
        # Eteins tous les digits 
        dev.write(0x1, digits)
        arr = [0x41, 0x0A, 0x0F]
        dev.write(0x1, arr)
        dev.write(0x1, outs[0])
        dev.write(0x1, outs[1])
        dev.write(0x1, outs[2])
        dev.write(0x1, outs[3])
        dev.write(0x1, outs[4])
        dev.write(0x1, outs[5])
        # arr = [0x39, d0, d8, dS, 0, d1, d9, dt, 0, d2, do, dd, 0, d3, dm, 0, 0, d4, dm, dS, 0, d5, dm, dt, 0, d6, dm, dd, 0, d7, dm, 0, 0]
        # dev.write(0x1, arr)
        digits = FCU.digitsOfCode(-1, 123, digits)
        digits = FCU.digitsOfCode(-2, 234, digits)
        digits = FCU.digitsOfCode(-3, 34567, digits)
        digits = FCU.digitsOfCode(-4, 45678, digits)
        digits = FCU.digitsOfCode(-5, 5678, digits)
        digits = FCU.digitsOfCode(-6, 6789, digits)

        dev.write(0x1, str(bytearray(digits)))
        out = FCU.outputsOfCode(int(input('Entrer une valeur : ')))
        val = int(input('Entre 1 ou 0: '))

        for i in range(len(out)):
            byte = 2 ** out[i][2]
            if val == 1:
                if out[i][1] == 0:
                    outs[out[i][0]][2] |= byte
                else:
                    outs[out[i][0]][3] |= byte
            else:
                byte = ~byte
                if out[i][1] == 0:
                    outs[out[i][0]][2] &= byte
                else:
                    outs[out[i][0]][3] &= byte

            dev.write(0x1, outs[out[i][0]])

        data = dev.read(0x81, 64, 1)
        print(text_reponse)

    except usb.core.USBError as e:
        if e.args == ('Operation timed out',):
            pass
    except ValueError:
        print("Not a number")
