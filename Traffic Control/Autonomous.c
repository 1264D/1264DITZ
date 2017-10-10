int moveDir;
int liftDir;
int turnDir;
int turnAngle;


void Auton1(){


}

void stackAuton(int lift, int chain){
	stack();
	while(SensorValue[gLift] < liftHeight && SensorValue[pChainbar] < chainAngle){
		if(SensorValue[gLift] < liftHeight){
			motor[mLiftLeft] = lift;
			motor[mLiftRight] = lift;
		}
		else{
			motor[mLiftLeft] = 0;
			motor[mLiftRight] = 0;
		}

		if(SensorValue[pChainbar] < chainAngle){
			motor[mChainbar] = chain;
		}
		else{
			motor[mChainbar] = 0;
		}
	}
	while(clawAngle < clawOpen){
		motor[mClaw] = 127;
	}
	while(SensorValue[tLiftDown] != 1 && SensorValue[pChainbar] > 0){
		if(SensorValue[tLiftDown] != 1){
			motor[mLiftLeft] = -lift;
			motor[mLiftRight] = -lift;
		}
		else{
			motor[mLiftLeft] = 0;
			motor[mLiftRight] = 0;
		}
		if(SensorValue[pChainbar] > 0){
			motor[mChainbar] = chain;
		}
		else{
			motor[mChainbar] = 0;
		}
	}
}

void mobile(string pos, int pwr){
	if(SensorValue[tMobileUp] == 1){
		while(SensorValue[tMobileDown] != 0){
			motor[mMobileLeft] = -pwr;
			motor[mMobileRight] = -pwr;
		}
		motor[mMobileLeft] = 0;
		motor[mMobileRight] = 0;
	}
	else if(SensorValue[tMobileDown] == 1){
		while(SensorValue[tMobileUp] != 0){
			motor[mMobileLeft] = pwr;
			motor[mMobileRight] = pwr;
		}
		coneStack = 0;
		motor[mMobileLeft] = 0;
		motor[mMobileRight] = 0;
	}
	else{
		while(SensorValue[tMobileDown] != 0){
			motor[mMobileLeft] = -pwr;
			motor[mMobileRight] = -pwr;
		}
		coneStack = 0;
		motor[mMobileLeft] = 0;
		motor[mMobileRight] = 0;
	}
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
 if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while((dis < 0 && SensorValue[qLeftDrive] > dis && SensorValue[qRightDrive] > dis) || (dis > 0 && SensorValue[qLeftDrive] < dis && SensorValue[qRightDrive] < dis)){
		lDrive(127*moveDir);
		rDrive(127*moveDir);
	}
	wait1Msec(250);
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
	}
	lDrive(0);
	rDrive(0);
}
void dr4b(int angle, int pwr){
	if(angle < 0){
		liftDir = -1;
	}
	else{
		liftDir = 1;
	}
	while((angle > 0 && SensorValue[gLift] > angle) || (angle < 0 && SensorValue[gLift] < angle)){
		motor[mLiftLeft] = pwr*liftDir;
		motor[mLiftRight] = pwr*liftDir;
	}
	motor[mLiftLeft] = 0;
	motor[mLiftRight] = 0;
}
void reset(string sensor){
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
}

void drive(int dis, int pwr){
	if(dis < 0){
		moveDir = -1;
	}
	else{
		moveDir = 1;
	}
	while((dis < 0 && SensorValue[qLeftDrive] > dis && SensorValue[qRightDrive] > dis) || (dis > 0 && SensorValue[qLeftDrive] < dis && SensorValue[qRightDrive] < dis)){
		lDrive(pwr*moveDir);
		rDrive(pwr*moveDir);
	}
	lDrive(0);
	rDrive(0);
}

task autonomous(){
	AutonomousCodePlaceholderForTesting();
}
