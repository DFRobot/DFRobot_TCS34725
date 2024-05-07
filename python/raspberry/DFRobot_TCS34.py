# -*- coding: utf-8 -*
'''!
    @file  DFRobot_TCS34.py
    @brief A library of color sensors
    @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
    @license     The MIT License (MIT)
    @author      TangJie(jie.tang@dfrobot.com)
    @version     V1.0.0
    @date        2024-04-26
    @url         https://github.com/DFRobot/DFRobot_TCS

'''

import smbus
import time
from DFRobot_TCS34Publics import *

class DFRobot_TCS34(object):
  
    TCS34_COMMAND_BIT      =(0x80)
    TCS34_ENABLE           =(0x00)
    TCS34_ENABLE_AIEN      =(0x10)    #RGBC Interrupt Enable 
    TCS34_ENABLE_WEN       =(0x08)    #Wait enable - Writing 1 activates the wait timer 
    TCS34_ENABLE_AEN       =(0x02)    #RGBC Enable - Writing 1 actives the ADC, 0 disables it 
    TCS34_ENABLE_PON       =(0x01)    #Power on - Writing 1 activates the internal oscillator, 0 disables it 
    TCS34_ATIME            =(0x01)    #Integration time 
    TCS34_WTIME            =(0x03)    #Wait time (if TCS34725_ENABLE_WEN is asserted) 
    TCS34_WTIME_2_4MS      =(0xFF)    #WLONG0 = 2.4ms   WLONG1 = 0.029s 
    TCS34_WTIME_204MS      =(0xAB)    #WLONG0 = 204ms   WLONG1 = 2.45s  
    TCS34_WTIME_614MS      =(0x00)    #WLONG0 = 614ms   WLONG1 = 7.4s   
    TCS34_AILTL            =(0x04)    #Clear channel lower interrupt threshold 
    TCS34_AILTH            =(0x05)
    TCS34_AIHTL            =(0x06)    #Clear channel upper interrupt threshold 
    TCS34_AIHTH            =(0x07)
    TCS34_PERS             =(0x0C)    #Persistence register - basic SW filtering mechanism for interrupts 
    TCS34_PERS_NONE        =(0b0000)  #Every RGBC cycle generates an interrupt                                
    TCS34_PERS_1_CYCLE     =(0b0001)  #1 clean channel value outside threshold range generates an interrupt   
    TCS34_PERS_2_CYCLE     =(0b0010)  #2 clean channel values outside threshold range generates an interrupt  
    TCS34_PERS_3_CYCLE     =(0b0011)  #3 clean channel values outside threshold range generates an interrupt  
    TCS34_PERS_5_CYCLE     =(0b0100)  #5 clean channel values outside threshold range generates an interrupt  
    TCS34_PERS_10_CYCLE    =(0b0101)  #10 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_15_CYCLE    =(0b0110)  #15 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_20_CYCLE    =(0b0111)  #20 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_25_CYCLE    =(0b1000)  #25 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_30_CYCLE    =(0b1001)  #30 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_35_CYCLE    =(0b1010)  #35 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_40_CYCLE    =(0b1011)  #40 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_45_CYCLE    =(0b1100)  #45 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_50_CYCLE    =(0b1101)  #50 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_55_CYCLE    =(0b1110)  #55 clean channel values outside threshold range generates an interrupt 
    TCS34_PERS_60_CYCLE    =(0b1111)  #60 clean channel values outside threshold range generates an interrupt 
    TCS34_CONFIG           =(0x0D)
    TCS34_CONFIG_WLONG     =(0x02)    #Choose between short and long (12x) wait times via TCS34725_WTIME 
    TCS34_CONTROL          =(0x0F)    #Set the gain level for the sensor 
    TCS34_ID               =(0x12)    #0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727  0x90 = TCS34001/TCS34005  0x93 = TCS34003/TCS34007
    TCS34_STATUS           =(0x13)
    TCS34_STATUS_AINT      =(0x10)    #RGBC Clean channel interrupt 
    TCS34_STATUS_AVALID    =(0x01)    #Indicates that the RGBC channels have completed an integration cycle 
    TCS34_CDATAL           =(0x14)    #Clear channel data 
    TCS34_CDATAH           =(0x15)
    TCS34_RDATAL           =(0x16)    #Red channel data 
    TCS34_RDATAH           =(0x17)
    TCS34_GDATAL           =(0x18)    #Green channel data 
    TCS34_GDATAH           =(0x19)
    TCS34_BDATAL           =(0x1A)    #Blue channel data 
    TCS34_BDATAH           =(0x1B)
  
    def __init__(self,bus = 1,addr=0,int=0,gain=0):
        self.__i2cbus = smbus.SMBus(bus)
        self.__i2c_addr = addr
        self.tcs34_gain = gain
        self.tcs34_integration_time = int
  
    def begin(self,sensor):
        '''!
          @fn begin
	        @brief Initializes I2C and configures the sensor (call this function beforedoing anything else).
	        @param sensor Select sensor
	        @return boolean
	        @retval true success
	        @retval false fail
        '''
        buf = self._read_reg(self.TCS34_ID,1)
        if sensor == TCS3400:
            if(buf[0] != TCS34_001_005) and (buf[0] != 0x10):
                return False
        else:
            if(buf[0] != TCS34_721_725) and (buf[0]!= 0x10):
                return False
        self.set_integration_time(self.tcs34_integration_time)
        self.set_gain(self.tcs34_gain)
        self.enable()
        return True
    
    def enable(self):
        '''!
          @fn enable
	        @brief Enables the device
        '''
        data = self.TCS34_ENABLE_PON
        self._write_reg(self.TCS34_ENABLE,data)
        data = self.TCS34_ENABLE_PON | self.TCS34_ENABLE_AEN
        time.sleep(0.03)
        self._write_reg(self.TCS34_ENABLE,data)
    
    def disable(self):
        '''!
          @fn disable
	        @brief disenables the device
        '''
        reg = self._read_reg(self.TCS34_ENABLE,1)
        data = reg[0] & ~(self.TCS34_ENABLE_PON| self.TCS34_ENABLE_AEN)
        self._write_reg(self.TCS34_ENABLE,data)

    def set_integration_time(self,it):
        '''!
          @fn set_integration_time
	        @brief Sets the integration time for the TC34725.
	        @param it  integration time.
        '''
        self.tcs34_integration_time = it
        self._write_reg(self.TCS34_ATIME,it)
    
    def set_gain(self,gain):
        '''!
          @fn set_gain
	        @brief Adjusts the gain on the TCS34725 (adjusts the sensitivity to light)
	        @param gain  gain time.
        '''
        self.tcs34_gain = gain
        self._write_reg(self.TCS34_CONTROL,gain)

    def calculate_colortemperature(self,r,g,b):
        '''!
          @fn calculate_colortemperature
	        @brief Converts the raw R/G/B values to color temperature in degrees
	        @param r  red.
	        @param g  green.
	        @param b  blue.
	        @return uint16_t color temperature
        '''
        X = (-0.14282 * r) + (1.54924 * g) + (-0.95641 * b)
        Y = (-0.32466 * r) + (1.57837 * g) + (-0.73191 * b)
        Z = (-0.68202 * r) + (0.77073 * g) + ( 0.56332 * b)
        xc = (X) / (X + Y + Z)
        yc = (Y) / (X + Y + Z)
        n = (xc - 0.3320) / (0.1858 - yc)
        cct = (449.0 * powf(n, 3)) + (3525.0 * powf(n, 2)) + (6823.3 * n) + 5520.33
        return cct

    def calculate_lux(self,r,g,b):
        '''!
          @fn calculateLux
	        @brief Converts the raw R/G/B values to lux
	        @param r  red.
	        @param g  green.
	        @param b  blue.
	        @return  uint16_t lux.
        '''
        illuminance = (-0.32466 * r) + (1.57837 * g) + (-0.73191 * b)
        return illuminance
    
    def lock(self):
        '''!
          @fn lock
	        @brief Interrupts enabled
        '''
        reg = self._read_reg(self.TCS34_ENABLE,1)
        data = reg[0]|self.TCS34_ENABLE_AIEN
        self._write_reg(self.TCS34_ENABLE,data)
    
    def unlock(self):
        '''!
          @fn unlock
	        @brief Interrupts disabled
        '''
        reg = self._read_reg(self.TCS34_ENABLE,1)
        data = reg[0]&(~self.TCS34_ENABLE_AIEN)
        self._write_reg(self.TCS34_ENABLE,data)
    
    def clear(self):
        '''!
          @fn clear
	        @brief clear Interrupts
        '''
        self.__i2cbus.write_byte_data(self.__i2c_addr,0xE6,0)
    
    def set_int_limits(self,low,high):
        '''!
          @fn set_int_limits
	        @brief set Int Limits
	        @param l low .
	        @param h high .
        '''
        data = low & 0xff
        self._write_reg(0x04,data)
        data = low >> 8
        self._write_reg(0x05,data)
        data = high & 0xff
        self._write_reg(0x06,data)
        data = high >> 8
        self._write_reg(0x07,data)

    def set_generateinterrupts(self):
        '''!
          @fn setGenerateinterrupts
	        @brief Set the Generate interrupts object
        '''
        data = self.TCS34_PERS_NONE
        self._write_reg(self.TCS34_PERS,data)
    
    def read_reg_word(self,reg):
        buf = self._read_reg(reg,2)
        data = buf[0] | buf[1] << 8
        return data 

    def _write_reg(self, reg, data):
        '''!
          @brief writes data to a register
          @param reg register address
          @param data written data
        '''
        self._reg = reg | self.TCS34_COMMAND_BIT
        if isinstance(data, int):
            data = [data]
            #logger.info(data)
        self.__i2cbus.write_i2c_block_data(self.__i2c_addr, self._reg, data)

    def _read_reg(self, reg, length):
        '''!
          @brief read the data from the register
          @param reg register address
          @param length read data length
        '''
        self._reg = reg | self.TCS34_COMMAND_BIT
        return self.__i2cbus.read_i2c_block_data(self.__i2c_addr, self._reg, length)