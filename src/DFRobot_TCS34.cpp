/*!
 * @file  DFRobot_TCS34.cpp
 * @brief A library of color sensors
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-16
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#include "DFRobot_TCS34.h"

static float _powf(const float x, const float y)
{
  return (float)(pow((double)x, (double)y));
}

DFRobot_TCS34::DFRobot_TCS34(TwoWire *pWire , uint8_t I2C_addr,eIntegrationTime_t it, eGain_t gain)
:_pWire(pWire),_I2C_addr(I2C_addr),_tcs34Gain(gain),_tcs34IntegrationTime(it){}

boolean DFRobot_TCS34::begin(uint8_t sensor)
{
  Wire.begin();
  uint8_t x =0;
  readReg(TCS34_ID, &x,1); 

  if(sensor == TCS34725){
    if ((x != TCS34_721_725) && (x != 0x10)){
      return false;
    }
  }else{
    if ((x != TCS34_001_005) && (x != 0x10)){
      return false;
    }
  }
  
  setIntegrationtime(_tcs34IntegrationTime);
  setGain(_tcs34Gain);
  enable();
  return true;
}

void DFRobot_TCS34::enable(void)
{
  uint8_t data = TCS34_ENABLE_PON;
  writeReg(TCS34_ENABLE, &data,1);
  data = TCS34_ENABLE_PON | TCS34_ENABLE_AEN;
  delay(3);
  writeReg(TCS34_ENABLE, &data,1);
}

void DFRobot_TCS34::disable(void)
{
  uint8_t reg = 0;
  readReg(TCS34_ENABLE, &reg,1);
  reg = reg & ~(TCS34_ENABLE_PON | TCS34_ENABLE_AEN);
  writeReg(TCS34_ENABLE, &reg,1);
}

void DFRobot_TCS34::setIntegrationtime(eIntegrationTime_t it)
{
  uint8_t data = it;
  writeReg(TCS34_ATIME, &data,1);
  _tcs34IntegrationTime = it;
}

void DFRobot_TCS34::setGain(eGain_t gain)
{
  uint8_t data = gain;
  writeReg(TCS34_CONTROL, &data,1);
  _tcs34Gain = gain;
}



uint16_t DFRobot_TCS34::calculateColortemperature(uint16_t r, uint16_t g, uint16_t b)
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
  cct = (449.0F * _powf(n, 3)) + (3525.0F * _powf(n, 2)) + (6823.3F * n) + 5520.33F;

  /* Return the results in degrees Kelvin */
  return (uint16_t)cct;
}


uint16_t DFRobot_TCS34::calculateLux(uint16_t r, uint16_t g, uint16_t b)
{
  float illuminance;
  /* This only uses RGB ... how can we integrate clear or calculate lux */
  /* based exclusively on clear since this might be more reliable?      */
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  return (uint16_t)illuminance;
}

void DFRobot_TCS34::lock(void)
{
	uint8_t r;
  readReg(TCS34_ENABLE, &r,1);
  r |= TCS34_ENABLE_AIEN;
	writeReg(TCS34_ENABLE, &r,1);
}

void DFRobot_TCS34::unlock(void)
{
	uint8_t r;
  readReg(TCS34_ENABLE, &r,1);
  r &= ~TCS34_ENABLE_AIEN;
	writeReg(TCS34_ENABLE, &r,1);
}

void DFRobot_TCS34::clear(void) {
  _pWire->beginTransmission(_I2C_addr);
#if ARDUINO >= 100
  _pWire->write(TCS34_COMMAND_BIT | 0x66);
#else
  _pWire->send(TCS34_COMMAND_BIT | 0x66);
#endif
  _pWire->endTransmission();
}

void DFRobot_TCS34::setIntLimits(uint16_t low, uint16_t high) {
  uint8_t data = low & 0xFF;
  writeReg(0x04, &data,1);
  data = low >> 8;
  writeReg(0x05, &data, 1);
  data = high & 0xFF;
  writeReg(0x06, &data, 1);
  data = high >> 8;
  writeReg(0x07, &data, 1);
}

void DFRobot_TCS34::setGenerateinterrupts(void)
{
  uint8_t data = TCS34_PERS_NONE;
  writeReg(TCS34_PERS, &data,1);
}

void DFRobot_TCS34::writeReg(uint8_t Reg, void *pData, uint8_t len)
{
  uint8_t *Data = (uint8_t *)pData;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(TCS34_COMMAND_BIT | Reg);
  for (uint8_t i = 0; i < len; i++)
  {
    _pWire->write(Data[i]);
  }
  _pWire->endTransmission();
}

int16_t DFRobot_TCS34::readReg(uint8_t Reg, uint8_t *Data, uint8_t len)
{
  int i = 0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(TCS34_COMMAND_BIT | Reg);
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

uint16_t DFRobot_TCS34::readRegword(uint8_t reg)
{
  uint8_t data_buf[2];
  readReg(reg, data_buf, 2);
  return (data_buf[0] | data_buf[1] << 8);
}