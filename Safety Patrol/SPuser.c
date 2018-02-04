int RightJoyMV; //Main Right Y
int RightJoySV; //Partner Right Y
int LeftJoyMV;  //Main Left Y
int LeftJoySV;  //Partner Left Y
int LeftJoyMH; //Main Left X
int LeftJoySH; //Partner Left X
int RightJoyMH; //Main Right X
int RightJoySH; //Partner Right X
int coneStack = 0; //How many cones are currently in the stack
int chainAngle;
int liftHeight; //Requested angle for lift
static int liftMobileAngle = 2400;

string batteryMain; //String for lcd
int batteryMainDoub;
int autonNumber;
string batteryPowerExpander; //String for lcd
string autonString;
string autonName;
float basePower = 1.0;
int baseToggle;
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

void OneDriverBase(){//For Clarkston - main joysticks, 8L is half-power toggle
	if(vexRT[Btn8L] == 1){
		waitUntil(vexRT[Btn8L] == 0);
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
	motor[mLift] = PowerCap(LeftJoySV);
	//lift is controlled by right bumpers
}

void OneDriverLift(){//For Clarkston - Left bumpers, 7L does half power
	motor[mLift] = PowerCap((vexRT[Btn5D]*-127 + vexRT[Btn5U]*127) * (1 - 0.5*vexRT[Btn7L]) );
	//lift is controlled by left bumpers
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
	motor[mMobile] = PowerCap((vexRT[Btn6D]*70 + vexRT[Btn6U]*-127) + vexRT[Btn7L]*127 + vexRT[Btn7R]*-127 + vexRT[Btn7D]*70);
}

void OneDriverMobile(){//For Clarkston - Mobile Goal Intake Control
	motor[mMobile] = PowerCap(vexRT[Btn6D]*70 + vexRT[Btn6U]*-127 + vexRT[Btn8R]*127);
}

void Cone(){//configure claw and chainbar control
	motor[mClaw] = PowerCap(vexRT[Btn6DXmtr2]*-147 + vexRT[Btn6UXmtr2]*107 + 20);//claw motion is controlled via right d-pad
	motor[mChainbar] = PowerCap(RightJoySV);
}

void OneDriverCone(){//For Clarkston - Roller & 4-bar Control
	motor[mClaw] = PowerCap(vexRT[Btn7D]*-147 + vexRT[Btn7U]*107 + 20);//claw motion is controlled via left d-pad, idles at 20 power in
	motor[mChainbar] = PowerCap(vexRT[Btn8U]*127 + vexRT[Btn8D]*-127); //Chainbar by left bumpers, U->up, D->down
}

void Control() {//consolidate control
	if(SensorValue[jAuton8] == false){
		Mobile();
		Base();
		Lift();
		Cone();
	} else {
		OneDriverMobile();
		OneDriverLift();
		OneDriverBase();
		OneDriverCone();
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
		break;
	case 3: //DO NOT RESET
		SensorValue[gMobile3] = 0;
		break;
	case 4: //DO NOT RESET
		SensorValue[gChainbar4] = 0;
		break;
	case 10: //DO NOT RESET
		SensorValue[gBase1] = 0;
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
//	if(SensorValue[jAuton8] == true){
//		autonNumber += 8;
//	}
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
		case 0:
			autonName = "disabled";
			break;
		case 1:
			autonName = "Center Station.";
			break;
		case 2:
			autonName = "Side Station.";
			break;
		case 3:
			autonName = "Left Mobile 20";
			break;
		case 4:
			autonName = "Right Mobile 20";
			break;
		case 5:
			autonName = "Left Mobile 10";
			break;
		case 6:
			autonName = "Right Mobile 10";
			break;
		case 7:
			autonName = "Pragma Skills";
			break;
		default:
			autonName = "disabled";
			break;
		}
		displayLCDCenteredString(1, autonName);
	}
}
