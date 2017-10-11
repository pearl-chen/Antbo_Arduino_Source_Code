//
//  ANTboaction.cpp
//  
//  V1.0
//  Created by Jason on 15-10-28.
//
//

#include "ANTboaction.h"

Servo frontLeg;
Servo midLeg;
Servo rearLeg;

static uint8_t frontLegAngle = 0;
static uint8_t midLegAngle = 0;
static uint8_t actionMode = 0;

ANTboaction::ANTboaction()
{
	midTime = 0;
	frontRearTime = 0;
	stepIndex = 0;  
	
	//Servo pins
	frontLegPin   = 7;
	midLegPin     = 8;
	rearLegPin    = 4;
	
	//seting the servo angle  for init
	frontLegInit = 83;
	midLegInit = 90;
	rearLegInit = 80;

}

//初始化舵机的角度初始值，当前中后脚摆正的时候，因个体差异，
//会使每个舵机的最合适的摆正角度有一定差别，不完全是90度
void ANTboaction::updateInitAngle()
{
	frontMinAngle  = frontLegInit - 25;
	frontMaxAngle  = frontLegInit + 25;
	midMinAngle    = midLegInit - 13;
	midMaxAngle    = midLegInit + 13;
	rearMinAnget   = rearLegInit - 25;
	tearMaxAnget   = rearLegInit + 25;

	//初始化舵机运动时候的最大最小转动角度
	frontLegAngle = frontMaxAngle;    
	midLegAngle = midMinAngle;
	
	
	frDvalue = rearLegInit - frontLegInit;
	
}

void ANTboaction::setup()
{
	updateInitAngle();
	frontLeg.attach(frontLegPin);
	midLeg.attach(midLegPin);
	rearLeg.attach(rearLegPin);
}

void ANTboaction::update()
{
	//测试代码
	//forwardAction(8,20,20);
	//reverseAction(8,20,20);
	//leftTurnAction(1,4,4);
	//rightTurnAction(1,4,4);
	//shakeAction(1,2);
	//rockAction(1,4);
	//stopAction();
	
}

//The middle legs shaking function
//midDelay = 2
void ANTboaction::shakeAction(uint8_t stepAngle,uint8_t midDelay)
{
	frontLeg.write(frontLegInit);
	rearLeg.write(rearLegInit);
	if (actionMode > 1)
	{
		actionMode = 0;
	}
	if(actionMode == 0 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle += stepAngle;
		if(midLegAngle >= midMaxAngle+10)   //中间脚摆到最大位置
			actionMode = 1;
		midLeg.write(midLegAngle);	
	}
	if(actionMode == 1 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle -= stepAngle;
		if(midLegAngle <= midMinAngle-10)  //中间脚摆到最小位置
			actionMode = 0;
		midLeg.write(midLegAngle);		
	}
}

//With both feet, shaking movement function
//frontDelay = 4
void ANTboaction::rockAction(uint8_t stepAngle,uint8_t frontDelay)
{
	if (actionMode > 1)
	{
		actionMode = 0;
	}
	midLeg.write(midLegInit);
	if(actionMode == 0 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle -= stepAngle;
		if(frontLegAngle <= frontMinAngle) //前后脚摆到最小位置
			actionMode = 1;
		frontLeg.write(frontLegAngle);
		rearLeg.write(frontLegAngle+frDvalue);
	}
	if(actionMode == 1 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle += stepAngle;
		if(frontLegAngle >= frontMaxAngle)  //前后脚摆到最大位置
			actionMode = 0;
		frontLeg.write(frontLegAngle);
		rearLeg.write(frontLegAngle+frDvalue);
	}
}

//张望
void ANTboaction::lookAction(uint8_t stepAngle, uint8_t frontDelay)
{

	midLeg.write(midLegInit);
	if (actionMode == 0 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle -= stepAngle;
		if (frontLegAngle <= frontMinAngle + 5) //前后脚摆到最小位置
			actionMode = 1;
		rearLeg.write(frontLegAngle + frDvalue);
		frontLeg.write(frontLegAngle);
	}
	if (actionMode == 1)                        //消耗时间
	{
		if (millis() - frontRearTime < 1000)
			servoDetach();
		else {
			servoAttach();
			actionMode = 2;
		}
	}
	if (actionMode == 2 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle += stepAngle;
		if (frontLegAngle >= frontMaxAngle - 5)  //前后脚摆到最大位置
			actionMode = 3;
		rearLeg.write(frontLegAngle + frDvalue);
		frontLeg.write(frontLegAngle);
	}
	if (actionMode == 3)                         //消耗时间
	{
		if (millis() - frontRearTime < 1000)
			servoDetach();
		else {
			servoAttach();
			actionMode = 0;
		}
	}
}

