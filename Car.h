#pragma once
#include "Patient.h"

enum Status {
	READY,ASSIGNED,LOADED
};
class Car
{
private:
	string type;
	int speed;
	Status carStatus;
	Patient* assignedPatient=nullptr;
	int assignmentTime=-1;
	int HospitalID;
	int reachTime=-1;

public:
	Car(string type, int speed,int hid, Status carstatus = READY) :type(type), speed(speed), HospitalID(hid), carStatus(carstatus) {};
	void assignPatient(Patient* p, int time);
	void pickUp();
	Patient* drop();
	Patient* getPatient() const;
	int getHospitalID() const;
	int getSpeed() const{
		return speed;
	}
	int cancelPatient();

	void setReachTime(int time) {

		reachTime = time;
	};

	int getReachTime() {
		return reachTime;
	}
	int getAssignmentTime() {
		return assignmentTime;
	}
	Patient* getAssignedPatient() {
		return assignedPatient;
	}
	string getType() {
		return type;
	}

};
