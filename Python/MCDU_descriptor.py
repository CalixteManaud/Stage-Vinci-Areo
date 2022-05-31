#!/usr/bin/python
# -*-coding:latin_1-*-

idVendor = 0x04d8
idProduct = 0x0071

# Code attendu par le PC
outputs = list(range(255, 326))
outputs.append(568)  # ATCCOMM

# Données reçues par le module : [groupe, byte1]
inputs = [[5, 4], [5, 5], [5, 6], [5, 7], [5, 8], [4, 4], [4, 5], [4, 6], [4, 7], [4, 8], [3, 4], [3, 5], [3, 6],
          [3, 7], [3, 8], [2, 4], [2, 5], [2, 6], [2, 7], [2, 8], [1, 4], [1, 5], [1, 6], [1, 7], [1, 8], [0, 4],
          [0, 2], [3, 1], [3, 2], [3, 3], [2, 1], [2, 2], [2, 3], [1, 1], [1, 2], [1, 3], [8, 4], [8, 3], [7, 3],
          [6, 3], [5, 3], [4, 3], [7, 6], [6, 6], [7, 7], [6, 7], [7, 8], [6, 8], [0, 8], [0, 7], [8, 2], [8, 1],
          [8, 7], [8, 8], [7, 2], [7, 1], [5, 1], [4, 1], [5, 2], [4, 2], [0, 6], [0, 5], [0, 3], [0, 1], [8, 5],
          [6, 5], [9, 2], [9, 1], [7, 4], [8, 6], [6, 1], [6, 4]]


def codeOf(a):
    if inputs.count(a) > 0:
        return outputs[inputs.index(a)]
    return 0


def charOf(a):
    if inputs.count(a) > 0:
        return char[inputs.index(a)]
    return None
