#pragma once
//#include "UI.h"
# include "LinkedQueue.h"
# include "priQueue.h"
# include "Car.h"
#include "Patient.h"
#include "Hospital.h"   
class UI;

class Organizer
{
private:
    int NumHospitals;
    int Nspeed;
    int Sspeed;
    int NumPatients;
    int NumCancels;
    int NumNCars;
    int NumSCars;
    int NumCars;
    int currentTime = 0;
    LinkedQueue<Patient*> AllPatients;
    LinkedQueue<Patient*> CancellationList;
    UI* ui;
public:
    
    Hospital** Hospitals = nullptr;
private:
    derivedpriQueue Outcars;
    priQueue<Car*> Backcars;
    LinkedQueue<Patient*> FinishedPatients;

public:
    Organizer(string file);
    void AddHospital(int Ncars, int Scars);
    void AddPatient(string type, int rtime, int PID, int HID, int distance, int severity);
    void AddFinishedPatient(Patient* patient);
    void AddcancelledPatient(int PID, int canceltime);  //assigned patient in the car should be null
    void cancelPatient();
    void setnumpatients(int n);
    Hospital** getHospitals() const {
        return Hospitals;
    }


    void AddOutCar(Car* car);
    void AddBackCar(int currenttime);
    int countFreeCars();
    void LoadInputFile(string file);
    
    LinkedQueue<Patient*> getAllrequests() const;
    
    void setMode(int mode){}
    
    Hospital** getHospitals() {
        return Hospitals;
    }
    int getNumHospitals() {
        return NumHospitals;
    }
    LinkedQueue<Patient*> cancelList() {
        return CancellationList;
    }
    
    //assigned patient in the car should be null and added to finished patient list
    template <typename T>
    
    T* getdatafromqueue(LinkedQueue<T*> q, int index);

    ~Organizer();
    int getCurrentTimestep() const;
    void setcurrentTimestep(int time);
    int calculateAverageWaitingTime();
    int GetcountFinishedPatients();
   // LinkedQueue<Patient*> getAllrequests() const;
    LinkedQueue<Patient*> getAllcancells() const;

    int getNumofPatients() const {
        return NumPatients;
    }
    int getNumofCancels() const {
        return NumCancels;
    }
    int getNumNCars() const {
        return NumNCars;
    }
    int getNumSCars() const {
        return NumSCars;
    }
    int getNumCars() const {
        return NumCars;
    }
    void simulate();
    void printHospitalStatus(int hospitalIndex);
    void print(int hospitalIndex);
    UI* getui() const{
        return ui;
    }
    
};