//Forward movement function
//正常前进的时候：
//midDelay = 5
//frontDelay = 4
//快速前进的时候
//midDelay = 1
//frontDelay = 2

void ANTboaction::forwardAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay)
{

	if(actionMode == 0 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle+= stepAngle;
		if(midLegAngle >= midMaxAngle)           //中间脚摆到最大位置
			actionMode = 1;
		midLeg.write(midLegAngle);		
	}
	if(actionMode == 1 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle-= stepAngle;
		if(frontLegAngle <= frontMinAngle)  
			actionMode = 2;
		frontLeg.write(frontLegAngle);           //前后脚同时摆到最小位置
		rearLeg.write(frontLegAngle+frDvalue);
	}
	if(actionMode == 2 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle-= stepAngle;
		if(midLegAngle <= midMinAngle)           //中间脚摆到最小位置
			actionMode = 3;
		midLeg.write(midLegAngle);		
	}
	if(actionMode == 3 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle += stepAngle;
		if(frontLegAngle >= frontMaxAngle)   
			actionMode = 4;
		frontLeg.write(frontLegAngle);           //前后脚摆到最大位置
		rearLeg.write(frontLegAngle+frDvalue);
	}
	if (actionMode == 4) {
		actionMode = 0;
		stepIndex++;                              //步数累加
	}

	
}

void ANTboaction::fRockAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay)
{

	if(actionMode == 0 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle+= stepAngle;
		if(midLegAngle >= midMaxAngle)          //中间脚摆到最大位置
			actionMode = 1;
		midLeg.write(80);		
	}
	if(actionMode == 1 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle-= stepAngle;
		if(frontLegAngle <= frontMinAngle)  
			actionMode = 2;
		frontLeg.write(frontLegAngle);           //前后脚同时摆到最小位置
		rearLeg.write(frontLegAngle+frDvalue);
	}
	if(actionMode == 2 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle-= stepAngle;
		if(midLegAngle <= midMinAngle)           //中间脚摆到最小位置
			actionMode = 3;
		midLeg.write(80);		
	}
	if(actionMode == 3 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle += stepAngle;
		if(frontLegAngle >= frontMaxAngle)   
			actionMode = 0;
		frontLeg.write(frontLegAngle);           //前后脚摆到最大位置
		rearLeg.write(frontLegAngle+frDvalue);
	}
	
}


//Backward motion function
//正常后退的时候：
//midDelay = 5
//frontDelay = 4
void ANTboaction::reverseAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay) //forwardActiongit
{
	if(actionMode == 0 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle += stepAngle;
		if(midLegAngle >= midMaxAngle)          //中间脚摆到最大位置
			actionMode = 1; 
		midLeg.write(midLegAngle);		
	}
	if(actionMode == 1 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle += stepAngle;
		if(frontLegAngle >= frontMaxAngle)
			actionMode = 2;
		frontLeg.write(frontLegAngle);          //前后脚摆到最大位置
		rearLeg.write(frontLegAngle+frDvalue);
	}
	if(actionMode == 2 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle -= stepAngle;
		if(midLegAngle <= midMinAngle)          //中间脚摆到最小位置
			actionMode = 3;
		midLeg.write(midLegAngle);		
	}
	if(actionMode == 3 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle -= stepAngle;
		if(frontLegAngle <= frontMinAngle)      //前后脚摆到最小位置
			actionMode = 4;
		frontLeg.write(frontLegAngle);
		rearLeg.write(frontLegAngle+frDvalue);
	}
	if (actionMode == 4) {
		actionMode = 0;
		stepIndex++;                               //步数累加
	}
}

//Forward movement function
//正常前进的时候：
//midDelay = 5
//frontDelay = 4
//快速前进的时候
//midDelay = 1
//frontDelay = 2

