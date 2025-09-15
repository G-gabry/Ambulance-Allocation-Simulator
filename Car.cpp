#include "Car.h"

void Car::assignPatient(Patient* p, int time) {
	assignmentTime = time;
	carStatus = ASSIGNED; assignedPatient = p;
	int pickUpTime = assignmentTime + assignedPatient->getDistance() / speed;
	assignedPatient->setPickUpTime(pickUpTime);
};
void Car::pickUp() {

	carStatus = LOADED;
	setReachTime(2 *(assignedPatient->getPickTime()) - assignmentTime);
	//int pickUpTime = assignmentTime + assignedPatient->getDistance() / speed;
	//assignedPatient->setPickUpTime(pickUpTime);

}

Patient* Car::getPatient() const {
	return assignedPatient;
}
Patient* Car::drop() {
	carStatus = READY;
	int finishTime = assignedPatient->getPickTime() + assignedPatient->getDistance() / speed;
	assignedPatient->setFinishTime(finishTime);
	Patient* ap = assignedPatient;
	assignedPatient = nullptr;
	return ap;

}
int Car::getHospitalID() const {
    return HospitalID;
}

int Car::cancelPatient()
{
	int canceltime = assignedPatient->getcancelletionTime();
	assignedPatient = nullptr;
	return canceltime;
}
