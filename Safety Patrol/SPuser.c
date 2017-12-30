int RightJoyMV; //Main Right Y
int RightJoySV; //Partner Right Y
int LeftJoyMV;  //Main Left Y
int LeftJoySV;  //Partner Left Y
int LeftJoyMH; //Main Left X
int LeftJoySH; //Partner Left X
int RightJoyMH; //Main Right X
int RightJoySH; //Partner Right X
int coneStack; //How many cones are currently in the stack
int chainAngle;
int liftHeight; //Requested angle for lift
static int liftMobileAngle = 200;

string batteryMain; //String for lcd
string batteryPowerExpander; //String for lcd
float basePower = 1.0;
int baseToggle;


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
	if(vexRT[Btn8R] == 1){
		waitUntil(vexRT[Btn8R] == 0);
		if(baseToggle == true){
			baseToggle = false;
			basePower = 1.0;
		}
		else{
			baseToggle = true;
			basePower = 0.5;
		}
	}
	lDrive(LeftJoyMV*basePower);//Left wheels are controlled by left joystick
	rDrive(RightJoyMV*basePower);//Right wheels are controlled by right joystick
}

void Lift(){//configure lift control
	motor[mLiftLeft] = PowerCap(LeftJoySV);
	motor[mLiftRight] = PowerCap(LeftJoySV);
	//lift is controlled by right bumpers
}

void Mobile(){//configure mobile goal intake control
	if(SensorValue[gLift2] > liftMobileAngle){
		motor[mMobileLeft] = PowerCap(vexRT[Btn6D]*127 + vexRT[Btn5D]*-70+ vexRT[Btn8R]*-127);
		motor[mMobileRight] = PowerCap(vexRT[Btn6D]*127 + vexRT[Btn5D]*-70+ vexRT[Btn8R]*-127);
	}
	else{
		motor[mLiftLeft] = PowerCap(vexRT[Btn6D]*127 + vexRT[Btn5D]*-127);
		motor[mLiftRight] = PowerCap(vexRT[Btn6D]*127 + vexRT[Btn5D]*-127);
	}
}

void Cone(){//configure claw and chainbar control
	motor[mClaw] = PowerCap(vexRT[Btn6DXmtr2]*-50 + vexRT[Btn6UXmtr2]*50 + vexRT[Btn5UXmtr2]*127 + vexRT[Btn5DXmtr2]*-127);//claw motion is controlled via right d-pad
	motor[mChainbar] = PowerCap(RightJoySV);
}

void Control() {//consolidate control
	Mobile();
	Base();
	Lift();
	Cone();
}

void stack(){//configure lift and chainbar angles based on how many cones are on the stack
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
	}
}

void reset(int sensor){ //intakes number associated with sensor or combination and resets those variables (set to 0)
	//1 = gBase1
	//2 = gLift2
	//3 = gMobile3
	//4 = gChainbar4
	//10 = Gyros
	//11 = qLeftDrive
	//12 = qRightDrive
	//13 = qRollers
	//36 = Quadratures
	//0 = All Sensors
	switch(sensor){
	case 0:
		SensorValue[gBase1] = 0;
		SensorValue[qLeftDrive11] = 0;
		SensorValue[qRightDrive12] = 0;
		break;
	case 1:
		SensorValue[gBase1] = 0;
		break;
	case 2://DO NOT RESET
		SensorValue[gLift2] = 0;
		break;
	case 3: //DO NOT RESET
		SensorValue[gMobile3] = 0;
		break;
	case 4: //DO NOT RESET
		SensorValue[gChainbar4] = 0;
		break;
	case 10: //DO NOT RESET
		SensorValue[gBase1] = 0;
		SensorValue[gLift2] = 0;
		SensorValue[gMobile3] = 0;
		SensorValue[gChainbar4] = 0;
		break;
	case 11:
		SensorValue[qLeftDrive11] = 0;
		break;
	case 12:
		SensorValue[qRightDrive12] = 0;
		break;
	case 13:
		SensorValue[qRollers13] = 0;
		break;
	case 36:
		SensorValue[qLeftDrive11] = 0;
		SensorValue[qRightDrive12] = 0;
		SensorValue[qRollers13] = 0;
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
		if(vexRT[Btn7U] == 1){
		SensorValue[gBase1] = 0;
		SensorValue[gLift2] = 0;
		SensorValue[gMobile3] = 0;
		SensorValue[gChainbar4] = 0;
		SensorValue[qLeftDrive11] = 0;
		SensorValue[qRightDrive12] = 0;
		SensorValue[qRollers13] = 0;
		}
	}
}
