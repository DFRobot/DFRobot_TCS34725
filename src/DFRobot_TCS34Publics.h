/*!
 * @file  DFRobot_TCS34Publics.h
 * @brief General document
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      TangJie(jie.tang@dfrobot.com)
 * @version     V1.0.0
 * @date        2024-04-24
 * @url         https://github.com/DFRobot/DFRobot_TCS
 */
#ifndef _DFROBOT_TCS34PUBLICS_H_
#define _DFROBOT_TCS34PUBLICS_H_

#define TCS34725                0 
#define TCS3400                 1
#define TCS34_001_005           0X90
#define TCS34_003_007           0X93
#define TCS34_721_725           0X44
#define TCS34_723_727           0X4d

/**
 	   * @enum eIntegrationTime_t
 	   * @brief Integration Time
 	   */
	  typedef enum
    {
      //TCS34725
      TCS34725_INTEGRATIONTIME_2_4MS  = 0xFF,   ///<  2.4ms - 1 cycle    - Max Count: 1024  
      TCS34725_INTEGRATIONTIME_24MS   = 0xF6,   ///<  24ms  - 10 cycles  - Max Count: 10240 
      TCS34725_INTEGRATIONTIME_50MS   = 0xEB,   ///<  50ms  - 20 cycles  - Max Count: 20480 
      TCS34725_INTEGRATIONTIME_101MS  = 0xD5,   ///<  101ms - 42 cycles  - Max Count: 43008 
      TCS34725_INTEGRATIONTIME_154MS  = 0xC0,   ///<  154ms - 64 cycles  - Max Count: 65535 
      TCS34725_INTEGRATIONTIME_700MS  = 0x00,   ///<  700ms - 256 cycles - Max Count: 65535 
      //TCS3400
      TCS3400_INTEGRATIONTIME_2_78MS  = 0xFF,   ///<  2.78ms - 1 cycle    - Max Count: 1024
      TCS3400_INTEGRATIONTIME_27_8MS  = 0xF6,   ///<  27.8ms  - 10 cycles  - Max Count: 10240 
      TCS3400_INTEGRATIONTIME_103MS   = 0xDB,   ///<  103ms  - 20 cycles  - Max Count: 37888 
      TCS3400_INTEGRATIONTIME_178MS   = 0xC0,   ///<   178ms - 42 cycles  - Max Count: 65535 
      TCS3400_INTEGRATIONTIME_712MS   = 0x00,   ///<   712ms - 64 cycles  - Max Count: 65535 
    }eIntegrationTime_t;

    /**
     * @enum eGain_t
     * @brief Used to set the color sensor receive gain
     */
    typedef enum
    {
      //TCS34725
      TCS34725_GAIN_1X                = 0x00,   ///<  1x gain  
      TCS34725_GAIN_4X                = 0x01,   ///<  4x gain  
      TCS34725_GAIN_16X               = 0x02,   ///<  16x gain 
      TCS34725_GAIN_60X               = 0x03,   ///<  60x gain 
      //TCS3400
      TCS3400_GAIN_1X                 = 0x00,   ///<  1x gain  
      TCS3400_GAIN_4X                 = 0x01,   ///<  4x gain  
      TCS3400_GAIN_16X                = 0x02,   ///<  16x gain 
      TCS3400_GAIN_64X                = 0x03,   ///<  64x gain 
    }eGain_t;

#endif
