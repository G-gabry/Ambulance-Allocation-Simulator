#include "Organizer.h"
#include "LinkedQueue.h"
#include"Hospital.h"
#include "UI.h"
#include <iostream>	
#include <random>						//To use C++ console I/O functionality
						//, we need to include iostream which contains necessary declarations.

using namespace std;	//This statement enables us to use classes and objects in the standard C++ library
						//without prefixing them with "std::"
//This is the program starting point.
int main()
{
	

	string inputFileName;
	cout << "Welcome to the Emergency Room Simulation" << endl;
	cout << "Please enter the input file name" << endl;
	cin >> inputFileName;
	Organizer* org = new Organizer(inputFileName);
	UI* ui = org->getui();
	
	org->simulate();
	


	/*Hospital** h = org->getHospitals();
	LinkedQueue<Patient*> Allrequests = org->getAllrequests();
	LinkedQueue<Patient*> Allcanelations = org->getAllcancells();
	Patient* p;
	while (Allrequests.dequeue(p)) {

		cout << p->getReqTime() << p->getSeverity();
	}
	int currenttime = 0;




	
	bool flag = true;
	int count = 0;
	while (flag)
	{
		Patient* p;
		Patient* p1;
		bool condition = true;
		bool condition1 = true;
		while (condition)
		{
			if (Allrequests.peek(p))
			{
				if (p->getReqTime() == count)
				{
					org->AddPatient(p->getType(), p->getReqTime(), p->getPID(), p->getHospital(), p->getDistance(), p->getSeverity());
					Allrequests.dequeue(p);
				}
				else
				{
					condition = false;
				}
			}
			else
			{
				delete org;
				org = nullptr;
				flag = false;
			}
		}
		while (condition1)
		{
			if (Allcanelations.peek(p1))
			{
				if (p1->getcancelletionTime() == count)
				{
					// You should cancel the patient and move the car from the out cars to the back cars
					org->AddcancelledPatient(p1->getPID(), p1->getcancelletionTime());
					Allcanelations.dequeue(p1);
				}
				else
				{
					condition1 = false;
				}
			}
			else
			{
				condition1 = false;
			}
		}
		count++;
		org->setcurrentTimestep(count);
	}*/
}
  
