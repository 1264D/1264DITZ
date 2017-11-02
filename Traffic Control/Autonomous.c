int moveDir;
int liftDir;
int turnDir;
int turnAngle;
int autonNumber;
bool mobileOut;
int timer;
void mobile(int pwr, int angle){
	timer = nSysTime;
	if(mobileOut == false){
		while(SensorValue[gMobile] > -angle && nSysTime - timer <= 1000){
			motor[mMobileLeft] = -pwr;
			motor[mMobileRight] = -pwr;
		}
		mobileOut = true;
	}
	else if(mobileOut == true){
		while(SensorValue[gMobile] < angle && SensorValue[tMobileUp] == 0 && nSysTime - timer <= 1000){
			motor[mMobileLeft] = pwr;
			motor[mMobileRight] = pwr;
		}
		mobileOut = false;
	}
	motor[mMobileLeft] = 0;
	motor[mMobileRight] = 0;
	SensorValue[gMobile] = 0;
}

void turn1(int angle){
	if(angle < 0){
		turnDir = -1;
	}
	else{
		turnDir = 1;
	}
	while((angle < 0 && SensorValue[gBase] > angle) || (angle > 0 && SensorValue[gBase] < angle)){
		lDrive(127*turnDir);
		rDrive(127*-turnDir);
	}
	wait1Msec(250);
	if(SensorValue[gBase] != angle){
		if(abs(SensorValue[gBase]) < abs(angle)){
			turnDir = turnDir;
		}
		else{
			turnDir = -turnDir;
		}
		while((angle < 0 && SensorValue[gBase] < angle) || (angle > 0 && SensorValue[gBase] > angle)){
			lDrive(50*turnDir);
			rDrive(50*-turnDir);
		}
	}
	rDrive(0);
	lDrive(0);
}

void turn2(int dis){
	turnAngle = dis;
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while((dis < 0 && SensorValue[qLeftDrive] > dis /*&& SensorValue[qRightDrive] > dis*/) || (dis > 0 && SensorValue[qLeftDrive] < dis /*&& SensorValue[qRightDrive] < dis*/)){
		lDrive(127*moveDir);
		rDrive(127*-moveDir);
	}
	/*wait1Msec(250);
	if(SensorValue[gBase] != turnAngle){
	if(abs(SensorValue[gBase]) < abs(turnAngle)){
	turnDir = turnDir;
	}
	else{
	turnDir = -turnDir;
	}
	while((turnAngle < 0 && SensorValue[gBase] < turnAngle) || (turnAngle > 0 && SensorValue[gBase] > turnAngle)){
	lDrive(50*turnDir);
	rDrive(50*-turnDir);
	}
	} */
	lDrive(0);
	rDrive(0);
	SensorValue[qLeftDrive] = 0;
}
void dr4b(int angle, int pwr){
	if(angle < 0){
		liftDir = -1;
	}
	else{
		liftDir = 1;
	}
	while((angle > 0 && SensorValue[pLift] < angle) || (angle < 0 && SensorValue[pLift] > angle)){
		motor[mLiftLeft] = pwr*liftDir;
		motor[mLiftRight] = pwr*liftDir;
	}
	motor[mLiftLeft] = 0;
	motor[mLiftRight] = 0;
}
/*void reseter(string sensor){
if(sensor == "gLift"){
SensorValue[gLift] = 0;
}
else if(sensor == "gBase"){
SensorValue[gBase] = 0;
}
else if(sensor == "gyros"){
SensorValue[gBase] = 0;
SensorValue[gLift] = 0;
}

else if(sensor == "qLeftDrive"){
SensorValue[qLeftDrive] = 0;
}
else if(sensor == "qRightDrive"){
SensorValue[qRightDrive] = 0;
}
else if(sensor == "quadatures"){
SensorValue[qLeftDrive] = 0;
SensorValue[qRightDrive] = 0;
}

else if(sensor == "all"){
SensorValue[qLeftDrive] = 0;
SensorValue[qRightDrive] = 0;
SensorValue[gBase] = 0;
SensorValue[gLift] = 0;
}
} */

void drive(int dis, int Lpwr, int Rpwr){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while(((dis < 0 && SensorValue[qLeftDrive] >= dis /*&& SensorValue[qRightDrive] <= dis*/) ||
		(dis > 0 && SensorValue[qLeftDrive] <= dis /*&& SensorValue[qRightDrive] >= dis*/))){
		lDrive(Lpwr*moveDir);
		rDrive(Rpwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
	SensorValue[qLeftDrive] = 0;
	SensorValue[qRightDrive] = 0;
}

void driveMobile(int dis, int Lpwr, int Rpwr){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while(((dis < 0 && SensorValue[qLeftDrive] >= dis /*&& SensorValue[qRightDrive] <= dis*/) ||
		(dis > 0 && SensorValue[qLeftDrive] <= dis /*&& SensorValue[qRightDrive] >= dis*/)) &&
	(SensorValue[lMobile] >= 2000)){
		lDrive(Lpwr*moveDir);
		rDrive(Rpwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
	SensorValue[qLeftDrive] = 0;
	SensorValue[qRightDrive] = 0;
}

void Auton1(){ //stationary auton
	drive(225,80,80);
	wait1Msec(250);
	dr4b(3700,127);
	motor[mLiftLeft] = 127;
	motor[mLiftRight] = 127;
	motor[mClaw] = 70;
	wait1Msec(500);
	motor[mClaw] = -70;
	wait1Msec(500);
	motor[mClaw] = 0;
	drive(-100,80,80);
	motor[mLiftLeft] = 0;
	motor[mLiftRight] = 0;
}

void Auton2(){ //left mogo auton
	dr4b(2400,127);
	mobile(100,800);
	driveMobile(-1600,127,100);
	mobile(127,700);
	drive(1000,127,100);
	turn2(-610);
	drive(-1000,127,100);
	drive(-420,127,0);
	drive(-100,127,100);
	mobile(75, 400);
	drive(400,127,100);
	SensorValue[gMobile] = 0;
	//Lift Up
	//Lower mobile
	// drive forward
	//inkate mogo
	//turn around
	//drive forward
	//dump mobile
	//back up
}

void Auton3(){
	dr4b(2400,127);
	mobile(100,800);
	driveMobile(-1600,127,100);
	mobile(127,700);
	drive(1000,127,100);
	turn2(720);
	drive(-800,127,100);
	while(SensorValue[qRightDrive] <= 500){
		rDrive(127);
	}
	SensorValue[qRightDrive] = 0;
	rDrive(0);
	drive(-100,127,100);
	mobile(75, 400);
	drive(400,127,100);
	SensorValue[gMobile] = 0;
	//Lift Up
	//Lower mobile
	// drive forward
	//inkate mogo
	//turn around
	//drive forward
	//dump mobile
	//back up
}
void autonSelecter(){
	if(SensorValue[jAuton1] == true){
		autonNumber += 1;
	}
	if(SensorValue[jAuton2] == true){
		autonNumber += 2;
	}
	if(SensorValue[jAuton3] == true){
		autonNumber += 4;
	}
	if(SensorValue[jAuton4] == true){
		autonNumber += 8;
	}
	switch(autonNumber){
	case 0: //none
		break;
	case 1:
		Auton1();
		break;
	case 2:
		Auton2();
	case 3:
		Auton3();
	default:
		break;
	}
}

task autonomous(){
	autonNumber = 0;
	SensorValue[qLeftDrive] = 0;
	SensorValue[qRightDrive] = 0;
	SensorValue[gBase] = 0;
	SensorValue[gMobile] = 0;
	mobileOut = false;
	autonSelecter();
}
