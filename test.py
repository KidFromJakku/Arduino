# -*- coding: utf-8 -*-
"""
Created on Tue Dec 27 20:15:34 2016

@author: baren
"""

import serial as sr
import math as m
from matplotlib import pyplot
ser = sr.Serial('COM3', 9600)

i = 0
pyplot.figure(1)


while True:
    if (ser.inWaiting() > 0):
        rawData = str(ser.readline())
        VRes = int(rawData[2:5])*0.0049

        R2 = 12E3/(5/VRes-1)
        B = 3944
        A = 10E3*m.exp(-B/298)

        Temp = B / (m.log(R2/A))
        
        pyplot.scatter(i, Temp)
        pyplot.pause(0.1)
        # pyplot.ylim(200,400)
        print(i, Temp)
        i += 1
        