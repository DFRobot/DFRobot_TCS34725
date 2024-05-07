/*!
 * @file  colorview.ino
 * @brief Gets the ambient light color
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      TangJie(jie.Tang@dfrobot.com)
 * @version     V1.0.0
 * @date        2024-04-24
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#include "DFRobot_TCS3400.h"

DFRobot_TCS3400 tcs = DFRobot_TCS3400(&Wire, TCS3400_ADDR,TCS3400_INTEGRATIONTIME_27_8MS, TCS3400_GAIN_1X);
void setup() 
{
  Serial.begin(115200);
  Serial.println("Color View Test!");

  while(tcs.begin() != 0)
  {
    Serial.println("No TCS3400 found ... check your connections");
    delay(1000);
  }
}

void loop() {
  uint16_t clear, red, green, blue;
  tcs.getRGBC(&red, &green, &blue, &clear);
  tcs.lock();  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.println("\t");
  
  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
}

