#!/usr/bin/python
# -*-coding:latin_1-*-

idVendor = 0x04d8
idProduct = 0x0050
nbGroupes = 5

# Code attendu par le PC
codeIN = list(range(149, 230))
codeIN.append(378)
codeIN.append(379)

# Données reçues par le module : [groupe, byte1, byte2]
inputs = [[1, 1, 4], [1, 1, 3], [1, 1, 0], [0, 1, 5], [0, 1, 7], [0, 1, 6], [0, 1, 4], [0, 1, 2], [0, 0, 7], [0, 0, 6],
          [0, 0, 5], [0, 1, 1], [0, 1, 0], [1, 1, 2], [1, 1, 1], [2, 0, 7], [2, 0, 6], [1, 0, 5], [1, 0, 4], [0, 0, 0],
          [0, 0, 1], [0, 0, 2], [0, 0, 3], [0, 0, 4], [1, 1, 5], [1, 1, 6], [1, 0, 7], [1, 1, 7], [5, 1, 4], [5, 1, 5],
          [4, 1, 1], [4, 0, 7], [4, 0, 6], [4, 0, 5], [4, 1, 0], [4, 1, 2], [4, 1, 5], [4, 1, 7], [4, 1, 6], [4, 1, 4],
          [4, 1, 3], [3, 0, 2], [3, 0, 3], [5, 0, 1], [5, 0, 2], [5, 0, 5], [5, 0, 4], [4, 0, 4], [4, 0, 3], [4, 0, 2],
          [4, 0, 1], [4, 0, 0], [5, 1, 2], [5, 1, 3], [5, 0, 7], [5, 1, 1], [2, 0, 1], [3, 1, 1], [2, 0, 4], [2, 0, 5],
          [2, 0, 2], [2, 0, 3], [3, 0, 0], [3, 0, 1], [2, 1, 2], [2, 1, 3], [2, 1, 6], [2, 1, 7], [3, 1, 6], [3, 1, 7],
          [3, 0, 7], [3, 0, 6], [3, 1, 3], [2, 1, 0], [2, 1, 4], [3, 1, 4], [3, 0, 4], [2, 1, 1], [2, 1, 5], [3, 1, 5],
          [3, 0, 5], [3, 1, 2], [2, 0, 0]]

# inputs.append([groupe, byte, bit])


def codeOfInput(i):
    if inputs.count(i) > 0:
        return codeIN[inputs.index(i)]
    return 0


def inputOfCode(c):
    if codeIN.count(c) > 0:
        return inputs[codeIN.index(c)]
    return None


# Code envoyé par le PC
codeOUT = list(range(300, 313))
codeOUT.append(314)
codeOUT += list(range(322, 341))

# Données envoyées par le module : [nbData, groupe, byte1, bit]
outputs = []
outputs2 = []

# outputs.append([nbData, index])
outputs.append([1, 0])  # CPT_FD
outputs.append([1, 1])  # CPT_LS
outputs.append([1, 2])  # CPT_CSTR
outputs.append([1, 3])  # CPT_WPT
outputs.append([1, 4])  # CPT_VOR
outputs.append([1, 5])  # CPT_NDB
outputs.append([1, 6])  # CPT_ARPT
outputs.append([2, 7])  # CPT_QFE
outputs.append([2, 9])  # CPT_QNH
outputs.append([2, 11])  # SPD
outputs.append([2, 13])  # MACH
outputs.append([8, 15])  # HDGVS
outputs.append([8, 23])  # TRKFPA
outputs.append([1, 31])  # HDGDOT
outputs.append([1, 32])  # ALTDOT
outputs.append([1, 33])  # SPDDOT
outputs.append([1, 34])  # AP1
outputs.append([1, 35])  # AP2
outputs.append([1, 36])  # ATHR
outputs.append([1, 37])  # LOC
outputs.append([1, 38])  # APPR
outputs.append([1, 39])  # EXPED
outputs.append([1, 40])  # CPT_FD
outputs.append([1, 41])  # CPT_LS
outputs.append([1, 42])  # CPT_CSTR
outputs.append([1, 43])  # CPT_WPT
outputs.append([1, 44])  # CPT_VOR
outputs.append([1, 45])  # CPT_NDB
outputs.append([1, 46])  # CPT_ARPT
outputs.append([2, 47])  # CPT_QFE
outputs.append([2, 49])  # CPT_QNH

