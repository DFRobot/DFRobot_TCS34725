# -*- coding: utf-8 -*

from __future__ import print_function
import sys
import os
sys.path.append("../../")
import time
from DFRobot_TCS34725 import *



tcs = DFRobot_TCS34725(1,TCS34725_ADDRESS,TCS34725_INTEGRATIONTIME_24MS,TCS34725_GAIN_1X)

def setup():
  while (tcs.begin() != 0):
    print("No TCS3400 found ... check your connections")
    time.sleep(1)
  
def loop():
  red,green,blue,clear = tcs.get_rgbc()
  tcs.lock()
  print("R: ",red,"G: ",green,"B: ",blue,"C: ",clear,"\n")

  

if __name__ == "__main__":
  setup()
  while True:
    loop()