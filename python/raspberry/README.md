# DFRobot_TCS

- [中文版](./README_CN.md)

TCS34725 is a low-cost, cost-effective RGB full-color color recognition sensor. The sensor uses optical induction to identify the surface color of an object.  Support red, green, blue (RGB) three basic colors, support bright light sensor, can output the corresponding specific value, to help you restore the true color.  In order to improve the accuracy and prevent the interference of the surrounding environment, we specially added an infrared visor at the bottom of the sensor to minimize the infrared spectrum component of the incident light and make the color management more accurate.  Onboard comes with four high-light LED, which enables the sensor to work normally even in low ambient light, realizing the function of "light filling".  The module adopts I2C communication, with PH2.0 and XH2.54 (breadboard) two interfaces, users can choose interfaces according to their own needs, more convenient.  
![正反面svg效果图](./resources/images/SEN0212.png)

## Product Link(https://www.dfrobot.com/product-1546.html)

SKU：SEN0212

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

A library of color sensors

## Installation

Download the DFRobot_LIS file to the Raspberry Pi file directory, then run the following command line to use this sensor:
```
cd DFRobot_LIS/python/raspberry/examples/TCS3400
python colorview.py
```

## Methods

```python
	def begin(self):
    '''!
      @fn begin
      @brief Initialize the sensor
      @return Initialization status
    '''
    
  def set_integration_time(self,it):
    '''!
      @fn set_integration_time
	    @brief Sets the integration time for the TC34725.
	    @param it  integration time.
    '''
    
  def set_gain(self,gain):
    '''!
      @fn set_gain
	    @brief Adjusts the gain on the TCS34725 (adjusts the sensitivity tolight)
	    @param gain  gain time.
    '''

  def calculate_colortemperature(self,r,g,b):
    '''!
      @fn calculate_colortemperature
	    @brief Converts the raw R/G/B values to color temperature in degrees
	    @param r  red.
	    @param g  green.
	    @param b  blue.
	    @return uint16_t color temperature
    '''

  def calculate_lux(self,r,g,b):
    '''!
      @fn calculateLux
	    @brief Converts the raw R/G/B values to lux
	    @param r  red.
	    @param g  green.
	    @param b  blue.
	    @return  uint16_t lux.
    '''
  
  def lock(self):
    '''!
      @fn lock
	    @brief Interrupts enabled
    '''
  
  def unlock(self):
    '''!
      @fn unlock
	    @brief Interrupts disabled
    '''
  
  def clear(self):
      '''!
        @fn clear
	      @brief clear Interrupts
      '''
  
  def set_int_limits(self,low,high):
      '''!
        @fn set_int_limits
	      @brief set Int Limits
	      @param l low .
	      @param h high .
      '''

  def set_generateinterrupts(self):
    '''!
      @fn setGenerateinterrupts
	    @brief Set the Generate interrupts object
    '''

```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Raspberry Pi              |      √         |            |             | 

## History

- 2022/3/16 - V1.0.0
- 2024/4/24 - V1.0.1

## Credits

Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))