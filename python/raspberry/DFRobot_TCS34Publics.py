# -*- coding: utf-8 -*
'''!
@file  DFRobot_TCS34Publics.py
@brief General document
@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
@license     The MIT License (MIT)
@author      TangJie(jie.tang@dfrobot.com)
@version     V1.0.0
@date        2024-04-24
@url         https://github.com/DFRobot/DFRobot_TCS

'''

TCS34725          =      0 
TCS3400           =      1
TCS34_001_005     =      0X90
TCS34_003_007     =      0X93
TCS34_721_725     =      0X44
TCS34_723_727     =      0X4d

#TCS34725
TCS34725_INTEGRATIONTIME_2_4MS  = 0xFF
TCS34725_INTEGRATIONTIME_24MS   = 0xF6
TCS34725_INTEGRATIONTIME_50MS   = 0xEB
TCS34725_INTEGRATIONTIME_101MS  = 0xD5
TCS34725_INTEGRATIONTIME_154MS  = 0xC0
TCS34725_INTEGRATIONTIME_700MS  = 0x00
#TCS3400
TCS3400_INTEGRATIONTIME_2_78MS  = 0xFF
TCS3400_INTEGRATIONTIME_27_8MS  = 0xF6
TCS3400_INTEGRATIONTIME_103MS   = 0xDB
TCS3400_INTEGRATIONTIME_178MS   = 0xC0
TCS3400_INTEGRATIONTIME_712MS   = 0x00

#TCS34725
TCS34725_GAIN_1X                = 0x00    #1x gain  
TCS34725_GAIN_4X                = 0x01    #4x gain  
TCS34725_GAIN_16X               = 0x02    #16x gain 
TCS34725_GAIN_60X               = 0x03    #60x gain 
#TCS
TCS3400_GAIN_1X                  = 0x00    #1x gain  
TCS3400_GAIN_4X                 = 0x01    #4x gain  
TCS3400_GAIN_16X                = 0x02    #16x gain 
TCS3400_GAIN_64X                = 0x03    #64x gain 