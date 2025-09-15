#include "Organizer.h"
#include <fstream>
#include <iostream>	
#include <random>	
#include "UI.h"


Organizer::Organizer(string inputFileName)
{
    LoadInputFile(inputFileName);
    ui = new UI(this);
}

void Organizer::LoadInputFile(string file) {
    ifstream inputFile(file);
    inputFile >> NumHospitals >> Sspeed >> Nspeed;
    Hospitals = new Hospital * [NumHospitals];
    for (int i = 0; i < NumHospitals; i++) {
        Hospitals[i] = nullptr;
    }
    int distance;
    for (int i = 0; i < NumHospitals; i++) {
        for (int j = 0; j < NumHospitals; j++) {
            inputFile >> distance;
        }
    }

    for (int i = 0; i < NumHospitals; i++) {
        int SCars, Ncars;
        inputFile >> SCars >> Ncars;
        NumNCars += Ncars;
        NumSCars += SCars;
        NumCars += SCars + Ncars;
        AddHospital(Ncars, SCars);
    }
    inputFile >> NumPatients;
    for (int i = 0; i < NumPatients; i++) {
        string Type;
        int ReqTime, PID, HID, distance, severity = 1;
        inputFile >> Type >> ReqTime >> PID >> HID >> distance;
        if (Type == "EP") {
            inputFile >> severity;
        } AddPatient(Type, ReqTime, PID, HID, distance, severity);
    }
    inputFile >> NumCancels;
    for (int i = 0; i < NumCancels; i++) {
        int PID, cancelTime;
        inputFile >> PID >> cancelTime;
        AddcancelledPatient(PID, cancelTime);
    }
    inputFile.close();
}


void Organizer::setnumpatients(int n)
{
    NumPatients = n;
}
void Organizer :: AddHospital(int Ncars, int Scars)
{
    Hospital* h = new Hospital(this);
    //Hospitals[NumHospitals]=h;
    static int count = 0;
    Hospitals[count++] = h;
    for (int j = 0; j < Scars; j++)
    {
        Car* c = new Car("Special", Sspeed, NumHospitals+1);
        h->addSCar(c);
    }
    for (int j = 0; j < Ncars; j++)
    {
        Car* c = new Car("Normal", Nspeed, NumHospitals+1);
        h->addNCar(c);
    }
    //NumHospitals++;
}


void Organizer::AddPatient(string type, int rtime, int PID, int HID, int distance, int severity=1)
{
    Patient* patient = new Patient(type, HID,distance ,rtime, severity, PID);
    AllPatients.enqueue(patient);
    Hospitals[HID-1]->addPatient(patient, type);
}


void Organizer::AddFinishedPatient(Patient* patient)
{
    FinishedPatients.enqueue(patient);
}

void Organizer::AddcancelledPatient(int PID, int canceltime)
{
    Patient* patient = getdatafromqueue(AllPatients, PID);
    if (patient == nullptr) {
        return;
    }
    patient->setcancellationTime(canceltime);
    CancellationList.enqueue(patient);
}



void Organizer::AddOutCar(Car* car)
{
    Outcars.enqueue(car, car->getAssignedPatient()->getPickTime());
    cout << "Doneee";
}

template<typename T>
T* Organizer::getdatafromqueue(LinkedQueue<T*>q, int index) {
        LinkedQueue<T*> tempQueue = q; 
        T* temp=nullptr;   
        for (int i = 1; i < index+1; i++) {
            tempQueue.dequeue(temp);
        }
        return temp;
}

Organizer::~Organizer()
{
    Patient* temp;
    Car* temp2;
    for (int i = 0; i < NumHospitals; i++)
    {
        delete Hospitals[i];
        Hospitals[i] = nullptr; 
    }
    delete[] Hospitals;
    while (AllPatients.dequeue(temp))
    {
        delete temp;
    };
    while (CancellationList.dequeue(temp))
    {
        delete temp;
    };
    while (FinishedPatients.dequeue(temp))
    {
        delete temp;
    };
    FinishedPatients.~LinkedQueue();
    Outcars.~derivedpriQueue();
}

LinkedQueue<Patient*> Organizer::getAllrequests() const
{
    return AllPatients;
}
LinkedQueue<Patient*> Organizer::getAllcancells() const
{
    return CancellationList;
}

