# -*- coding: utf-8 -*

from __future__ import print_function
import sys
import os
sys.path.append("../../")
import time
from DFRobot_TCS3400 import *



tcs = DFRobot_TCS3400(1,TCS3400_ADDR,TCS3400_INTEGRATIONTIME_27_8MS,TCS3400_GAIN_1X)

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