# outputs2.append([groupe, byte, bit])
outputs2.append([3, 0, 0])  # CPT_FD
outputs2.append([3, 0, 1])  # CPT_LS
outputs2.append([3, 0, 4])  # CPT_CSTR
outputs2.append([3, 0, 2])  # CPT_WPT
outputs2.append([3, 0, 3])  # CPT_VOR
outputs2.append([3, 0, 6])  # CPT_NDB
outputs2.append([3, 0, 5])  # CPT_ARPT
outputs2.append([3, 1, 0])  # CPT_QFE
outputs2.append([3, 1, 1])  # CPT_QFE
outputs2.append([3, 1, 5])  # CPT_QNH
outputs2.append([3, 1, 6])  # CPT_QNH
outputs2.append([0, 0, 2])  # SPD
outputs2.append([0, 0, 3])  # SPD
outputs2.append([0, 0, 5])  # MACH
outputs2.append([0, 0, 6])  # MACH
outputs2.append([0, 0, 0])  # HDGVS
outputs2.append([0, 0, 1])  # HDGVS
outputs2.append([0, 1, 0])  # HDGVS
outputs2.append([0, 1, 1])  # HDGVS
outputs2.append([1, 1, 1])  # HDGVS
outputs2.append([1, 1, 6])  # HDGVS
outputs2.append([2, 0, 2])  # HDGVS
outputs2.append([2, 0, 4])  # HDGVS
outputs2.append([0, 1, 5])  # TRKFPA
outputs2.append([0, 1, 6])  # TRKFPA
outputs2.append([1, 1, 2])  # TRKFPA
outputs2.append([1, 1, 3])  # TRKFPA
outputs2.append([1, 1, 4])  # TRKFPA
outputs2.append([1, 1, 5])  # TRKFPA
outputs2.append([2, 0, 0])  # TRKFPA
outputs2.append([2, 0, 5])  # TRKFPA
outputs2.append([0, 1, 2])  # HDGDOT
outputs2.append([2, 1, 1])  # ALTDOT
outputs2.append([0, 0, 4])  # SPDDOT
outputs2.append([1, 0, 6])  # AP1
outputs2.append([1, 0, 4])  # AP2
outputs2.append([1, 0, 3])  # ATHR
outputs2.append([1, 0, 5])  # LOC
outputs2.append([1, 0, 1])  # APPR
outputs2.append([1, 0, 2])  # EXPED
outputs2.append([4, 1, 0])  # FO_FD
outputs2.append([4, 1, 1])  # FO_LS
outputs2.append([4, 1, 4])  # FO_CSTR
outputs2.append([4, 1, 6])  # FO_WPT
outputs2.append([4, 1, 3])  # FO_VOR
outputs2.append([4, 1, 2])  # FO_NDB
outputs2.append([4, 1, 5])  # FO_ARPT
outputs2.append([5, 1, 0])  # FO_QFE
outputs2.append([5, 1, 6])  # FO_QFE
outputs2.append([5, 1, 1])  # FO_QNH
outputs2.append([5, 1, 5])  # FO_QNH


def codeOfOutput(o):
    if outputs2.count(o) > 0:
        for i in range(len(outputs) - 1):
            if outputs2.index(o) >= outputs[i][1] and outputs2.index(o) < outputs[i + 1][1]:
                return codeOUT[i]
        return codeOUT[len(outputs) - 1]
    return 0


def outputsOfCode(c):
    if codeOUT.count(c) > 0:
        r = []
        o = outputs[codeOUT.index(c)]
        for i in range(o[0]):
            r.append(outputs2[i + o[1]])
        return r
    return None


# Index pour le registre des digits
digitsIndex = [1, 5, 9, 13, 17, 21, 25, 29, 2, 6, 10, 14, 18, 22, 26, 30, 3, 7, 11, 15, 19, 23, 27, 31, 4, 8, 12, 16,
               20, 24, 28, 32]

# Valeur héxadécimale de l'afficheur 7 segments pour un digit
digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'S', 't', 'd', 'o', 'm']
digitsHex = [0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x5B, 0x0F, 0x3D, 0x1D, 0x01]


def digitsOfCode(id, value, register):
    if id < -6 or id > -1:
        return None
    if id == -1:
        str = "%03d" % value
        register[digitsIndex[0]] = digitsHex[digits.index(str[-3])]
        register[digitsIndex[1]] = digitsHex[digits.index(str[-2])]
        register[digitsIndex[2]] = digitsHex[digits.index(str[-1])]
    if id == -2:
        str = "%03d" % value
        register[digitsIndex[3]] = digitsHex[digits.index(str[-3])]
        register[digitsIndex[4]] = digitsHex[digits.index(str[-2])]
        register[digitsIndex[5]] = digitsHex[digits.index(str[-1])]
    if id == -3:
        str = "%05d" % value
        register[digitsIndex[6]] = digitsHex[digits.index(str[-5])]
        register[digitsIndex[7]] = digitsHex[digits.index(str[-4])]
        register[digitsIndex[8]] = digitsHex[digits.index(str[-3])]
        register[digitsIndex[9]] = digitsHex[digits.index(str[-2])]
        register[digitsIndex[10]] = digitsHex[digits.index(str[-1])]
    if id == -4:
        str = "%05d" % value
        register[digitsIndex[11]] = digitsHex[digits.index(str[-5])]
        register[digitsIndex[12]] = digitsHex[digits.index(str[-4])]
        register[digitsIndex[13]] = digitsHex[digits.index(str[-3])]
        register[digitsIndex[14]] = digitsHex[digits.index(str[-2])]
        register[digitsIndex[15]] = digitsHex[digits.index(str[-1])]
    if id == -5:
        str = "%04d" % value
        register[digitsIndex[16]] = digitsHex[digits.index(str[-4])]
        register[digitsIndex[17]] = digitsHex[digits.index(str[-3])]
        register[digitsIndex[18]] = digitsHex[digits.index(str[-2])]
        register[digitsIndex[19]] = digitsHex[digits.index(str[-1])]
    if id == -6:
        str = "%04d" % value
        register[digitsIndex[20]] = digitsHex[digits.index(str[-4])]
        register[digitsIndex[21]] = digitsHex[digits.index(str[-3])]
        register[digitsIndex[22]] = digitsHex[digits.index(str[-2])]
        register[digitsIndex[23]] = digitsHex[digits.index(str[-1])]
    return register
