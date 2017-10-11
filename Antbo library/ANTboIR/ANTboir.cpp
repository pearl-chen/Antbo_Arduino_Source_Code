#include "ANTboir.h"

//static int  irNumber = 0;
//ANTboir irCount;
char irCountNumber;

ANTboir::ANTboir()
{
	pinIrIn = 3;
	pinIrLed = 5;
	isObstacle = false;
}

void ANTboir::resetIr()
{
	isObstacle = false;
}

bool ANTboir::isObstacled()
{
	if(isObstacle)
	{
		isObstacle = false;
		return true;
	}
	else
		return false;
}

void count()
{
	//irCount.irNumber++;
	irCountNumber++;
}

void ANTboir::setup()
{
	pinMode(pinIrLed,OUTPUT);//接近传感器灯
       
    pinMode(pinIrIn,INPUT);//init the ir receiver pin
    
    digitalWrite(pinIrLed,HIGH);
    	
	attachInterrupt(1, count, FALLING);
	
}


void ANTboir::update()
{
	//irCount.irNumber = 0;
	irCountNumber = 0;
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 50; j++)
		{
			digitalWrite(pinIrLed,LOW);  //ir_led on
			delayMicroseconds(6);
			
			digitalWrite(pinIrLed,HIGH);
			delayMicroseconds(6);
		}

		delayMicroseconds(600);
	}
	irNumber = irCountNumber;
	//Serial.println(irCount.irNumber);
	if(irCountNumber >= 20 )
	{
		isObstacle = true;
		// Serial.println("In front of obstacles");
		// Serial.println(irCount.irNumber);
	}
}



