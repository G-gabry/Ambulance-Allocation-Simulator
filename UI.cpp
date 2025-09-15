#include"Organizer.h"
#include<string>
#include "UI.h"
#include"fstream"
#include "priQueue.h" 



bool UI::chooseMode()
{
	int mode;
	cout << "If you need active mood choose 1 and choose -1 for silent mood" << endl;
	cin >> mode;
	while (mode != 1 && mode != -1) {
		cout << "please Enter 1 for active mode or -1 for silent mode Enter mode again";
		cin >> mode;		
	}
	//organizer->setMode(mood);
	if (mode == 1) {
	
		return true;
	}
	else {
		return false;
	}	
}

void UI::printStatus() {
	cout << "Current Timestep: " << organizer->getCurrentTimestep() <<endl;
	cout << "All Patients: ";
	printQueue(organizer->getAllrequests());
	cout << "Cancellation List: ";
	printQueue(organizer->getAllcancells());
	/* cout << "Out Cars: ";
	printPriorityQueue(organizer->getOutcars());
	cout << "Back Cars: ";
	printPriorityQueue(organizer->getBackcars()); */

}

void UI::printQueue(LinkedQueue<Patient*> queue)
	{
		LinkedQueue<Patient*> tempQueue = queue;
		Patient* temp;
		while (!tempQueue.isEmpty()) {
			tempQueue.dequeue(temp);
			std::cout << "Patient ID: " << temp->getPID() << ", Type: " << temp->getType() << std::endl;
		}
	}

/*void UI::printPriorityQueue(derivedpriQueue& queue) {
	derivedpriQueue tempQueue = queue; 
	Car* temp;
	while (!tempQueue.isEmpty()) {
		tempQueue.dequeue(temp);
		std::cout << "Car ID: " << temp->getID()
			<< ", Type: " << temp->getType() << std::endl;
	}
}*/

void UI::printFinalStatistics() {
	cout << "Simulation Complete!" << endl;
 	cout << "Total Patients Served: " << organizer->GetcountFinishedPatients() <<endl;	
	}	

void UI::writeOutputFile() {
	
		outputFileName = "simulationtxt";		
		std::ofstream outFile(outputFileName);		
		outFile << "FT\tPID\tQT\tWT\n"; 
		LinkedQueue<Patient*> tempQueue = organizer->getAllrequests();
		Patient* temp;
		while (!tempQueue.isEmpty()) {
			tempQueue.dequeue(temp);
			if (temp->getFinishTime() == -1) {
				temp->setFinishTime(organizer->getCurrentTimestep());
			}
			outFile << temp->getFinishTime() << "\t"  
				<< temp->getPID() << "\t"         
				<< temp->getReqTime() << "\t"
				<< temp->getWaitingTime() << "\n";
		}

		
		outFile << "--------------------------------------\n";
		outFile << "Patients: " << organizer->getNumofPatients() << "\n";
		outFile << "hospitals " << organizer->getNumHospitals()<<"\n";
		outFile << "Cars: " << organizer->getNumCars()<<" [ "<<"NCars " << organizer->getNumNCars()<<" Scars "<<organizer->getNumSCars()<<" ]"<<endl;
		outFile << "Average Waiting Time: " << organizer->calculateAverageWaitingTime() << " timesteps\n";
		//outFile << "AVG Utilization: " << organizer->calculateCarUtilization() << "%\n";	 */	
		outFile.close();
		
	} 

