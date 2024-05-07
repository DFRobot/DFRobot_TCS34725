/*!
 * @file  DFRobot_TCS34725.h
 * @brief A library of color sensors
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-16
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#ifndef _DFROBOT_TCS34725_H_
#define _DFROBOT_TCS34725_H_
#include "Arduino.h"
#include "DFRobot_TCS34.h"
#include "DFRobot_TCS34Publics.h"

#define TCS34725_ADDRESS    (0x29) ///< TCS3400 device addr

#define RET_OK 0
#define RET_ERROR -1

class DFRobot_TCS34725:public DFRobot_TCS34
{
public:
  DFRobot_TCS34725(TwoWire *pWire=&Wire, uint8_t I2C_addr = TCS34725_ADDRESS, eIntegrationTime_t it= TCS34725_INTEGRATIONTIME_2_4MS, eGain_t gain= TCS34725_GAIN_1X);
  /**
   * @fn begin
   * @brief Initialize the sensor
   * @return Initialization status
   * @retval RET_OK Initialization successful
   * @retval RET_ERROR Initialization failed
  */
  int8_t begin(void);

  /**
	 * @fn getRGBC
	 * @brief Reads the raw red, green, blue and clear channel values
	 * @param r  red.
	 * @param g  green.
	 * @param b  blue.
	 * @param c  color temperature
	 */
	void getRGBC(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);

};

#endif
