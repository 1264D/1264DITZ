#pragma config(Sensor, in1,    gBase1,         sensorGyro)
#pragma config(Sensor, in2,    gLift2,         sensorGyro)
#pragma config(Sensor, in3,    gMobile3,       sensorGyro)
#pragma config(Sensor, in4,    gChainbar4,     sensorGyro)
#pragma config(Sensor, in5,    lMobile,        sensorLineFollower)
#pragma config(Sensor, in6,    lRollers,       sensorLineFollower)
#pragma config(Sensor, dgtl1,  jAuton1,        sensorTouch)
#pragma config(Sensor, dgtl2,  jAuton2,        sensorTouch)
#pragma config(Sensor, dgtl3,  jAuton4,        sensorTouch)
#pragma config(Sensor, dgtl4,  jAuton8,        sensorTouch)
#pragma config(Sensor, dgtl7,  qRollers13,     sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  qRightDrive12,  sensorQuadEncoder)
#pragma config(Sensor, dgtl11, qLeftDrive11,   sensorQuadEncoder)
#pragma config(Motor,  port1,           mRightTop,     tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           mRightBottom,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           mMobileRight,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mLiftRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mClaw,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           mChainbar,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           mLiftLeft,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           mMobileLeft,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mLeftBottom,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          mLeftTop,      tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "SPuser.c"

int moveDir;
int liftDir;
int turnDir;
int autonNumber;
bool mobileOut;
int timer;

int oldQuadValue;
int disDiff;
float CMV;
float NMV;
float motDiff;

void mobile(int pwr, int angle){
	timer = nSysTime;
	if(mobileOut == false){
		while(SensorValue[gMobile3] > -angle && nSysTime - timer <= 1000){
			motor[mMobileLeft] = -pwr;
			motor[mMobileRight] = -pwr;
		}
		mobileOut = true;
	}
	else if(mobileOut == true){
		while(SensorValue[gMobile3] < angle && nSysTime - timer <= 1000){
			motor[mMobileLeft] = pwr;
			motor[mMobileRight] = pwr;
		}
		mobileOut = false;
	}
	motor[mMobileLeft] = 0;
	motor[mMobileRight] = 0;
	reset(3);
}

void turnG(int angle){
	if(angle < 0){
		turnDir = -1;
	}
	else{
		turnDir = 1;
	}
	while((angle < 0 && SensorValue[gBase1] > angle) || (angle > 0 && SensorValue[gBase1] < angle)){
		lDrive(127*turnDir);
		rDrive(127*-turnDir);
	}
	rDrive(0);
	lDrive(0);
	reset(0);
}

void turnQ(int dis){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while((dis < 0 && SensorValue[qLeftDrive11] >= dis && SensorValue[qRightDrive12] <= -dis) ||
		(dis > 0 && SensorValue[qLeftDrive11] <= dis && SensorValue[qRightDrive12] >= -dis)){
		lDrive(127*moveDir);
		rDrive(127*-moveDir);
	}
	lDrive(0);
	rDrive(0);
	reset(0);
}
void dr4b(int angle, int pwr){
	if(angle < 0){
		liftDir = -1;
	}
	else{
		liftDir = 1;
	}
	while((angle > 0 && SensorValue[gLift2] < angle) || (angle < 0 && SensorValue[gLift2] > angle)){
		motor[mLiftLeft] = pwr*liftDir;
		motor[mLiftRight] = pwr*liftDir;
	}
	motor[mLiftLeft] = 0;
	motor[mLiftRight] = 0;
}

