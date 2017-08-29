#pragma config(Sensor, in1,    pLLift,         sensorPotentiometer)
#pragma config(Sensor, in2,    gLift,          sensorGyro)
#pragma config(Sensor, in3,    pChainbar,      sensorPotentiometer)
#pragma config(Sensor, in4,    pClaw,          sensorPotentiometer)
#pragma config(Sensor, in5,    gBase,          sensorGyro)
#pragma config(Sensor, in6,    lLeft,          sensorLineFollower)
#pragma config(Sensor, in7,    lMiddle,        sensorLineFollower)
#pragma config(Sensor, in8,    lRight,         sensorLineFollower)
#pragma config(Sensor, dgtl1,  qLeftDrive,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  qRightDrive,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  tLiftDown,      sensorTouch)
#pragma config(Sensor, dgtl6,  tMobileOut,     sensorTouch)
#pragma config(Sensor, dgtl7,  tMobileIn,      sensorTouch)
#pragma config(Sensor, dgtl8,  tMobileLoaded,  sensorTouch)
#pragma config(Motor,  port1,           mChainbar,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           mFrontRight,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           mFrontLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mLiftRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           mMobileLeft,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           mMobileRight,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mLiftLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mBackLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           mBackRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          mClaw,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "Autonomous.c"

int RightJoyMV; //Main Right Y
int RightJoySV; //Partner Right Y
int LeftJoyMV;  //Main Left Y
int LeftJoySV;  //Partner Left Y
int LeftJoyMH; //Main Left X
int LeftJoySH; //Partner Left X
int RightJoyMH; //Main Right X
int RightJoySH; //Partner Right X
string batteryMain; //String for lcd
string batteryPowerExpander; //String for lcd


int JoyClear(int origVal) { //intake current joystick position
	if(abs(origVal) < 10){ // if joystick is close to still just return 0
		return 0;
	}
	else{
		return origVal; //else, function properly
	}
	//Stops the idle motor sound
}


int PowerCap(int motorPower){ //intake joystick position
	if(abs(motorPower) <= 127){ //if power value is between 127 & -127 then return actual power
		return motorPower;
	}
	else if(motorPower > 127){ //if above 127, set to 127
		return 127;
	}
	else{ //if below -127, set to -127
		return -127;
	}
}

void Variables(){
	RightJoyMV = JoyClear(vexRT[Ch2]);
	RightJoySV = JoyClear(vexRT[Ch2Xmtr2]);
	LeftJoyMV = JoyClear(vexRT[Ch3]);
	LeftJoySV = JoyClear(vexRT[Ch3Xmtr2]);
	RightJoyMH = JoyClear(vexRT[Ch1]);
	RightJoySH = JoyClear(vexRT[Ch1Xmtr2]);
	LeftJoyMH = JoyClear(vexRT[Ch4]);
	LeftJoySH = JoyClear(vexRT[Ch4Xmtr2]);
	//Configure joysticks for deidling
}

void lDrive(int pwr){
	motor[mBackLeft] = pwr;
	motor[mFrontLeft] = pwr;
}

void rDrive(int pwr){
	motor[mBackRight] = pwr;
	motor[mFrontRight] = pwr;
}

void Base(){
	lDrive(LeftJoyMV);
	rDrive(RightJoyMV);
}

void Lift(){
	motor[mLiftLeft] = PowerCap(vexRT[Btn6U]*127 + vexRT[Btn6D]*-127);
	motor[mLiftRight] = PowerCap(vexRT[Btn6U]*127 + vexRT[Btn6D]*-127);
}

void Cone(){
	motor[mClaw] = PowerCap(vexRT[Btn7U]*127 + vexRT[Btn7D]*-127);
	motor[mChainbar] = PowerCap(vexRT[Btn5U]*127 + vexRT[Btn5D]*-127);
}

void Control() {
	Base();
	Lift();
	Cone();
}

void pre_auton()
{
	bStopTasksBetweenModes = true;
}

task usercontrol(){
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
	motor[port9] = 0;
	motor[port10] = 0;
	while (true){
		Variables();
		Control();
	}
}