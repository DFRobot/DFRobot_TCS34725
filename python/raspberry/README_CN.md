# DFRobot_TCS

- [English Version](./README.md)

TCS34725是一款低成本，高性价比的RGB全彩颜色识别传感器，传感器通过光学感应来识别物体的表面颜色。支持红、绿、蓝(RGB)三基色，支持明光感应，可以输出对应的具体数值，帮助您还原颜色本真。 为了提高精度，防止周边环境干扰，我们特意在传感器底部添加了一块红外遮光片，最大程度减小了入射光的红外频谱成份，让颜色管理更加准确。板载自带四个高亮LED，可以让传感器在低环境光的情况下依然能够正常使用，实现“补光”的功能。模块采用I2C通信，拥有PH2.0和XH2.54（面包板）两种接口，用户可以根据自己的需求来选择接口，更加便利。
![正反面svg效果图](./resources/images/SEN0212.png)

## 产品链接(https://www.dfrobot.com.cn/goods-1349.html)

SKU：SEN0212

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

一个颜色传感器库

## 库安装

要使用这个库，首先将库下载到Raspberry Pi，然后打开例程文件夹。要执行一个例程demox.py，请在命令行中输入python demox.py。例如，要执行colorview.py例程，你需要输入:
```
cd DFRobot_TCS/python/raspberry/examples/TCS3400
python colorview.py
```

## 方法
```python
	def begin(self):
    '''!
      @fn begin
      @brief 初始化传感器
      @return 返回初始状态
    '''
    
  def set_integration_time(self,it):
    '''!
      @fn set_integration_time
	    @brief 设置积分时间
	    @param it  积分时间
    '''
    
  def set_gain(self,gain):
    '''!
      @fn set_gain
	    @brief 设置增益
	    @param gain  增益值
    '''

  def calculate_colortemperature(self,r,g,b):
    '''!
      @fn calculate_colortemperature
	    @brief  将原始R/G/B值转换为色温(以度为单位)  
	    @param r  red.
	    @param g  green.
	    @param b  blue.
	    @return uint16_t 色温
    '''

  def calculate_lux(self,r,g,b):
    '''!
      @fn calculateLux
	    @brief 将原始的R/G/B值转换为lux
	    @param r  red.
	    @param g  green.
	    @param b  blue.
	    @return  uint16_t lux.
    '''
  
  def lock(self):
    '''!
      @fn lock
	    @brief 启用中断
    '''
  
  def unlock(self):
    '''!
      @fn unlock
	    @brief 不启用中断
    '''
  
  def clear(self):
      '''!
        @fn clear
	      @brief 清除中断
      '''
  
  def set_int_limits(self,low,high):
      '''!
        @fn set_int_limits
	      @brief 设置Int限制
	      @param l low .
	      @param h high .
      '''

  def set_generateinterrupts(self):
    '''!
      @fn setGenerateinterrupts
	    @brief 设置通用中断
    '''

```
## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Raspberry Pi              |      √         |            |             | 

## 历史

- 2022/3/16 - 1.0.0 版本
- 2024/4/24 - 1.0.1 版本

## 创作者

Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
