#pragma config(Sensor, in1,    pLift,          sensorPotentiometer)
#pragma config(Sensor, in2,    gLift,          sensorGyro)
#pragma config(Sensor, in3,    lMobile,        sensorLineFollower)
#pragma config(Sensor, in4,    pClaw,          sensorPotentiometer)
#pragma config(Sensor, in5,    gBase,          sensorGyro)
#pragma config(Sensor, in6,    lLeft,          sensorLineFollower)
#pragma config(Sensor, in7,    lMiddle,        sensorLineFollower)
#pragma config(Sensor, in8,    lRight,         sensorLineFollower)
#pragma config(Sensor, dgtl1,  qLeftDrive,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  qRightDrive,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  tLiftDown,      sensorTouch)
#pragma config(Sensor, dgtl6,  tMobileDown,    sensorTouch)
#pragma config(Sensor, dgtl7,  tMobileUp,      sensorTouch)
#pragma config(Sensor, dgtl9,  jAuton4,        sensorTouch)
#pragma config(Sensor, dgtl10, jAuton3,        sensorTouch)
#pragma config(Sensor, dgtl11, jAuton2,        sensorTouch)
#pragma config(Sensor, dgtl12, jAuton1,        sensorTouch)
#pragma config(Motor,  port1,           mMobileLeft,   tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           mFrontRight,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           mFrontLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mLiftRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           mClaw,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           mChainbar,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           mLiftLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mBackLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           mBackRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          mMobileRight,  tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"


int RightJoyMV; //Main Right Y
int RightJoySV; //Partner Right Y
int LeftJoyMV;  //Main Left Y
int LeftJoySV;  //Partner Left Y
int LeftJoyMH; //Main Left X
int LeftJoySH; //Partner Left X
int RightJoyMH; //Main Right X
int RightJoySH; //Partner Right X
int coneStack; //How many cones are currently in the stack
int liftHeight; //Requested angle for lift
int chainAngle; //Requested angle for chainbar
int clawAngle; //Requested angle for claw
int clawOpen; //Potentiometer value of when the claw is open
int clawClose; //Potentiometer Value if when the claw is closed
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

void lDrive(int pwr){//intake power
	motor[mBackLeft] = pwr;
	motor[mFrontLeft] = pwr;
	//Set left motors to a certain power
}

void rDrive(int pwr){//intake power
	motor[mBackRight] = pwr;
	motor[mFrontRight] = pwr;
	//Set right motors to a certain power
}

void Base(){//Configure base control joysticks
	lDrive(LeftJoyMV);//Left wheels are controlled by left joystick
	rDrive(RightJoyMV);//Right wheels are controlled by right joystick
}

void Lift(){//configure lift control
	motor[mLiftLeft] = PowerCap(LeftJoySV);
	motor[mLiftRight] = PowerCap(LeftJoySV);
	//lift is controlled by right bumpers
}

void Mobile(){//configure mobile goal intake control
	motor[mMobileLeft] = PowerCap(vexRT[Btn6D]*127 + vexRT[Btn5D]*-70+ vexRT[Btn8R]*-127);
	motor[mMobileRight] = PowerCap(vexRT[Btn6D]*127 + vexRT[Btn5D]*-70+ vexRT[Btn8R]*-127);
}

void Cone(){//configure claw and chainbar control
	motor[mClaw] = PowerCap(vexRT[Btn5UXmtr2]*127 + vexRT[Btn6UXmtr2]*-127);//claw motion is controlled via right d-pad
}

void Control() {//consolidate control
	Mobile();
	Base();
	Lift();
	Cone();
}

#include "Autonomous.c"

void pre_auton(){
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
	SensorValue[qLeftDrive] = 0;
	SensorValue[qLeftDrive] = 0;
	//reset motors
	while(true){
		Variables(); //configure variables
		Control();//set control
	}
}

