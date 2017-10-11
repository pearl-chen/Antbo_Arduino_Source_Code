//
//  ANTboled.h
//  
//  V1.0
//  Created by Jason on 15-11-2.
//
//
#include"ANTboled.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel leds = Adafruit_NeoPixel(ANTBO_LEDS, RGBPIN, NEO_GRB + NEO_KHZ800);

//初始化LED相关引脚和参数
void ANTboled::setup()
{
	//FastLED.addLeds<WS2812, RGBPIN, RGB>(leds, ANTBO_LEDS);
	leds.begin();  // Call this to start up the LED strip.                      
	resetLed();    // This function, defined below, turns all LEDs off...       
	leds.show();   // ...but the LEDs don't actually update until you call this. 
	
}

//刷新LED显示函数
void ANTboled::update()
{
	leds.show();	
}



//熄灭所有LED
void ANTboled::resetLed()
{
	for(int i = 0; i < ledNumber; i++)
		leds.setPixelColor(i, 0);
}

//熄灭指定的LED
void ANTboled::resetLed(int lednumber)
{
	leds.setPixelColor(lednumber, 0);
}

//指定亮度点亮某个LED
void ANTboled::lightLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,uint8_t light)
{
	leds.setPixelColor(lednumber, red, green, blue);
	leds.setBrightness(light);

}

//最大亮度点亮某个LED
void ANTboled::lightLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue)
{
	leds.setPixelColor(lednumber, red, green, blue);
}

//点亮所有LED
void ANTboled::lightLedAll(uint8_t red,uint8_t green,uint8_t blue,uint8_t light)
{
	for(uint8_t i = 0; i < ANTBO_LEDS; i++)
		lightLed(i, red, green, blue, light);
}

//小灯闪烁
void ANTboled::blinkLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,int time)
{
	static unsigned long currentTime;
  //static uint8_t light = 255;
    if((millis() - currentTime) < time)
    {
	  lightLed(lednumber,red,green,blue,255);
    }
    else
		resetLed();
	//resetLed(lednumber);
	if(millis() - currentTime > 2*time)
    {
      currentTime = millis();
    }
}
//小灯指定亮度闪烁
void ANTboled::blinkLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,uint8_t ledlight,int time)
{
	static unsigned long currentTime;
    static uint8_t light = 255;
    if((millis() - currentTime) < time)
    {
	  lightLed(lednumber,red,green,blue,ledlight);
    }
    else
		resetLed();
	//resetLed(lednumber);
	if(millis() - currentTime > 2*time)
    {
      currentTime = millis();
    }
}

//所有LED以time时间闪烁
void ANTboled::blinkLedAll(uint8_t red,uint8_t green,uint8_t blue,int time)
{
	for(uint8_t i = 0; i < ANTBO_LEDS; i++)
		blinkLed( i, red, green, blue, time);
}

//所有小灯指定亮度闪烁
void ANTboled::blinkLedAll(uint8_t red,uint8_t green,uint8_t blue,uint8_t light,int time)
{
	for(uint8_t i = 0; i < ANTBO_LEDS; i++)
		blinkLed( i, red, green, blue, light,time);										
}

//呼吸灯函数
void ANTboled::breatheLed(int lednumber,uint8_t red,uint8_t green,uint8_t blue,int time)
{
	static unsigned long currentTime;
	static uint8_t light;
	static float angle = PI;//0.0;
	if((millis() - currentTime) > time)
	{
		currentTime = millis(); 
		angle += PI/180;
		light = Y-A*cos(angle);
		if(angle >= 2*PI)
		{
		angle = 0;
		} 
	}
	lightLed(lednumber, red, green, blue, light);
	//lightLed(lednumber,uint8_t(light*red/255),uint8_t(light*green/255),uint8_t(light*blue/255));
}

//所有LED呼吸灯
void ANTboled::breatheLedAll(uint8_t red,uint8_t green,uint8_t blue,int time)
{
	for(uint8_t i = 0; i < ANTBO_LEDS; i++)
		breatheLed( i, red, green, blue, time);
}


ANTboled::ANTboled(int lednumbers)
{
	fastLed = 0;
	ledNumber = lednumbers;
}













