#!/usr/bin/python
#-*-coding:latin_1-*-

idVendor = 0x04d8
idProduct = 0x0071

#Code attendu par le PC
outputs = list(range(255, 326))
outputs.append(568)#ATCCOMM

#Données reçues par le module : [groupe, byte1]
inputs = []
inputs.append([5,4]) #A
inputs.append([5,5]) #B
inputs.append([5,6]) #C
inputs.append([5,7]) #D
inputs.append([5,8]) #E
inputs.append([4,4]) #F
inputs.append([4,5]) #G
inputs.append([4,6]) #H
inputs.append([4,7]) #I
inputs.append([4,8]) #J
inputs.append([3,4]) #K
inputs.append([3,5]) #L
inputs.append([3,6]) #M
inputs.append([3,7]) #N
inputs.append([3,8]) #O
inputs.append([2,4]) #P
inputs.append([2,5]) #Q
inputs.append([2,6]) #R
inputs.append([2,7]) #S
inputs.append([2,8]) #T
inputs.append([1,4]) #U
inputs.append([1,5]) #V
inputs.append([1,6]) #W
inputs.append([1,7]) #X
inputs.append([1,8]) #Y
inputs.append([0,4]) #Z
inputs.append([0,2]) #0
inputs.append([3,1]) #1
inputs.append([3,2]) #2
inputs.append([3,3]) #3
inputs.append([2,1]) #4
inputs.append([2,2]) #5
inputs.append([2,3]) #6
inputs.append([1,1]) #7
inputs.append([1,2]) #8
inputs.append([1,3]) #9
inputs.append([8,4]) #LSK1
inputs.append([8,3]) #LSK2
inputs.append([7,3]) #LSK3
inputs.append([6,3]) #LSK4
inputs.append([5,3]) #LSK5
inputs.append([4,3]) #LSK6
inputs.append([7,6]) #RSK1
inputs.append([6,6]) #RKS2
inputs.append([7,7]) #RSK3
inputs.append([6,7]) #RSK4
inputs.append([7,8]) #RSK5
inputs.append([6,8]) #RSK6
inputs.append([0,8]) #CLR
inputs.append([0,7]) #OVFY
inputs.append([8,2]) #DIR
inputs.append([8,1]) #PROG
inputs.append([8,7]) #PERF
inputs.append([8,8]) #INIT
inputs.append([7,2]) #FPLN
inputs.append([7,1]) #RADNAV
inputs.append([5,1]) #Larrow
inputs.append([4,1]) #Rarrow
inputs.append([5,2]) #Uarrow
inputs.append([4,2]) #Darrow
inputs.append([0,6]) #SP
inputs.append([0,5]) #Slash
inputs.append([0,3]) #plus
inputs.append([0,1]) #point
inputs.append([8,5]) #SECFPLN
inputs.append([6,5]) #MCDUMENU
inputs.append([9,2]) #BRT
inputs.append([9,1]) #DIM
inputs.append([7,4]) #DATA
inputs.append([8,6]) #FUELPRED
inputs.append([6,1]) #AIRPORT
inputs.append([6,4]) #ATCCOMM

def codeOf(a):
    if inputs.count(a) > 0:
        return outputs[inputs.index(a)]
    return 0

def charOf(a):
    if inputs.count(a) > 0:
        return char[inputs.index(a)]
    return None

