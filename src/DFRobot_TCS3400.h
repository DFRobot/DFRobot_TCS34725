/*!
 * @file  DFRobot_TCS3400.h
 * @brief A library of color sensors
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      TangJie(jie.tang@dfrobot.com)
 * @version     V1.0.0
 * @date        2024-04-24
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#ifndef _DFROBOT_TCS3400_H_
#define _DFROBOT_TCS3400_H_

#include "Arduino.h"
#include "DFRobot_TCS34.h"
#include "DFRobot_TCS34Publics.h"

#define TCS3400_ADDR 0X39 ///< TCS3400 device addr

#define RET_OK 0
#define RET_ERROR -1

class DFRobot_TCS3400:public DFRobot_TCS34
{
public:
  /**
   * @fn DFRobot_TCS3400
   * @brief Constructor for TCS3400
   * @param pWire I2C object
   * @param it Data acquisition waiting time
   * @param gain Data gain
  */
  DFRobot_TCS3400(TwoWire *pWire=&Wire, uint8_t I2C_addr = TCS3400_ADDR, eIntegrationTime_t it= TCS3400_INTEGRATIONTIME_2_78MS, eGain_t gain= TCS3400_GAIN_1X);
  
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
