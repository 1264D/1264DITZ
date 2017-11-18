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
int clawAngle; //Requested angle for claw
int clawOpen; //Potentiometer value of when the claw is open
int clawClose; //Potentiometer Value if when the claw is closed
string batteryMain; //String for lcd
string batteryPowerExpander; //String for lcd


int JoyClear(int origVal) { //intake current joystick position
	if(abs(origVal) < 15){ // if joystick is close to still just return 0
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
	motor[mLeftTop] = pwr;
	motor[mLeftBottom] = pwr;
	//Set left motors to a certain power
}

void rDrive(int pwr){//intake power
	motor[mRightTop] = pwr;
	motor[mRightBottom] = pwr;
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
	motor[mChainbar] = PowerCap(RightJoySV);
}

void Control() {//consolidate control
	Mobile();
	Base();
	Lift();
	Cone();
}

void reset(int sensor){ //intakes number associated with sensor or combination and resets those variables (set to 0)
	//1 = gBase1
	//2 = gLift2
	//3 = gMobile3
	//6 = Gyros
	//7 = qLeftDrive
	//8 = qRightDrive
	//15 = Quadratures
	//0 = All Sensors
	switch(sensor){
	case 0:
		SensorValue[gBase1] = 0;
		SensorValue[gLift2] = 0;
		SensorValue[gMobile3] = 0;
		SensorValue[qLeftDrive7] = 0;
		SensorValue[qRightDrive8] = 0;
		break;
	case 1:
		SensorValue[gBase1] = 0;
		break;
	case 2:
		SensorValue[gLift2] = 0;
		break;
	case 3:
		SensorValue[gMobile3] = 0;
		break;
	case 6:
		SensorValue[gBase1] = 0;
		SensorValue[gLift2] = 0;
		SensorValue[gMobile3] = 0;
		break;
	case 7:
		SensorValue[qLeftDrive7] = 0;
		break;
	case 8:
		SensorValue[qRightDrive8] = 0;
		break;
	case 11:
		SensorValue[qLeftDrive7] = 0;
		SensorValue[qRightDrive8] = 0;
		break;
	default:
		break;
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
	reset(0);
	//reset motors
	while(true){
		Variables(); //configure variables
		Control();//set control
	}
}
