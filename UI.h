#pragma once
#include "Organizer.h" //

#include<iostream>
//class Organizer;
//class Hospital;

class UI {
private:
    Organizer* organizer; 
    string inputFileName;
    string outputFileName;
    
public:
    
    UI(Organizer* org) : organizer(org) {};   
    bool chooseMode();
    void printStatus();
    void printFinalStatistics();    
    void printQueue(const LinkedQueue<Patient*> queue);
    void printPriorityQueue(const derivedpriQueue& queue);    
   int GetNumCars();
    int GetNumNCars();
    int GetNumSCars();
    void writeOutputFile();
};