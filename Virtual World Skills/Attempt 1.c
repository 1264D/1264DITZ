#pragma config(Sensor, in1,    lLeft,          sensorReflection)
#pragma config(Sensor, in2,    lMiddle,        sensorReflection)
#pragma config(Sensor, in3,    lRight,         sensorReflection)
#pragma config(Sensor, in4,    pWrist,         sensorPotentiometer)
#pragma config(Sensor, in6,    gBase,          sensorGyro)
#pragma config(Sensor, dgtl1,  qBaseR,         sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  qBaseL,         sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  qLift,          sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  sBase,          sensorSONAR_cm)
#pragma config(Motor,  port1,           mFrontRight,   tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           mBackRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mFrontLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mBackLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           mClaw,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mLeftLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mRightLift,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//

int coneStack; //How many cones are currently in the stack
int liftHeight; //Requested angle for lift
int clawAngle; //Requested angle for claw
int moveDir;
int liftDir;
int turnDir;
int turnAngle;

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

void drive(int dis, int pwr){
	if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while((dis < 0 && SensorValue[qBaseL] > dis && SensorValue[qBaseR] > dis) || (dis > 0 && SensorValue[qBaseL] < dis && SensorValue[qBaseR] < dis)){
		lDrive(pwr*moveDir);
		rDrive(pwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
}

task main(){


}
