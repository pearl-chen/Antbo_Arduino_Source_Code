#ifndef _ANTboir_H_
#define _ANTboir_H_

#include <Arduino.h>

class ANTboir
{
	public:
		ANTboir();
		bool isObstacled(); //true表示前面有障碍
		void resetIr();
		void setup();
		void update();
	    int irNumber;
	private:
		bool isObstacle;
		int pinIrIn;
		int pinIrLed;
};


#endif