//
//  ANTboaction.h
//  
//  V1.0
//  Created by Jason on 15-10-28.
//
//

#ifndef _ANTboaction_H_
#define _ANTboaction_H_

#include "Arduino.h"
#include "Servo.h"

/*
//Servo pins
#define FRONTLEGPIN  7
#define MIDLEGPIN 	8
#define REARLEGPIN 4

//seting the servo angle  for init
#define  FRONTLEGINIT 90
#define  MIDLEGINIT 90
#define  REARLEGINIT 90

#define FRONTMINANGLE (FRONTLEGINIT-20)
#define FRONTMAXANGLE (FRONTLEGINIT+20)
#define MIDMINANGLE (MIDLEGINIT-20)
#define MIDMAXANGLE (MIDLEGINIT+20)
#define REARMINANGLE (REARLEGINIT-20)
#define REARMAXANGLE (REARLEGINIT+20)

*/

//creating the servo objects for chongchong
/*
Servo frontLeg;
Servo midLeg;
Servo rearLeg;
*/

/*
uint8_t frontLegAngle;
uint8_t midLegAngle;
uint8_t rearLegAngle;
*/

class ANTboaction
{
	public:
		ANTboaction();
		void updateInitAngle();
		void servoDetach();
		void servoAttach();
		void stopAction();
		void shakeAction(uint8_t stepAngle,uint8_t midDelay);
		void rockAction(uint8_t stepAngle,uint8_t frontDelay);
		void lookAction(uint8_t stepAngle, uint8_t frontDelay);
		void forwardAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay);
		void reverseAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay);
		void leftTurnAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay);
		void rightTurnAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay);
		void updateServoAngle(uint8_t fleg, uint8_t mleg, uint8_t rleg);
		void setFrontServoAngle(uint8_t fleg);
		void setMidServoAngle(uint8_t mleg);
		void setRearServoAngle(uint8_t rleg);
		void initFrontServoAngle(uint8_t fleg);
		void initMidServoAngle(uint8_t mleg);
		void initRearServoAngle(uint8_t rleg);
		
		void fRockAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay);
		
		//Servo pins
		int frontLegPin;
		int midLegPin;
		int rearLegPin;

		//seting the servo angle  for init
		int frontLegInit;
		int midLegInit;
		int rearLegInit;

		int frDvalue;
		
		
		void setup();
		void update();

		unsigned long stepIndex;           //步数
		unsigned long obstacleTimesIndex;  //避障次数
		unsigned long fallTimesIndex;      //跌倒次数
		unsigned long frightenTimesIndex;  //受惊次数
		unsigned long graspTimesIndex;     //抓住次数
		unsigned long coquetryTimesIndex;  //撒娇次数
		unsigned long phototaxisIndex;     //趋光度
		unsigned long photophbismIndex;    //避光度

	private:
		unsigned long midTime;
		unsigned long frontRearTime;	
	    uint8_t frontMinAngle; 
		uint8_t frontMaxAngle; 
		uint8_t midMinAngle;
		uint8_t midMaxAngle;
		uint8_t rearMinAnget;
		uint8_t tearMaxAnget;

		

};

#endif



