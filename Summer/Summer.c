#pragma config(Sensor, in1,    sLeftLift,      sensorPotentiometer)
#pragma config(Sensor, in2,    sRightLift,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  sMobile1,       sensorDigitalOut)
#pragma config(Sensor, dgtl2,  sMobile2,       sensorDigitalOut)
#pragma config(Sensor, dgtl3,  sLeftDrive,     sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  sRightDrive,    sensorQuadEncoder)
#pragma config(Sensor, dgtl12, sDriveDirection, sensorTouch)
#pragma config(Motor,  port1,           Chainbar,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           FrontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FrontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           TopLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           TopRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           BottomRight,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           BottomLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           BackLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           BackRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          Claw,          tmotorVex393_HBridge, openLoop)
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
string batteryMain; //String for lcd
string batteryPowerExpander; //String for lcd
bool mobileState = false;
int driveDirection = 1;


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

void lDrive(int pwr){
	motor[BackLeft] = pwr;
	motor[FrontLeft] = pwr;
}

void rDrive(int pwr){
	motor[BackRight] = pwr;
	motor[FrontRight] = pwr;
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

void Base(){
	lDrive(LeftJoyMV*driveDirection);
	rDrive(RightJoyMV*driveDirection);
}

void Lift(){
	motor[TopLeft] = PowerCap(vexRT[Btn6U]*127 + vexRT[Btn6D]*-127);
	motor[TopRight] = PowerCap(vexRT[Btn6U]*127 + vexRT[Btn6D]*-127);
	motor[BottomLeft] = PowerCap(vexRT[Btn6U]*127 + vexRT[Btn6D]*-127);
	motor[BottomRight] = PowerCap(vexRT[Btn6U]*127 + vexRT[Btn6D]*-127);
}

void Cone(){
	motor[Claw] = PowerCap(vexRT[Btn7U]*127 + vexRT[Btn7D]*-127);
	motor[Chainbar] = PowerCap(vexRT[Btn5U]*127 + vexRT[Btn5D]*-127);
}

void Goal(){
	if(mobileState == 0){
		waitUntil(vexRT[Btn8R] == 0);
		mobileState = true;
		SensorValue[sMobile1] = 1;
		SensorValue[sMobile2] = 1;
	}
	else if(mobileState == 1){
		waitUntil(vexRT[Btn8R] == 0);
		mobileState = false;
		SensorValue[sMobile1] = 0;
		SensorValue[sMobile2] = 0;
	}
}

void Control() {
	Base();
	Lift();
	Cone();
	Goal();
}
void pre_auton(){
	bStopTasksBetweenModes = true;
}

task autonomous(){
	while(SensorValue[sLeftDrive] < 200){
	motor[port1] = 127;
	}
	SensorValue[sLeftDrive] = 0;
	while(SensorValue[sLeftDrive] > -200){
 	motor[port2] = -127;
	}
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
	if(SensorValue[sDriveDirection] == 1) {
		driveDirection = -1;
	}
	else if(SensorValue[sDriveDirection] == 0) {
		driveDirection = 1;
}
	while (true){
		Variables();
		Control();
	}
}
