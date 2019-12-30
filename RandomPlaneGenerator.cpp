#include <iostream>
#include <stdlib.h>
#include <map>
#include "boost/signals2/signal.hpp"
#include "./DummyAirPlane.h"
#include"./ControlTower.cpp"
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")


using namespace std;

class RandomPlaneGenerator {


private:
	std::map<std::string, koordinates > nameToDirectionMap;
	vector<Plane>::iterator existingPlanes;


public:

RandomPlaneGenerator() {
	_controlTower = controlTower;
}


void RandomPlaneGenerator::GeneratePlanes()
{
	int planeAmount = 7;
	while (true) {
		planeAmount = planeAmount + 1;
		for (x = existingPlanes.size(); x < planeAmount;x++) {

			//Create Name For Plane
			UUID newId;
			UuidCreate(&newId);
			Plane plane = new Plane(UuidToString(newId));

			koordinates coords = new koordinates();
			coords._longtitude = (rand() % 999) + 100000;
			coords._latitude = (rand() % 999) + 100000;
			coords._altitude = 6000;

			plane.currKoor = coords;
			plane.prevKoor = new koordinates();

			//Randomize Tragectory

			koordinates tragectory = new koordinates();
			switch ((rand() % 1) + 4)
			{
			case 1: // code to be executed if n = 1;
				
				tragectory._latitude = -20;
				tragectory._longtitude = -20;
				break;
			case 2: // code to be executed if n = 2;
				tragectory._latitude = 20;
				tragectory._longtitude = -20;
				break;
			case 3:
				tragectory._latitude = -20;
				tragectory._longtitude = 20;
				break;
			case 4:
				tragectory._latitude = 20;
				tragectory._longtitude = 20;

			}

			nameToDirectionMap.insert(UuidToString(newId),tragectory)
		}

		for (int a = 0; a < existingPlanes.size()-1; a = a + 1) {
			auto chosenPlane = existingPlanes[a];
			auto tragectory = nameToDirectionMap.find(chosenPlane.name);
			chosenPlane.prevKoor = chosenPlane.currKoor;
			chosenPlane.currKoor = chosenPlane.currKoor - tragectory;
			broadcastPlaneData(chosenPlane);

		}

		Sleep(1000);
	}
}



	
};



