#include "Hospital.h"
#include "Organizer.h"
Hospital::Hospital(Organizer* o) {
    organizer = o;
}

void Hospital::addPatient(Patient* p, const string& type) {
    if (type == "SP") {
        SPList.enqueue(p);
    }
    else if (type == "NP") {
        NPList.enqueue(p);
    }
    else if (type == "EP") {
        EPList.enqueue(p, p->getSeverity());  
    }

}

void Hospital::addSCar(Car* c) {
    SCars.enqueue(c);
    numSC++;
}

void Hospital::addNCar(Car* c) {
    NCars.enqueue(c);
    numNC++;
}
void LinkedQueue<Patient*>::print() const {
    Node<Patient*>* currentNode = frontPtr; 
    while (currentNode != nullptr) {
        Patient* patient = currentNode->getItem();
        cout << patient->getPID() << ", "; 
        currentNode = currentNode->getNext();
    }
    cout << endl;
}




bool Hospital::cancelNPatient(int PID) {
   bool found= NPList.cancel(PID);
   if (found) { return true; }
   return false;
}


void Hospital::assignPatients(int currentTime) {
    Patient* p;
    int severity;
    Car* c;


    while (EPList.dequeue(p, severity)) {
        if (NCars.dequeue(c)) {
            c->assignPatient(p, currentTime); 
            //c->pickUp(); 
            totalWaitingTime += (currentTime - p->getReqTime());
            carBusyTime += p->getDistance() / c->getSpeed();
            int reachtime = 2 * (p->getPickTime() - c->getAssignmentTime());
            c->setReachTime(reachtime);
            organizer->AddOutCar(c);
//            cout << "Done";

        }
        else if (SCars.dequeue(c)) {
            c->assignPatient(p, currentTime); 
            c->pickUp(); 
            totalWaitingTime += (currentTime - p->getReqTime());
            carBusyTime += p->getDistance() / c->getSpeed();
            organizer->AddOutCar(c);
        }
        else {
            EPList.enqueue(p, severity); 
        }
    }



    while (SPList.dequeue(p)) {
        if (SCars.dequeue(c)) {
            c->assignPatient(p, currentTime); 
            c->pickUp(); 
            totalWaitingTime += (currentTime - p->getReqTime());
            carBusyTime += p->getDistance() / c->getSpeed();
           organizer->AddOutCar(c);
        }
    }

    while (NPList.dequeue(p)) {
        if (NCars.dequeue(c)) {
            c->assignPatient(p, currentTime);
            c->pickUp(); 
            totalWaitingTime += (currentTime - p->getReqTime());
            carBusyTime += p->getDistance() / c->getSpeed();
           organizer->AddOutCar(c);
        }
    }
}

void Hospital::print() {
    Patient* p; int severity;
    while (EPList.dequeue(p, severity)) {
        cout << severity << endl;
    }
    cout << "Done";
}