void Organizer::simulate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    std::uniform_int_distribution<int> dist2(0, NumHospitals - 1);

    std::cout << "Simulation Started!" << std::endl;
    std::cout << "-------------------" << std::endl;
    bool flag = true;
    while (NumPatients > (NumCancels + GetcountFinishedPatients())&& flag) {
        
        std::cout << "Current Timestep: " << currentTime << std::endl;

        
        for (int i = 0; i < NumHospitals; ++i) {
            printHospitalStatus(i);
        }

        
        int randomValue = dist(gen);
        int hospitalIndex = dist2(gen);

        if (randomValue >= 10 && randomValue < 20) { 
            Patient* p = nullptr;
            Hospitals[hospitalIndex]->SPList.dequeue(p);
            if (p) {
                FinishedPatients.enqueue(p);
            }
        }
        else if (randomValue >= 20 && randomValue < 25) { 
            Patient* p = nullptr;
            int pri;
            Hospitals[hospitalIndex]->EPList.dequeue(p, pri);
            if (p) {
                FinishedPatients.enqueue(p);
            }
        }
        else if (randomValue >= 30 && randomValue < 40) { 
            Patient* p = nullptr;
            Hospitals[hospitalIndex]->NPList.dequeue(p);
            if (p) {
                FinishedPatients.enqueue(p);
            }
        }
        else if (randomValue >= 40 && randomValue < 45) {
            Car* c = nullptr;
            Hospitals[hospitalIndex]->SCars.dequeue(c);
            if (c) {
                Outcars.enqueue(c, currentTime);
            }
        }
        else if (randomValue >= 70 && randomValue < 75) {
            Car* c = nullptr;
            Hospitals[hospitalIndex]->NCars.dequeue(c);
            if (c) {
                Outcars.enqueue(c, currentTime);
            }
        }
        else if (randomValue >= 80 && randomValue < 90) {
            Car* c = nullptr;
            int dispatchTime;
            Outcars.dequeue(c, dispatchTime);
            if (c) {
                Backcars.enqueue(c, dispatchTime);
            }
        }

       
        currentTime++;
        cout << "-------------------" << endl;
        char c;
        cin >> c;
        cout << "To stop press s and to continue press c" << endl;
        if (c == 's')flag = false;
        if (c == 'c')flag = true;
    }

   
    cout << "\nSimulation Complete!" << std::endl;
    cout << "-------------------" << std::endl;
    ui->printQueue(FinishedPatients);
    ui->printStatus();
    ui->printFinalStatistics();
}
void Organizer::printHospitalStatus(int hospitalIndex) {
    Hospital* hospital = Hospitals[hospitalIndex];

   cout << "==============  HOSPITAL #" << hospitalIndex + 1 << " data  ==============" << endl;

    
   cout << "EP requests: ";
  

    
   cout << "SP requests: ";
    hospital->SPList.print();

    
   cout << "NP requests: ";
    hospital->NPList.print();

    
    cout << "Free Cars: " << hospital->getnumSC() << " SCars, "
        << hospital->getnumNC() << " NCars" << endl;

    cout << "==============  HOSPITAL #" << hospitalIndex + 1 << " data end  ==============" << endl;
}





int Organizer::getCurrentTimestep() const
{
    return currentTime;
}

void Organizer::setcurrentTimestep(int time)
{
    currentTime = time;
}
void Organizer::AddBackCar(int currenttime) {
    Car* c;
    int pickTime;
    while (Outcars.peek(c, pickTime)) {
        if (pickTime > 0 && pickTime == currenttime) {
            Outcars.dequeue(c, pickTime);

            c->pickUp();
            Backcars.enqueue(c, c->getReachTime());
        }



    }
}
int Organizer::countFreeCars() {
    int totalFreeCars = 0;

    
    for (int i = 0; i < NumHospitals; i++) {
        totalFreeCars += Hospitals[i]->getnumSC(); 
        totalFreeCars += Hospitals[i]->getnumNC(); 
    }

    return totalFreeCars;
}

int Organizer::calculateAverageWaitingTime()
{
    LinkedQueue<Patient*> FinishedPatients2 = FinishedPatients;

    Patient* FPatient;
    int totalWaitingTime = 0;
    int numPatients = 0;

    while (FinishedPatients2.dequeue(FPatient))
    {
        totalWaitingTime += FPatient->getWaitingTime();
        numPatients++;
    }

    return totalWaitingTime / numPatients;
}

int Organizer::GetcountFinishedPatients()
{
    LinkedQueue<Patient*> FinishedPatients2 = FinishedPatients;

    Patient* FPatient;
    int totalWaitingTime = 0;
    int numPatients = 0;

    while (FinishedPatients2.dequeue(FPatient))
    {
        if(FPatient)
        totalWaitingTime += FPatient->getWaitingTime();
        numPatients++;
    }
    return numPatients;
}

void Organizer::cancelPatient(){
    Patient* p;
    while (CancellationList.peek(p)&&p->getcancelletionTime()==currentTime) {
        bool found = Hospitals[p->getHospital()]->cancelNPatient(p->getPID());
        if (!found) {
            Car* cancelledCar = Outcars.cancel(p);
            if (cancelledCar) {
                CancellationList.dequeue(p);
                Backcars.enqueue(cancelledCar, cancelledCar->getReachTime());
            }
        }
    }
}



