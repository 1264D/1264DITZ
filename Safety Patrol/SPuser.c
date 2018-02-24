int RightJoyMV; //Main Right Y
int RightJoySV; //Partner Right Y
int LeftJoyMV;  //Main Left Y
int LeftJoySV;  //Partner Left Y
int LeftJoyMH; //Main Left X
int LeftJoySH; //Partner Left X
int RightJoyMH; //Main Right X
int RightJoySH; //Partner Right X
int coneStack = 0; //How many cones are currently in the stack
static int liftMobileAngle = 2400;
int rollerPassive = 30;

string batteryMain; //String for lcd
int batteryMainDoub;
int autonNumber;
string batteryPowerExpander; //String for lcd
string autonString;
string autonName;
float basePower = 1.0;
int baseToggle;
int barBurnout;
bool mobileDisable = true;
bool liftDisable = false;


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
	motor[mLeftFront] = pwr;
	motor[mLeftBack] = pwr;
	//Set left motors to a certain power
}

void rDrive(int pwr){//intake power
	motor[mRightTop] = pwr;
	motor[mRightFront] = pwr;
	motor[mRightBack] = pwr;
	//Set right motors to a certain power
}

void Base(){//Configure base control joysticks
	if(vexRT[Btn7U] == 1){
		waitUntil(vexRT[Btn7U] == 0);
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
	motor[mLift] = PowerCap(LeftJoySV + vexRT[Btn6D]*127*liftDisable + vexRT[Btn6U]*127*liftDisable);
	//lift is controlled by right bumpers
}

void Mobile(){//configure mobile goal intake control
	if(SensorValue[pLift2] < liftMobileAngle){
		mobileDisable = false;
		liftDisable = true;
	}
	else{
		mobileDisable = true;
		liftDisable = false;
	}
	motor[mMobile] = PowerCap((vexRT[Btn6D]*70*mobileDisable + vexRT[Btn6U]*-127*mobileDisable + vexRT[Btn6D]*57*SensorValue[jAuton1]*SensorValue[jAuton2]*SensorValue[jAuton4]*SensorValue[jAuton8]) + vexRT[Btn7L]*127 + vexRT[Btn7R]*-127 + vexRT[Btn7D]*70);
}

void Cone(){//configure claw and chainbar control
	motor[mClaw] = PowerCap(vexRT[Btn6DXmtr2]*-157 + vexRT[Btn6UXmtr2]*97 + rollerPassive);//claw motion is controlled via right d-pad
	if(RightJoySV <= -50 && SensorValue[p4Bar] <= 1650 && SensorValue[p4Bar] >= 1400 ){
		barBurnout = 1;
	}
	else{
		barBurnout = 0;
	}
	motor[mChainbar] = PowerCap(RightJoySV + 70*barBurnout);
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
	//4 = gChainbar4
	//10 = Gyros
	//11 = qLeftDrive
	//12 = qRightDrive
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
	case 3: //DO NOT RESET
		SensorValue[gMobile3] = 0;
		break;
	case 4:
		SensorValue[gBase1] = 0;
		SensorValue[gMobile3] = 0;
		break;
	case 11:
		SensorValue[qLeftDrive11] = 0;
		break;
	case 12:
		SensorValue[qRightDrive12] = 0;
		break;
	case 23:
		SensorValue[qLeftDrive11] = 0;
		SensorValue[qRightDrive12] = 0;
		break;
	default:
		break;
	}
}

void autonRead(){
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
	if(SensorValue[jAuton16] == true){
		autonNumber += 16;
	}
}

void lcd(){
	batteryMainDoub = nAvgBatteryLevel/100;
	batteryMain = batteryMainDoub;
	displayLCDString(0,0,batteryMain);
	if(nLCDButtons > 0){
		autonNumber = 0;
		autonRead();
		clearLCDLine(1);
		autonString = autonNumber;
		displayLCDCenteredString(0, "Auton: ");
		displayNextLCDString(autonString);
		switch(autonNumber){
	case 0: //test
		autonName = "Test Autonomous";
		break;
	case 2: //mogo 20 left 3
		autonName = "20P Left 3C";
		break;
	case 3: //trick 20 left 3
		autonName = "Tr 20P Left 3C";
		break;
	case 4: //mogo 20 right 3
		autonName = "20P Right 3C";
		break;
	case 5://trick 20 right 3
		autonName = "Tr 20P Right 3C";
		break;
	case 6://mogo 10 left 3
		autonName = "10P Left 3C";
		break;
	case 7://trick 10 left 3
		autonName = "Tr 10P Left 3C";
		break;
	case 8://mogo 10 right 3
		autonName = "10P Right 3C";
		break;
	case 9://trick 10 right 3
		autonName = "Tr 10P Right 3C";
		break;
	case 10://mogo 5 left 3
		autonName = "5P Left 3C";
		break;
	case 11://trick 5 left 3
		autonName = "Tr 5P Left 3C";
		break;
	case 12://mogo 5 right 3
		autonName = "5P Right 3C";
		break;
	case 13://trick 5 right 3
		autonName = "Tr 5P Right 3C";
		break;
	case 14://stationary left
		autonName = "Station Left";
		break;
	case 15: //trick stationary left
		autonName = "Tr Station Left";
		break;
	case 16: //stationary right
		autonName = "Station Right";
		break;
	case 17: //trick stationary right
		autonName = "Tr Station Right";
		break;
	case 18: //mogo 20 left 2
		autonName = "20P Left 2C";
		break;
	case 19: //trick 20 left 2
		autonName = "Tr 20P Left 2C";
		break;
	case 20: //mogo 20 right 2
		autonName = "20P Right 2C";
		break;
	case 21: //trick 20 right 2
		autonName = "Tr 20P Right 2C";
		break;
	case 22: //mogo 10 left 2
		autonName = "10P Left 2C";
		break;
	case 23: //trick 10 left 2
		autonName = "Tr 10P Left 2C";
		break;
	case 24: //mogo 10 right 2
		autonName = "10P Right 2C";
		break;
	case 25: //trick 10 right 2
		autonName = "Tr 10P Right 2C";
		break;
	case 26: //mogo 5 left 2
		autonName = "5P Left 2C";
		break;
	case 27: //trick 5 left 2
		autonName = "Tr 5P Left 2C";
		break;
	case 28: //mogo 5 right 2
		autonName = "5P Right 2C";
		break;
	case 29: //trick 5 right 2
		autonName = "Tr 5P Right 2C";
		break;
	case 31: //pragma skills
		autonName = "Pragma Skills";
		break;
	}
		displayLCDCenteredString(1, autonName);
	}
}