void ANTboaction::rightTurnAction(uint8_t stepAngle, uint8_t midDelay, uint8_t frontDelay)
{
	if (actionMode == 0 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle += stepAngle;
		if (midLegAngle >= midMaxAngle)         //中间脚摆到最大位置
			actionMode = 1;
		midLeg.write(midLegAngle);
	}
	if (actionMode == 1 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle -= stepAngle;
		if (frontLegAngle <= frontMinAngle)
			actionMode = 2;
		frontLeg.write(frontLegAngle);           //前后脚同时摆到最小位置
		rearLeg.write(frontLegAngle + frDvalue-5);
	}
	if (actionMode == 2 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle -= stepAngle;
		if (midLegAngle <= midLegInit)            //中间脚摆正
			actionMode = 3;
		midLeg.write(midLegAngle);
	}
	if (actionMode == 3 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle += stepAngle;
		if (frontLegAngle >= frontMaxAngle)
			actionMode = 4;
		frontLeg.write(frontLegAngle);            //前后脚摆到最大位置
		rearLeg.write(frontLegAngle + frDvalue+5);
	}
	if (actionMode == 4) {
		actionMode = 0;
		stepIndex++;                               //步数累加
	}
	//stepIndex++; //步数累加
}


//Turn left movement function
//midDelay = 4
//frontDelay = 4
//void ANTboaction::leftTurnAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay)
//{
//	static uint8_t frontLegAngle = frontLegInit;
//	static uint8_t midLegAngle = midMaxAngle;
//	static uint8_t actionMode = 0;
//	if(actionMode == 0 && millis() - midTime > midDelay)
//	{
//		midTime = millis();
//		midLegAngle -= stepAngle;
//		if(midLegAngle <= midMinAngle-10)                  //中间脚摆到最小位置 + 10
//			actionMode = 1;
//		midLeg.write(midLegAngle);		
//	}
//	if(actionMode == 1 && millis() - frontRearTime > frontDelay)
//	{
//		frontRearTime = millis();
//		frontLegAngle += stepAngle;
//		if(frontLegAngle >= frontMaxAngle+10)
//			actionMode = 2;     
//		frontLeg.write(frontLegAngle);                      //前脚摆到最大位置 + 10
//		//rearLeg.write(frontLegAngle+frDvalue);
//	}
//	if(actionMode == 2 && millis() - midTime > midDelay)
//	{
//		midTime = millis();
//		midLegAngle += stepAngle;
//		if(midLegAngle >= midLegInit)                        //中间脚回正
//			actionMode = 3;
//		midLeg.write(midLegAngle);		
//	}
//	if(actionMode == 3 && millis() - frontRearTime > frontDelay)
//	{
//		frontRearTime = millis();
//		frontLegAngle -= stepAngle;
//		if(frontLegAngle <= frontMinAngle)//frontLegInit+5)   //前脚摆到最小位置
//			actionMode = 0;
//		frontLeg.write(frontLegAngle);
//		//rearLeg.write(frontLegAngle+frDvalue);
//	}
//}

void ANTboaction::leftTurnAction(uint8_t stepAngle, uint8_t midDelay, uint8_t frontDelay)
{

	if (actionMode == 0 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle -= stepAngle;
		if (midLegAngle <= midMinAngle)         //中间脚摆到最小位置
			actionMode = 1;
		midLeg.write(midLegAngle);
	}
	if (actionMode == 1 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle += stepAngle;
		if (frontLegAngle >= frontMaxAngle)
			actionMode = 2;
		frontLeg.write(frontLegAngle);           //前后脚同时摆到最大位置
		rearLeg.write(frontLegAngle + frDvalue+5);
	}
	if (actionMode == 2 && millis() - midTime > midDelay)
	{
		midTime = millis();
		midLegAngle += stepAngle;
		if (midLegAngle >= midLegInit)           //中间脚摆正
			actionMode = 3;
		midLeg.write(midLegAngle);
	}
	if (actionMode == 3 && millis() - frontRearTime > frontDelay)
	{
		frontRearTime = millis();
		frontLegAngle -= stepAngle;
		if (frontLegAngle <= frontMinAngle)
			actionMode = 4;
		frontLeg.write(frontLegAngle);         //前后脚摆到最小位置
		rearLeg.write(frontLegAngle + frDvalue-5);
	}
	if (actionMode == 4) {
		actionMode = 0;
		stepIndex++;                               //步数累加
	}
	//stepIndex++; //步数累加
}

