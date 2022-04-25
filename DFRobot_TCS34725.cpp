/*!
 * @file  DFRobot_TCS34725.cpp
 * @brief A library of color sensors
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-16
 * @url         https://github.com/DFRobot/DFRobot_TCS34725
 */

#include "DFRobot_TCS34725.h"

static float powf(const float x, const float y)
{
  return (float)(pow((double)x, (double)y));
}

DFRobot_TCS34725::DFRobot_TCS34725(TwoWire *pWire , uint8_t I2C_addr,eIntegrationTime_t it, eGain_t gain)
{
  _tcs34725IntegrationTime = it;
  _tcs34725Gain = gain;
  _pWire = pWire;
  _I2C_addr = I2C_addr;
}

boolean DFRobot_TCS34725::begin(void)
{
  Wire.begin();
  uint8_t x =0;
  readReg(TCS34725_ID, &x,1);
  if ((x != 0x44) && (x != 0x10))
    return false;
  setIntegrationtime(_tcs34725IntegrationTime);
  setGain(_tcs34725Gain);
  enable();
  return true;
}

void DFRobot_TCS34725::enable(void)
{
  uint8_t data = TCS34725_ENABLE_PON;
  writeReg(TCS34725_ENABLE, &data,1);
  data = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
  delay(3);
  writeReg(TCS34725_ENABLE, &data,1);
}

void DFRobot_TCS34725::disable(void)
{
  uint8_t reg = 0;
  readReg(TCS34725_ENABLE, &reg,1);
  reg = reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
  writeReg(TCS34725_ENABLE, &reg,1);
}

void DFRobot_TCS34725::setIntegrationtime(eIntegrationTime_t it)
{
  uint8_t data = it;
  writeReg(TCS34725_ATIME, &data,1);
  _tcs34725IntegrationTime = it;
}

void DFRobot_TCS34725::setGain(eGain_t gain)
{
  uint8_t data = gain;
  writeReg(TCS34725_CONTROL, &data,1);
  _tcs34725Gain = gain;
}

void DFRobot_TCS34725::getRGBC (uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  *c = readRegword(TCS34725_CDATAL);
  *r = readRegword(TCS34725_RDATAL);
  *g = readRegword(TCS34725_GDATAL);
  *b = readRegword(TCS34725_BDATAL);
  switch (_tcs34725IntegrationTime)
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
  }
}

uint16_t DFRobot_TCS34725::calculateColortemperature(uint16_t r, uint16_t g, uint16_t b)
{
  float X, Y, Z;      /* RGB to XYZ correlation      */
  float xc, yc;       /* Chromaticity co-ordinates   */
  float n;            /* McCamy's formula            */
  float cct;
  /* 1. Map RGB values to their XYZ counterparts.    */
  /* Based on 6500K fluorescent, 3000K fluorescent   */
  /* and 60W incandescent values for a wide range.   */
  /* Note: Y = Illuminance or lux                    */
  X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  Z = (-0.68202F * r) + (0.77073F * g) + ( 0.56332F * b);

  /* 2. Calculate the chromaticity co-ordinates      */
  xc = (X) / (X + Y + Z);
  yc = (Y) / (X + Y + Z);

  /* 3. Use McCamy's formula to determine the CCT    */
  n = (xc - 0.3320F) / (0.1858F - yc);

  /* Calculate the final CCT */
  cct = (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;

  /* Return the results in degrees Kelvin */
  return (uint16_t)cct;
}


uint16_t DFRobot_TCS34725::calculateLux(uint16_t r, uint16_t g, uint16_t b)
{
  float illuminance;
  /* This only uses RGB ... how can we integrate clear or calculate lux */
  /* based exclusively on clear since this might be more reliable?      */
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  return (uint16_t)illuminance;
}

void DFRobot_TCS34725::lock(void)
{
	uint8_t r;
  readReg(TCS34725_ENABLE, &r,1);
  r |= TCS34725_ENABLE_AIEN;
	writeReg(TCS34725_ENABLE, &r,1);
}

void DFRobot_TCS34725::unlock(void)
{
	uint8_t r;
  readReg(TCS34725_ENABLE, &r,1);
  r &= ~TCS34725_ENABLE_AIEN;
	writeReg(TCS34725_ENABLE, &r,1);
}

void DFRobot_TCS34725::clear(void) {
  _pWire->beginTransmission(TCS34725_ADDRESS);
#if ARDUINO >= 100
  _pWire->write(TCS34725_COMMAND_BIT | 0x66);
#else
  _pWire->send(TCS34725_COMMAND_BIT | 0x66);
#endif
  _pWire->endTransmission();
}

void DFRobot_TCS34725::setIntLimits(uint16_t low, uint16_t high) {
  uint8_t data = low & 0xFF;
  writeReg(0x04, &data,1);
  data = low >> 8;
  writeReg(0x05, &data, 1);
  data = high & 0xFF;
  writeReg(0x06, &data, 1);
  data = high >> 8;
  writeReg(0x07, &data, 1);
}

void DFRobot_TCS34725::setGenerateinterrupts(void)
{
  uint8_t data = TCS34725_PERS_NONE;
  writeReg(TCS34725_PERS, &data,1);
}

void DFRobot_TCS34725::writeReg(uint8_t Reg, void *pData, uint8_t len)
{
  uint8_t *Data = (uint8_t *)pData;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(TCS34725_COMMAND_BIT | Reg);
  for (uint8_t i = 0; i < len; i++)
  {
    _pWire->write(Data[i]);
  }
  _pWire->endTransmission();
}

int16_t DFRobot_TCS34725::readReg(uint8_t Reg, uint8_t *Data, uint8_t len)
{
  int i = 0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(TCS34725_COMMAND_BIT | Reg);
  if (_pWire->endTransmission() != 0)
  {
    return -1;
  }
  _pWire->requestFrom((uint8_t)this->_I2C_addr, (uint8_t)len);
  while (_pWire->available())
  {
    Data[i++] = _pWire->read();
  }
  return len;
}

uint16_t DFRobot_TCS34725::readRegword(uint8_t reg)
{
  uint8_t data_buf[2];
  readReg(reg, data_buf, 2);
  return (data_buf[0] | data_buf[1] << 8);
}