void drive(int dis, int pwr){
	if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while((dis < 0 && SensorValue[qLeftDrive11] <= -dis && SensorValue[qRightDrive12] >= dis) ||
		(dis > 0 && SensorValue[qLeftDrive11] >= -dis && SensorValue[qRightDrive12] <= dis)){
		lDrive(pwr*moveDir);
		rDrive(pwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
	reset(36);
}

void driveMobile(int dis, int pwr){
	if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while(((dis > 0 && SensorValue[qLeftDrive11] <= -dis && SensorValue[qRightDrive12] >= dis) ||
		(dis < 0 && SensorValue[qLeftDrive11] >= -dis && SensorValue[qRightDrive12] <= dis)) && (SensorValue[lMobile] >= 2000)){
		lDrive(pwr*moveDir);
		rDrive(pwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
	reset(36);
}

void PIDmove(int dis, int pwr){
	if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	CMV = pwr*moveDir;
	NMV = CMV;
	timer = nSysTime;
	while((dis < 0 && SensorValue[qLeftDrive11] <= -dis && SensorValue[qRightDrive12] >= dis) ||
		(dis > 0 && SensorValue[qLeftDrive11] >= -dis && SensorValue[qRightDrive12] <= dis)){
		if(nSysTime - timer >= 100 && SensorValue[qLeftDrive11] >= dis*.75){
			disDiff = -(SensorValue[qLeftDrive11] - oldQuadValue);
			motDiff = (pwr*1.0-30)/(dis*.25)*disDiff;
			NMV = CMV - motDiff;
			oldQuadValue = SensorValue[qLeftDrive11];
			CMV = NMV;
			timer = nSysTime;
		}
		lDrive(NMV);
		rDrive(NMV);
	}
	reset(36);
	lDrive(0);
	rDrive(0);
	CMV = 0;
	NMV = 0;
	motDiff = 0;
	oldQuadValue = 0;
	motDiff = 0;
}

void PIDmoveMobile(int dis,int pwr){
	if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	oldQuadValue = SensorValue[qLeftDrive11];
	CMV = pwr*moveDir;
	timer = nSysTime;
	while(((dis < 0 && SensorValue[qLeftDrive11] <= -dis && SensorValue[qRightDrive12] >= dis) ||
		(dis > 0 && SensorValue[qLeftDrive11] >= -dis && SensorValue[qRightDrive12] <= dis)) && (SensorValue[lMobile] >= 2000)){
		if(nSysTime - timer >= 100 && SensorValue[qLeftDrive11] >= dis*.75){
			disDiff = -(SensorValue[qLeftDrive11] - oldQuadValue);
			motDiff = (pwr*1.0-30)/dis*disDiff;
			NMV = CMV - motDiff;
			oldQuadValue = SensorValue[qLeftDrive11];
			CMV = NMV;
			timer = nSysTime;
		}
		lDrive(NMV);
		rDrive(NMV);
	}
	reset(36);
	lDrive(0);
	rDrive(0);
	CMV = 0;
	NMV = 0;
	motDiff = 0;
	oldQuadValue = 0;
	motDiff = 0;
}

void PIDturnG(int angle, int pwr){
	if(angle < 0){
		turnDir = -1;
	}
	else{
		turnDir = 1;
	}
	oldQuadValue = SensorValue[qLeftDrive11];
	CMV = pwr*moveDir;
	timer = nSysTime;
	while((angle < 0 && SensorValue[gBase1] > angle) || (angle > 0 && SensorValue[gBase1] < angle)){
		if(nSysTime - timer >= 100 && SensorValue[qLeftDrive11] >= angle*.75){
			disDiff = -(SensorValue[qLeftDrive11] - oldQuadValue);
			motDiff = (pwr*1.0-30)/(angle*.25)*disDiff;
			NMV = CMV - motDiff;
			oldQuadValue = SensorValue[qLeftDrive11];
			CMV = NMV;
			timer = nSysTime;
		}
		lDrive(NMV);
		rDrive(NMV);
	}
	lDrive(0);
	rDrive(0);
	CMV = 0;
	NMV = 0;
	motDiff = 0;
	oldQuadValue = 0;
	motDiff = 0;
	reset(0);
}

void PIDturnQ(int dis, int pwr){
	if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	oldQuadValue = SensorValue[qLeftDrive11];
	CMV = pwr*moveDir;
	timer = nSysTime;
	while((dis < 0 && SensorValue[qLeftDrive11] <= -dis && SensorValue[qRightDrive12] >= dis) ||
		(dis > 0 && SensorValue[qLeftDrive11] >= -dis && SensorValue[qRightDrive12] <= dis)){
		if(nSysTime - timer >= 100 && SensorValue[qLeftDrive11] >= dis*.75){
			disDiff = -(SensorValue[qLeftDrive11] - oldQuadValue);
			motDiff = (pwr*1.0-30)/(dis*.25)*disDiff;
			NMV = CMV - motDiff;
			oldQuadValue = SensorValue[qLeftDrive11];
			CMV = NMV;
			timer = nSysTime;
		}
		lDrive(NMV);
		rDrive(NMV);
	}
	lDrive(0);
	rDrive(0);
	CMV = 0;
	NMV = 0;
	motDiff = 0;
	oldQuadValue = 0;
	motDiff = 0;
	reset(36);
}

void autonSelecter(){
	if(SensorValue[jAuton1] == true){
		autonNumber += 1;
	}
	if(SensorValue[jAuton2] == true){
		autonNumber += 2;
	}
	if(SensorValue[jAuton4] == true){
		autonNumber += 4;
	}
	if(SensorValue[jAuton8] == true){
		autonNumber += 8;
	}
	switch(autonNumber){
	case 0: //none
		break;
	default:
		break;
	}
}

void pre_auton(){
	bStopTasksBetweenModes = true;
}

task autonomous(){
	autonNumber = 0;
	reset(0);
	mobileOut = false;
	PIDmove(3000,90);
	//autonSelecter();
}