//Turn right action function
//midDelay = 4
//frontDelay = 4
// void ANTboaction::rightTurnAction(uint8_t stepAngle,uint8_t midDelay,uint8_t frontDelay)
// {
	// static uint8_t frontLegAngle = frontLegInit;
	// static uint8_t midLegAngle = midMinAngle;
	// static uint8_t actionMode = 0;
	// if(actionMode == 0 && millis() - midTime > midDelay)
	// {
		// midTime = millis();
		// midLegAngle += stepAngle;
		// if(midLegAngle >= midMaxAngle+10)                      //中间脚摆到最大位置 + 10
			// actionMode = 1;
		// midLeg.write(midLegAngle);		
	// }
	// if(actionMode == 1 && millis() - frontRearTime > frontDelay)
	// {
		// frontRearTime = millis();
		// frontLegAngle -= stepAngle;
		// if(frontLegAngle <= frontMinAngle-10)                  //前脚摆到最小位置 - 10
			// actionMode = 2;
		// frontLeg.write(frontLegAngle);
		// //rearLeg.write(frontLegAngle+frDvalue);
	// }
	// if(actionMode == 2 && millis() - midTime > midDelay)
	// {
		// midTime = millis();
		// midLegAngle -= stepAngle;
		// if(midLegAngle <= midLegInit)                          //中间脚回正
			// actionMode = 3;
		// midLeg.write(midLegAngle);		
	// }
	// if(actionMode == 3 && millis() - frontRearTime > frontDelay)
	// {
		// frontRearTime = millis();
		// frontLegAngle += stepAngle;
		// if(frontLegAngle >= frontMaxAngle)//frontLegInit+5)    //前脚摆到最大位置
			// actionMode = 0;
		// frontLeg.write(frontLegAngle);
		// //rearLeg.write(frontLegAngle+frDvalue);
	// }

// }

//void ANTboaction::stopAction()
//{
//	frontLeg.write(frontLegInit);
//	midLeg.write(midLegInit);
//    rearLeg.write(rearLegInit);
//}

void ANTboaction::stopAction()
{
	midLeg.write(midLegInit);
	if (millis() - frontRearTime > 3)
	{
		frontRearTime = millis();
		if (frontLegAngle > frontLegInit) {
			frontLegAngle -= 1;
		}
		if (frontLegAngle < frontLegInit) {
			frontLegAngle += 1;
		}
		frontLeg.write(frontLegAngle);
		rearLeg.write(frontLegAngle + frDvalue);
	}
	//if (actionMode == 1 && millis() - frontRearTime > 2)
	//{
	//	frontRearTime = millis();
	//	if(midLegAngle > )
	//	frontLegAngle += 1;
	//	if (frontLegAngle >= frontMaxAngle)  //前后脚摆到最大位置
	//		actionMode = 0;
	//	frontLeg.write(frontLegAngle);
	//	rearLeg.write(frontLegAngle + frDvalue);
	//}
}

void ANTboaction::servoAttach()
{
	frontLeg.attach(frontLegPin);
	midLeg.attach(midLegPin);
	rearLeg.attach(rearLegPin);
}

void ANTboaction::servoDetach()
{
	frontLeg.detach();
	midLeg.detach();
	rearLeg.detach();
}

//Specify the motion of the steering Angle function
void ANTboaction::updateServoAngle(uint8_t fleg, uint8_t mleg, uint8_t rleg)
{
	midLeg.write(mleg);
	frontLeg.write(fleg);
    rearLeg.write(rleg);
}

void ANTboaction::setFrontServoAngle(uint8_t fleg)
{
	frontLeg.write(fleg);
}

void ANTboaction::setMidServoAngle(uint8_t mleg)
{
	midLeg.write(mleg);
}

void ANTboaction::setRearServoAngle(uint8_t rleg)
{
	rearLeg.write(rleg);
}

void ANTboaction::initFrontServoAngle(uint8_t fleg)
{
	frontLegInit = fleg;
}

void ANTboaction::initMidServoAngle(uint8_t mleg)
{
	midLegInit = mleg;
}

void ANTboaction::initRearServoAngle(uint8_t rleg)
{
	rearLegInit = rleg;
}



































