/*!
 * @file  DFRobot_TCS3400.cpp
 * @brief A library of color sensors
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      TangJie(jie.tang@dfrobot.com)
 * @version     V1.0.0
 * @date        2024-04-24
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#include "DFRobot_TCS3400.h"

DFRobot_TCS3400::DFRobot_TCS3400(TwoWire *pWire, uint8_t I2C_addr, eIntegrationTime_t it, eGain_t gain)\
:DFRobot_TCS34(pWire,I2C_addr,it,gain){}

int8_t DFRobot_TCS3400::begin(void)
{
  if(!DFRobot_TCS34::begin(TCS3400)){
    return RET_ERROR;
  }
  return RET_OK;
}

void DFRobot_TCS3400::getRGBC (uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  *c = DFRobot_TCS34::readRegword(TCS34_CDATAL);
  *r = DFRobot_TCS34::readRegword(TCS34_RDATAL);
  *g = DFRobot_TCS34::readRegword(TCS34_GDATAL);
  *b = DFRobot_TCS34::readRegword(TCS34_BDATAL);

  switch (_tcs34IntegrationTime)
  {
    case TCS3400_INTEGRATIONTIME_2_78MS:
      delay(3);
    break;
    case TCS3400_INTEGRATIONTIME_27_8MS:
      delay(28);
    break;
    case TCS3400_INTEGRATIONTIME_103MS:
      delay(103);
    break;
    case TCS3400_INTEGRATIONTIME_178MS:
      delay(178);
    break;
    case TCS3400_INTEGRATIONTIME_712MS:
      delay(712);
    break;
    default:
    break;
  }
}