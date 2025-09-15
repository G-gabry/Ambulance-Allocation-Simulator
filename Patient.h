#pragma once
#include <iostream>
using namespace std;

class Patient
{
private:
	
	int requestTime;
	int cancellationTime = -1;
	int pickUpTime;
	string type;
	int nearestHospital;
	int distance;
	int  severity; //default is one for Sp,Np and more than one for Ep
	int finishTime = -1;
	int PID;
	int waitingtime;
public:

	Patient(string type, int nearest, int d, int reqTime, int severity, int PID);
	void setPickUpTime(int time);
	void setFinishTime(int);
	int getReqTime() const;
	int getDistance() const;
	string getType()const;
	int getSeverity()const;
	int getPickTime()const;
	int getHospital()const;
	void setHospital(int hos);
	void setDistance(int d);
	int getPID()const;
	int getcancelletionTime()const;
	void setcancellationTime(int time);
	int getWaitingTime()const;
	int getFinishTime()const;
};