/*void stack(){//configure lift and chainbar angles based on how many cones are on the stack
coneStack++;// add one to stack
switch(coneStack){//How many cones are currently on the stack
case 1:liftHeight = 0; chainAngle = 0;
case 2:liftHeight = 0; chainAngle = 0;
case 3:liftHeight = 0; chainAngle = 0;
case 4:liftHeight = 0; chainAngle = 0;
case 5:liftHeight = 0; chainAngle = 0;
case 6:liftHeight = 0; chainAngle = 0;
case 7:liftHeight = 0; chainAngle = 0;
case 8:liftHeight = 0; chainAngle = 0;
case 9:liftHeight = 0; chainAngle = 0;
case 10:liftHeight = 0; chainAngle = 0;
case 11:liftHeight = 0; chainAngle = 0;
case 12:liftHeight = 0; chainAngle = 0;
case 13:liftHeight = 0; chainAngle = 0;
case 14:liftHeight = 0; chainAngle = 0;
case 15:liftHeight = 0; chainAngle = 0;
}
} */

/*void stackDriver(){//automated cone stacking
stack();//configure stack variables
while(SensorValue[gLift] < liftHeight && SensorValue[pChainbar] < chainAngle){ //move until the lift and chainbar are not at final positions
Base();
if(SensorValue[gLift] < liftHeight){//while lift is not at final position, move it
motor[mLiftLeft] = 127;
motor[mLiftRight] = 127;
}
else{
motor[mLiftLeft] = 0;
motor[mLiftRight] = 0;
}

if(SensorValue[pChainbar] < chainAngle){//while chainbar is not at final position, move it
motor[mChainbar] = 127;
}
else{
motor[mChainbar] = 0;
}
}
while(clawAngle < clawOpen){//open the claw/release the cone
Base();
motor[mClaw] = 127;
}
while(SensorValue[tLiftDown] != 1 && SensorValue[pChainbar] > 0){ // move the lift and chainbar back
if(SensorValue[tLiftDown] != 1){
Base();
motor[mLiftLeft] = -127;
motor[mLiftRight] = -127;
}
else{
motor[mLiftLeft] = 0;
motor[mLiftRight] = 0;
}
if(SensorValue[pChainbar] > 0){
motor[mChainbar] = 127;
}
else{
motor[mChainbar] = 0;
}
}
} */

/*void stackAuton(int lift, int chain){
stack();
while(SensorValue[gLift] < liftHeight && SensorValue[pChainbar] < chainAngle){
if(SensorValue[gLift] < liftHeight){
motor[mLiftLeft] = lift;
motor[mLiftRight] = lift;
}
else{

motor[mLiftLeft] = 0;
motor[mLiftRight] = 0;
}

if(SensorValue[pChainbar] < chainAngle){
motor[mChainbar] = chain;
}
else{
motor[mChainbar] = 0;
}
}
while(clawAngle < clawOpen){
motor[mClaw] = 127;
}
while(SensorValue[tLiftDown] != 1 && SensorValue[pChainbar] > 0){
if(SensorValue[tLiftDown] != 1){
motor[mLiftLeft] = -lift;
motor[mLiftRight] = -lift;
}
else{
motor[mLiftLeft] = 0;
motor[mLiftRight] = 0;
}
if(SensorValue[pChainbar] > 0){
motor[mChainbar] = chain;
}
else{
motor[mChainbar] = 0;
}
}
} */

/*void Mobile(){//configure mobile goal intake control
if(SensorValue[tMobileDown] == 1){//if intake is down, only let the motors go up
motor[mMobileLeft] = PowerCap(vexRT[Btn5U]*127);
motor[mMobileRight] = PowerCap(vexRT[Btn5U]*127);
if(coneStack != 0){//zero the stack
coneStack = 0;
}
}
else if(SensorValue[tMobileUp] == 1){//if intake is up, only let the motors go down
motor[mMobileLeft] = PowerCap(vexRT[Btn5D]*-127);
motor[mMobileRight] = PowerCap(vexRT[Btn5D]*-127);
}
else{//if it is inbetween, controllable both directions
motor[mMobileLeft] = PowerCap(vexRT[Btn5U]*127 + vexRT[Btn5D]*-127);
motor[mMobileRight] = PowerCap(vexRT[Btn5U]*127 + vexRT[Btn5D]*-127);
}
}*/
