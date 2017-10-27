#pragma config(Sensor, dgtl1,  qLeft,          sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  qRight,         sensorQuadEncoder)
#pragma config(Motor,  port1,           BaseLeft,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           BaseRight,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void moveBase(int speed){
	motor[BaseLeft] = speed;
	motor[BaseRight] = speed;
}

void PID(int target){
	float kp = .2;
	int error;
	int proportion;
	int finalPower;

	SensorValue[qLeft] = 0;
	SensorValue[qRight] = 0;
	while(true){
		error = target - (SensorValue[qLeft]+ SensorValue[qRight]);
		proportion = kp*error;
		finalPower = proportion;
		moveBase(finalPower);
	}
}
task main()
{



}
