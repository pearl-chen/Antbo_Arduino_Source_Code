//
//  ANTboled.h
//  
//  V1.0
//  Created by Jason on 15-11-2.
//
//

#ifndef _ANTboled_H_
#define _ANTboled_H_

#include <Arduino.h>
//#include "FastLED.h"
//#include "Adafruit_NeoPixel.h"

#define ANTBO_LEDS 2
#define RGBPIN 6 //WS2812的连接引脚
#define PI 3.14
#define A 125 //呼吸灯余弦函数的振幅，最大振幅255/2
#define Y 125 //呼吸灯余弦函数的Y轴平移量


/*
自然为蓝色（H:203  S:98  B:72） ，（R:4    G:115  B:184）
快乐为橙色（H:34   S:90  B:96） ，（R:245  G:149  B:24）
害羞为粉色（H:337  S:52  B:100），（R:255  G:122  B:173）
愤怒为红色（H:1    S:93  B:86） ，（R:219  G:19   B:15）
恐惧为紫色（H:308  S:78  B:58） ，（R:148  G:33   B:133）
厌恶为绿色（H:140  S:81  B:65） ，（R:31   G:166  B:76）
*/

class ANTboled
{
	public:
		ANTboled(int lednumbers);
		//熄灭所有LED
		void resetLed();   
		
		//熄灭指定LED
		void resetLed(int lednumber);  
		
		//颜色的平滑过渡，在此函数调用之前需要调用colorCount()函数
		//bool colorAction(int lednumber,uint8_t red,uint8_t green,uint8_t blue,int time); 
		
		//指定亮度light点亮指定LED
		void lightLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,uint8_t light); 
		
		//最大亮度点亮某个LED
		void lightLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue);  
		
		//点亮所有LED
		void lightLedAll(uint8_t red,uint8_t green,uint8_t blue,uint8_t light); 

		//计算LED平滑过渡值 
		//void colorCount(int lednumber,uint8_t red,uint8_t green,uint8_t blue,int time);
		
		//指定LED以time时间闪烁
		void blinkLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,int time);
		
		void blinkLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,uint8_t light,int time);
		
		//所有LED以time时间闪烁
		void blinkLedAll(uint8_t red,uint8_t green,uint8_t blue,int time);
		void blinkLedAll(uint8_t red,uint8_t green,uint8_t blue,uint8_t light,int time);
		
		//指定LED呼吸灯
		void breatheLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,int time);
		
		//所有LED呼吸灯
		void breatheLedAll(uint8_t red,uint8_t green,uint8_t blue,int time);
		
		//平滑过渡到指定显示的颜色
		//bool smoothLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,int time);
	
		void setup();
		void update();
		
	private:
		int ledNumber;
		float currentColor[ANTBO_LEDS][3];
		float targetColor[ANTBO_LEDS][3];
		float colorAcc[ANTBO_LEDS][3];
		bool fastLed;
		
};


#endif