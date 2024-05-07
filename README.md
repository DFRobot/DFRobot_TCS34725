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

To use this library download the zip file, uncompress it to a folder named DFRobot_TCS34725.
Download the zip file first to use this library and uncompress it to a folder named DFRobot_TCS34725.

## Methods

```C++
	/**
	 * @fn begin
	 * @brief Initializes I2C and configures the sensor (call this function beforedoing anything else).
	 * @return boolean
	 * @retval true success
	 * @retval false fail
	 */
	boolean begin(void);

	/**
	 * @fn setIntegrationtime
	 * @brief Sets the integration time for the TC34725.
	 * @param it  integration time.
	 */
	void setIntegrationtime(eIntegrationTime_t it);

	/**
	 * @fn setGain
	 * @brief Adjusts the gain on the TCS34725 (adjusts the sensitivity to light)
	 * @param gain  gain time.
	 */
	void setGain(eGain_t gain);

	/**
	 * @fn getRGBC
	 * @brief Reads the raw red, green, blue and clear channel values
	 * @param r  red.
	 * @param g  green.
	 * @param b  blue.
	 * @param c  color temperature
	 */
	void getRGBC(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);

	/**
	 * @fn calculateColortemperature
	 * @brief Converts the raw R/G/B values to color temperature in degrees
	 * @param r  red.
	 * @param g  green.
	 * @param b  blue.
	 * @return uint16_t color temperature
	 */
	uint16_t calculateColortemperature(uint16_t r, uint16_t g, uint16_t b);

	/**
	 * @fn calculateLux
	 * @brief Converts the raw R/G/B values to lux
	 * @param r  red.
	 * @param g  green.
	 * @param b  blue.
	 * @return  uint16_t lux.
	 */
	uint16_t calculateLux(uint16_t r, uint16_t g, uint16_t b);

	/**
	 * @fn lock
	 * @brief Interrupts enabled
	 */
	void lock(void);

	/**
	 * @fn unlock
	 * @brief Interrupts disabled
	 */
	void unlock(void);

	/**
	 * @fn clear
	 * @brief clear Interrupts
	 */
	void clear(void);

	/**
	 * @fn setIntLimits
	 * @brief set Int Limits
	 * @param l low .
	 * @param h high .
	 */
	void setIntLimits(uint16_t l, uint16_t h);

	/**
	 * @fn enable
	 * @brief Enables the device
	 */
	void enable(void);

	/**
	 * @fn enable
	 * @brief disenables the device
	 */
	void disable(void);

	/**
	 * @fn readRegword
	 * @brief read reg word
	 * @param reg
	 * @return uint16_t
	 */
	uint16_t readRegword(uint8_t reg);

	/**
	 * @fn setGenerateinterrupts
	 * @brief Set the Generateinterrupts object
	 */
	void setGenerateinterrupts(void);

```

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266|      √       |              |             | 
Mega2560  |      √       |             |            | 
Arduino uno |       √      |             |            | 
Leonardo  |      √       |              |             | 
Micro：bit  |      √       |              |             | 
M0  |      √       |              |             | 

## History

- 2022/3/16 - V1.0.0
- 2024/4/24 - V1.0.1

## Credits

Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))