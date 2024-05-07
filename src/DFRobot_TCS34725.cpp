/*!
 * @file  DFRobot_TCS34725.cpp
 * @brief A library of color sensors
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-16
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#include "DFRobot_TCS34725.h"

DFRobot_TCS34725::DFRobot_TCS34725(TwoWire *pWire, uint8_t I2C_addr, eIntegrationTime_t it, eGain_t gain)\
:DFRobot_TCS34(pWire,I2C_addr,it,gain){}

int8_t DFRobot_TCS34725::begin(void)
{
  if(!DFRobot_TCS34::begin(TCS34725)){
    return RET_ERROR;
  }
  return RET_OK;
}

void DFRobot_TCS34725::getRGBC (uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  *c = DFRobot_TCS34::readRegword(TCS34_CDATAL);
  *r = DFRobot_TCS34::readRegword(TCS34_RDATAL);
  *g = DFRobot_TCS34::readRegword(TCS34_GDATAL);
  *b = DFRobot_TCS34::readRegword(TCS34_BDATAL);

  switch (_tcs34IntegrationTime)
  {
    case TCS34725_INTEGRATIONTIME_2_4MS:
      delay(3);
    break;
    case TCS34725_INTEGRATIONTIME_24MS:
      delay(24);
    break;
    case TCS34725_INTEGRATIONTIME_50MS:
      delay(50);
    break;
    case TCS34725_INTEGRATIONTIME_101MS:
      delay(101);
    break;
    case TCS34725_INTEGRATIONTIME_154MS:
      delay(154);
    break;
    case TCS34725_INTEGRATIONTIME_700MS:
        delay(700);
    break;
    default:
    break;
  }
}