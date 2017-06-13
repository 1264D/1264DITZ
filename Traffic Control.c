#pragma config(Sensor, in1,    sLeftLift,      sensorPotentiometer)
#pragma config(Sensor, in2,    sRightLift,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  sMobile1,       sensorDigitalOut)
#pragma config(Sensor, dgtl2,  sMobile2,       sensorDigitalOut)
#pragma config(Sensor, dgtl3,  sLeftDrive,     sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  sRightDrive,    sensorQuadEncoder)
#pragma config(Motor,  port1,            ,             tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

void pre_auton(){
  bStopTasksBetweenModes = true;
}

task autonomous(){
  AutonomousCodePlaceholderForTesting();
}

task usercontrol(){

  while (true){
    UserControlCodePlaceholderForTesting();
  }
}
