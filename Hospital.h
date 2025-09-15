#pragma once
#include "LinkedQueue.h"
#include "CancellableQueue.h"
#include "priQueue.h"
#include "Patient.h"
#include "Car.h"
//#include "Organizer.h"
class Organizer;
class Hospital
{
public:
    Organizer* organizer;

	LinkedQueue<Patient*> SPList;
    CancellableQueue<Patient*> NPList;     
	priQueue<Patient*> EPList;
	LinkedQueue<Car*> SCars;
	LinkedQueue<Car*> NCars;
    int numNC = 0, numSC = 0;

private:
	
	int totalWaitingTime = 0;
    int carBusyTime = 0;

public:
    Hospital(Organizer*);
    //Hospital();
    void addPatient(Patient* p, const string& type);
    void addSCar(Car* c);
    void addNCar(Car* c);
    bool cancelNPatient(int PID);
    void assignPatients(int currentTime);
    void print();
    int getnumNC() {
        return numNC;
    }
    int getnumSC() {
        return numSC;
    }
};

