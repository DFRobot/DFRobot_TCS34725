/*!
 * @file  colorview.ino
 * @brief The Arduino is triggered to fetch data when there is a low level on the interrupt pin
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-16
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#include <DFRobot_TCS34725.h>
#define interruptPin 3

DFRobot_TCS34725 tcs = DFRobot_TCS34725(&Wire, TCS34725_ADDRESS, TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
volatile boolean state = false;

// Interrupt Service Routine
void isr(void)
{
  state = true;
}

/**
 * tcs.getRGBC() does a delay(Integration_Time) after the sensor readout.
 * We don't need to wait for the next integration cycle because we receive
 * an interrupt when the integration cycle is complete.
 */
void getRawData_noDelay(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  *c = tcs.readRegword(TCS34_CDATAL);
  *r = tcs.readRegword(TCS34_RDATAL);
  *g = tcs.readRegword(TCS34_GDATAL);
  *b = tcs.readRegword(TCS34_BDATAL);
}

void setup()
{
  Serial.begin(115200);
  // TCS interrupt output is Active-LOW and Open-Drain
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), isr, FALLING);
  while (tcs.begin() != 0)
  {
    Serial.println("No TCS34725 found ... check your connections");
    delay(1000);
  }
  // Set persistence filter to generate an interrupt for every RGB Cycle, regardless of the integration limits
  tcs.setGenerateinterrupts();
  tcs.lock();
  Serial.flush();
}

void loop()
{
  if (state)
  {
    uint16_t r, g, b, c, colorTemp, lux;
    getRawData_noDelay(&r, &g, &b, &c);
    colorTemp = tcs.calculateColortemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);
    Serial.print("Color Temp: ");
    Serial.print(colorTemp, DEC);
    Serial.print(" K - ");
    Serial.print("Lux: ");
    Serial.print(lux, DEC);
    Serial.print(" - ");
    Serial.print("R: ");
    Serial.print(r, DEC);
    Serial.print(" ");
    Serial.print("G: ");
    Serial.print(g, DEC);
    Serial.print(" ");
    Serial.print("B: ");
    Serial.print(b, DEC);
    Serial.print(" ");
    Serial.print("C: ");
    Serial.print(c, DEC);
    Serial.print(" ");
    Serial.println(" ");
    Serial.flush();
    tcs.clear();
    state = false;
  }
}