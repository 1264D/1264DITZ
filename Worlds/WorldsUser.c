int RightJoyMV; //Main Right Y
int RightJoySV; //Partner Right Y
int LeftJoyMV;  //Main Left Y
int LeftJoySV;  //Partner Left Y
int LeftJoyMH; //Main Left X
int LeftJoySH; //Partner Left X
int RightJoyMH; //Main Right X
int RightJoySH; //Partner Right X
static int liftMobileAngle = 3450;
int rollerPassive = 25;

string mainBattery, backupBattery, powerBattery; //String for lcd
int autonNumber;
string autonString, autonName;
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
	motor[mLeftMiddle] = PowerCap(pwr);
	motor[mLeftFront] = PowerCap(pwr);
	motor[mLeftBack] = PowerCap(pwr);
	//Set left motors to a certain power
}

void rDrive(int pwr){//intake power
	motor[mRightMiddle] = PowerCap(pwr);
	motor[mRightFront] = PowerCap(pwr);
	motor[mRightBack] = PowerCap(pwr);
	//Set right motors to a certain power
}

int baseGyroBuffer[5] = {SensorValue[gBase1], SensorValue[gBase1], SensorValue[gBase1], SensorValue[gBase1], SensorValue[gBase1]};
int baseGyroFilter() {
		int sum = 0;
		for(int i = 0; i < 4; i++) {
			baseGyroBuffer[i] = baseGyroBuffer[i+1];
			sum += baseGyroBuffer[i];
		}
		baseGyroBuffer[4] = SensorValue[gBase1];
		sum += baseGyroBuffer[4];
		return sum/5;
}

int liftPotBuffer[2] = {SensorValue[pLift2],SensorValue[pLift2]};
int liftPotFilter(){
		if(!(SensorValue[pLift2] - liftPotBuffer[1] >= 150)){
			liftPotBuffer[0] = liftPotBuffer[1];
			liftPotBuffer[1] = SensorValue[pLift2];
		}
		return liftPotBuffer[1];
}

void straightDrive(int power) {
	float deviation = 1.0*baseGyroFilter()/90;
	rDrive((int)((1.0-deviation)*power));
	lDrive((int)((1.0+deviation)*power));
}

void backStraightDrive(int power) {
	float deviation = 1.0*baseGyroFilter()/100;
	rDrive((int)((1.0+deviation)*power));
	lDrive((int)((1.0-deviation)*power));
}

void stopDrive() {
	lDrive(0);
	rDrive(0);
}

void Base(){//Configure base control joysticks
	if((LeftJoyMV != 0 && RightJoyMV != 0) || (vexRT[Btn5D] + vexRT[Btn5U] != 0) || (SensorValue[jAuton1]*SensorValue[jAuton2]*SensorValue[jAuton4]*SensorValue[jAuton8]*SensorValue[jAuton16] == 1)){
		rDrive(RightJoyMV);
		lDrive(LeftJoyMV);

		} else {
		rDrive(LeftJoyMV + RightJoyMV - (LeftJoyMH + RightJoyMH));
		lDrive(LeftJoyMV + RightJoyMV + (LeftJoyMH + RightJoyMH));
	}
}

void Lift(){//configure lift control
	motor[mLift] = PowerCap(LeftJoySV + vexRT[Btn6D]*127*liftDisable + vexRT[Btn6U]*127*liftDisable);
	//lift is controlled by right bumpers
}

void Mobile(){//configure mobile goal intake control
	if(SensorValue[pLift2] > liftMobileAngle){
		mobileDisable = false;
		liftDisable = true;
	}
	else{
		mobileDisable = true;
		liftDisable = false;
	}
	motor[mMobile] = PowerCap((vexRT[Btn6D]*70*mobileDisable + vexRT[Btn6U]*-127*mobileDisable + vexRT[Btn6D]*57*SensorValue[jAuton1]*SensorValue[jAuton2]*SensorValue[jAuton4]*SensorValue[jAuton8]*SensorValue[jAuton16]) + vexRT[Btn7L]*127 + vexRT[Btn7R]*-127 + vexRT[Btn7D]*70);
}

void Cone(){//configure claw and chainbar control
	motor[mRollers] = PowerCap(vexRT[Btn6DXmtr2]*-157 + vexRT[Btn6UXmtr2]*97 + rollerPassive);//claw motion is controlled via right d-pad
	if(RightJoySV <= -50 && SensorValue[p4Bar] >= 1000 && SensorValue[p4Bar] <= 1600){
		barBurnout = 1;
	}
	else{
		barBurnout = 0;
	}
	motor[m4Bar] = PowerCap(RightJoySV + 70*barBurnout);
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
	if(SensorValue[jAuton32] == true){
		autonNumber += 32;
	}
}

void lcd(){
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDString(0, 0, "M:");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');
	displayNextLCDString(mainBattery);

	displayNextLCDString(",PE:");
	sprintf(powerBattery, "%1.2f%c", SensorValue[PowerExpander]/280.0,'V');
	displayNextLCDString(powerBattery);

	displayLCDString(1, 0, "Backup: ");
	sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');
	displayNextLCDString(backupBattery);

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
		waitUntil(nLCDButtons == 0);
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
	bLCDBacklight = false;
	//reset motors
	while(true){
		Variables(); //configure variables
		Control();//set control
		lcd();
	}
}
