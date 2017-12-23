int moveDir;
int liftDir;
int turnDir;
int autonNumber;
bool mobileOut;
int timer;

int oldQuadValue;
int disDiff;
int CMV;
int NMV;
int motDiff;
void mobile(int pwr, int angle){
	timer = nSysTime;
	if(mobileOut == false){
		while(SensorValue[gMobile2] > -angle && nSysTime - timer <= 1000){
			motor[mMobileLeft] = -pwr;
			motor[mMobileRight] = -pwr;
		}
		mobileOut = true;
	}
	else if(mobileOut == true){
		while(SensorValue[gMobile2] < angle && SensorValue[tMobileUp] == 0 && nSysTime - timer <= 1000){
			motor[mMobileLeft] = pwr;
			motor[mMobileRight] = pwr;
		}
		mobileOut = false;
	}
	motor[mMobileLeft] = 0;
	motor[mMobileRight] = 0;
	reset(2);
}

void turnG(int angle){
	if(angle < 0){
		turnDir = -1;
	}
	else{
		turnDir = 1;
	}
	while((angle < 0 && SensorValue[gBase1] < -angle) || (angle > 0 && SensorValue[gBase1] > -angle)){
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
	while((dis < 0 && SensorValue
		[qLeftDrive5] >= dis && qRightCorrected >= dis) ||
		(dis > 0 && SensorValue[qLeftDrive5] <= dis && qRightCorrected <= dis)){
		lDrive(127*moveDir);
		rDrive(127*-moveDir);
	}
	lDrive(0);
	rDrive(0);
	reset(11);
}

void dr4b(int angle, int pwr){
	if(angle < SensorValue[pLift]){
		liftDir = -1;
	}
	else{
		liftDir = 1;
	}
	while((angle > SensorValue[pLift] && SensorValue[pLift] < angle) || (angle < SensorValue[pLift] && SensorValue[pLift] > angle)){
		motor[mLiftLeft] = pwr*liftDir;
		motor[mLiftRight] = pwr*liftDir;
	}
	motor[mLiftLeft] = 0;
	motor[mLiftRight] = 0;
}

void drive(int dis, int Lpwr, int Rpwr){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while(((dis > 0 && SensorValue[qLeftDrive5] <= dis && SensorValue[qRightDrive6] >= -dis) ||
		(dis < 0 && SensorValue[qLeftDrive5] >= dis && SensorValue[qRightDrive6] <= -dis))){
		lDrive(Lpwr*moveDir);
		rDrive(Rpwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
	reset(11);
}

void driveMobile(int dis, int Lpwr, int Rpwr){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while(((dis > 0 && SensorValue[qLeftDrive5] <= dis && SensorValue[qRightDrive6] >= -dis) ||
		(dis < 0 && SensorValue[qLeftDrive5] >= dis && SensorValue[qRightDrive6] <= -dis)) &&
	(SensorValue[lMobile] >= 2000)){
		lDrive(Lpwr*moveDir);
		rDrive(Rpwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
	reset(11);
}

void PIDmove(int dis, int pwr){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	oldQuadValue = SensorValue[qLeftDrive5];
	CMV = pwr*moveDir;
	while(((dis < 0 && SensorValue[qLeftDrive5] >= dis && qRightCorrected <= dis) ||
		(dis > 0 && SensorValue[qLeftDrive5] <= dis && qRightCorrected >= dis))){
		disDiff = SensorValue[qLeftDrive5] + oldQuadValue;
		motDiff = (pwr - 0)/dis*disDiff;
		NMV = CMV - motDiff;
		lDrive(NMV);
		rDrive(NMV);
		CMV = NMV;
		oldQuadValue = SensorValue[qLeftDrive5];
	}
}

void PIDmoveMobile(int dis,int pwr){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	oldQuadValue = SensorValue[qLeftDrive5];
	CMV = pwr*moveDir;
	while(((dis < 0 && SensorValue[qLeftDrive5] >= dis && qRightCorrected <= dis) ||
		(dis > 0 && SensorValue[qLeftDrive5] <= dis && qRightCorrected >= dis)) &&
	(SensorValue[lMobile] >= 2000)){
		disDiff = SensorValue[qLeftDrive5] + oldQuadValue;
		motDiff = (pwr - 0)/dis*disDiff;
		NMV = CMV - motDiff;
		lDrive(NMV);
		rDrive(NMV);
		CMV = NMV;
		oldQuadValue = SensorValue[qLeftDrive5];
	}
}

void PIDturnG(int angle, int pwr){
	if(angle < 0){
		turnDir = -1;
	}
	else{
		turnDir = 1;
	}
	while((angle < 0 && SensorValue[gBase1] > angle) || (angle > 0 && SensorValue[gBase1] < angle)){
		disDiff = SensorValue[qLeftDrive5] + oldQuadValue;
		motDiff = (pwr - 0)/angle*disDiff;
		NMV = CMV - motDiff;
		lDrive(NMV*turnDir);
		rDrive(NMV*-turnDir);
		CMV = NMV;
		oldQuadValue = SensorValue[qLeftDrive5];
	}
	rDrive(0);
	lDrive(0);
	reset(11);
}

void PIDturnQ(int dis, int pwr){
	if(dis > 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while((dis < 0 && SensorValue[qLeftDrive5] >= dis && qRightCorrected >= dis) ||
		(dis > 0 && SensorValue[qLeftDrive5] <= dis && qRightCorrected <= dis)){
		disDiff = SensorValue[qLeftDrive5] + oldQuadValue;
		motDiff = (pwr - 0)/dis*disDiff;
		NMV = CMV - motDiff;
		lDrive(NMV*moveDir);
		rDrive(NMV*-moveDir);
		CMV = NMV;
		oldQuadValue = SensorValue[qLeftDrive5];
	}
	lDrive(0);
	rDrive(0);
	reset(11);
}

void Auton1(){ //stationary auton
	drive(225,80,80);
	wait1Msec(250);
	motor[mClaw] = 70;
	dr4b(3700,127);
	motor[mLiftLeft] = 127;
	motor[mLiftRight] = 127;
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
	motor[mClaw] = 127;
	mobile(100,800);
	motor[mClaw] = 0;
	driveMobile(-1600,127,100);
	mobile(127,700);
	drive(1000,127,100);
	turnG(1300);
	drive(-1000,127,100);
	turnG(900);
	drive(-1000,127,100);
	mobile(100, 400);
	drive(400,127,100);

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
	motor[mClaw] = 127;
	mobile(100,800);
	motor[mClaw] = 0;
	driveMobile(-1600,127,100);
	mobile(127,700);
	drive(1000,127,100);
	turnG(-1300);
	drive(-1000,127,100);
	turnG(-900);
	drive(-1000,127,100);
	mobile(100, 400);
	drive(400,127,100);
	//Lift Up
	//Lower mobile
	//Drive forward
	//inkate mogo
	//turn around
	//drive forward
	//dump mobile
	//back up
}

void Auton4(){
	motor[mClaw] = 70;
	dr4b(2400,127);
	mobile(100,800);
	motor[mClaw] = 0;
	driveMobile(-1600,127,100);
	mobile(127,700);
	motor[mClaw] = 70;
	drive(1300,127,100);
	motor[mClaw] = 0;
	turnG(2100);
	mobile(100,800);
	drive(400,127,100);
	mobile(127,700);
	dr4b(2800,127);
	motor[mClaw] = 80;
	drive(-200,85,80);
	turnG(2100);
	drive(200,85,80);
	motor[mClaw] = 0;
	dr4b(2800,80);
	motor[mClaw] = -80;
	drive(-100,127,100);
	motor[mClaw] = 0;
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
		break;
	case 3:
		Auton3();
		break;
	case 4:
		Auton4();
	default:
		break;
	}
}

task autonomous(){
	autonNumber = 0;
	reset(0);
	mobileOut = false;
	autonSelecter();
}
