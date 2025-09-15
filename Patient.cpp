#include "Patient.h"

Patient::Patient(string type, int nearest, int d, int reqTime, int severity,int pid) {
	requestTime = reqTime;
	this->type = type;
	this->severity = severity;
	nearestHospital = nearest;
	distance = d;
	this->PID = pid;
	pickUpTime = -1;
	finishTime = -1;

}
void Patient::setPickUpTime(int time) {
	pickUpTime = time;
	waitingtime = pickUpTime - requestTime;
}

void Patient::setFinishTime(int time)
{
	finishTime = time;
}

int Patient::getReqTime() const {
	return requestTime;
}
int Patient::getPickTime() const
{
	return pickUpTime;
}
string Patient::getType()const {
	return type;
}
int Patient::getSeverity()const {
	return severity;
}
int Patient::getDistance()const {
	return distance;
}
int Patient:: getHospital()const {
	return nearestHospital;

}
void Patient::setHospital(int hos) {
	if (type == "EP") { nearestHospital = hos; }
}
void Patient::setDistance(int d) {
	if (type == "EP") { distance = d; }

}
int Patient::getPID()const {
	return PID;
}

int Patient::getcancelletionTime() const 
{
	return cancellationTime;
}

void Patient::setcancellationTime(int time)
{
	cancellationTime = time;
}

int Patient::getWaitingTime() const
{
	return waitingtime;
}
int Patient::getFinishTime() const
{
	return finishTime;
}
