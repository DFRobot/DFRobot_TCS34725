/*!
 * @file  DFRobot_TCS34.h
 * @brief A library of color sensors
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-16
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#ifndef _DFRobot_TCS34_H_
#define _DFRobot_TCS34_H_
#ifdef __AVR
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#endif
#include <stdlib.h>
#include <math.h>
#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <Wire.h>
#include "DFRobot_TCS34Publics.h"





#define TCS34_COMMAND_BIT      (0x80)
#define TCS34_ENABLE           (0x00)
#define TCS34_ENABLE_AIEN      (0x10)    ///< RGBC Interrupt Enable 
#define TCS34_ENABLE_WEN       (0x08)    ///< Wait enable - Writing 1 activates the wait timer 
#define TCS34_ENABLE_AEN       (0x02)    ///< RGBC Enable - Writing 1 actives the ADC, 0 disables it 
#define TCS34_ENABLE_PON       (0x01)    ///< Power on - Writing 1 activates the internal oscillator, 0 disables it 
#define TCS34_ATIME            (0x01)    ///< Integration time 
#define TCS34_WTIME            (0x03)    ///< Wait time (if TCS34725_ENABLE_WEN is asserted) 
#define TCS34_WTIME_2_4MS      (0xFF)    ///< WLONG0 = 2.4ms   WLONG1 = 0.029s 
#define TCS34_WTIME_204MS      (0xAB)    ///< WLONG0 = 204ms   WLONG1 = 2.45s  
#define TCS34_WTIME_614MS      (0x00)    ///< WLONG0 = 614ms   WLONG1 = 7.4s   
#define TCS34_AILTL            (0x04)    ///< Clear channel lower interrupt threshold 
#define TCS34_AILTH            (0x05)
#define TCS34_AIHTL            (0x06)    ///< Clear channel upper interrupt threshold 
#define TCS34_AIHTH            (0x07)
#define TCS34_PERS             (0x0C)    ///< Persistence register - basic SW filtering mechanism for interrupts 
#define TCS34_PERS_NONE        (0b0000)  ///< Every RGBC cycle generates an interrupt                                
#define TCS34_PERS_1_CYCLE     (0b0001)  ///< 1 clean channel value outside threshold range generates an interrupt   
#define TCS34_PERS_2_CYCLE     (0b0010)  ///< 2 clean channel values outside threshold range generates an interrupt  
#define TCS34_PERS_3_CYCLE     (0b0011)  ///< 3 clean channel values outside threshold range generates an interrupt  
#define TCS34_PERS_5_CYCLE     (0b0100)  ///< 5 clean channel values outside threshold range generates an interrupt  
#define TCS34_PERS_10_CYCLE    (0b0101)  ///< 10 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_15_CYCLE    (0b0110)  ///< 15 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_20_CYCLE    (0b0111)  ///< 20 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_25_CYCLE    (0b1000)  ///< 25 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_30_CYCLE    (0b1001)  ///< 30 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_35_CYCLE    (0b1010)  ///< 35 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_40_CYCLE    (0b1011)  ///< 40 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_45_CYCLE    (0b1100)  ///< 45 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_50_CYCLE    (0b1101)  ///< 50 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_55_CYCLE    (0b1110)  ///< 55 clean channel values outside threshold range generates an interrupt 
#define TCS34_PERS_60_CYCLE    (0b1111)  ///< 60 clean channel values outside threshold range generates an interrupt 
#define TCS34_CONFIG           (0x0D)
#define TCS34_CONFIG_WLONG     (0x02)    ///< Choose between short and long (12x) wait times via TCS34725_WTIME 
#define TCS34_CONTROL          (0x0F)    ///< Set the gain level for the sensor 
#define TCS34_ID               (0x12)    ///< 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727  0x90 = TCS34001/TCS34005  0x93 = TCS34003/TCS34007
#define TCS34_STATUS           (0x13)
#define TCS34_STATUS_AINT      (0x10)    ///< RGBC Clean channel interrupt 
#define TCS34_STATUS_AVALID    (0x01)    ///< Indicates that the RGBC channels have completed an integration cycle 
#define TCS34_CDATAL           (0x14)    ///< Clear channel data 
#define TCS34_CDATAH           (0x15)
#define TCS34_RDATAL           (0x16)    ///< Red channel data 
#define TCS34_RDATAH           (0x17)
#define TCS34_GDATAL           (0x18)    ///< Green channel data 
#define TCS34_GDATAH           (0x19)
#define TCS34_BDATAL           (0x1A)    ///< Blue channel data 
#define TCS34_BDATAH           (0x1B)


class DFRobot_TCS34
{
public:	
	/**
	 * @fn DFRobot_TCS34
	 * @brief Constructor of the TCS34 Series Parent Class
	 * @param pWire
	 * @param I2C_addr
	 * @param it 
	 * @param gain 
	*/
	DFRobot_TCS34(TwoWire *pWire, uint8_t I2C_addr, eIntegrationTime_t it, eGain_t gain);

	/**
	 * @fn begin
	 * @brief Initializes I2C and configures the sensor (call this function beforedoing anything else).
	 * @param sensor Select sensor
	 * @return boolean
	 * @retval true success
	 * @retval false fail
	 */
	boolean begin(uint8_t sensor);

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
	 * @fn disable
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
	 * @brief Set the Generate interrupts object
	 */
	void setGenerateinterrupts(void);
protected:
	eGain_t _tcs34Gain;
	eIntegrationTime_t _tcs34IntegrationTime;
private:
	void writeReg(uint8_t Reg, void *Data, uint8_t len);
	int16_t readReg(uint8_t Reg, uint8_t *Data, uint8_t len);
	
	TwoWire *_pWire;
	uint8_t _I2C_addr;
	
};
#endif
