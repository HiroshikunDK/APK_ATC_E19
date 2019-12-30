#include <iostream>
#include <stdlib.h>
#include <map>
#include "boost/signals2/signal.hpp"
#include "./DummyAirPlane.h"
#include "AirTrafficControl.h"
#include "RandomPlaneGenerator.h"
#include <Rpc.h>
#include <random>
#include <string>
#pragma comment(lib, "Rpcrt4.lib")


using namespace std;

void RandomPlaneGenerator::GeneratePlanes()
{
	
	while (true) {
		int planeAmount = 0;
		for (int j = 0; j < existingPlanes.size(); j++) {
			planeAmount++;
			
			if(existingPlanes[j].name == "default")
			{
			auto ranName = random_string(8);
			existingPlanes[j].name = ranName; //= new Plane(name);
			}
			koordinates coords = koordinates();


			if /*constexpr*/ (enviroment == "Test") //constexpr virker kun hvis enviroment er const
			{
				coords._longtitude = 2000;
				coords._latitude = 2000;
				coords._altitude = 6000;
			}
			else {
				coords._longtitude = (rand() % 999) + 100000;
				coords._latitude = (rand() % 999) + 100000;
				coords._altitude = 6000;
			}
			existingPlanes[j].currKoor = coords;
			existingPlanes[j].prevKoor = koordinates();

			//Randomize Tragectory

			koordinates tragectory = koordinates();
			switch ((rand() % 1) + 4)
			{
			case 1: // code to be executed if n = 1;

				tragectory._latitude = (rand() % -30) - 10;
				tragectory._longtitude = (rand() % -30) - 10;
				break;
			case 2: // code to be executed if n = 2;
				tragectory._latitude = (rand() % 30) + 10;
				tragectory._longtitude = (rand() % -30) - 10;
				break;
			case 3:
				tragectory._latitude = (rand() % -30) - 10;
				tragectory._longtitude = (rand() % 30) + 10;
				break;
			case 4:
				tragectory._latitude = (rand() % 30) + 10;
				tragectory._longtitude = (rand() % 30) + 10;

			}

			nameToDirectionMap.insert({existingPlanes[j].name, tragectory});
		}
		cout << "Updates loaded into maps: " << to_string(existingPlanes.size()) << endl;

		int i = 0;
		for (auto ite = existingPlanes.begin(); ite < existingPlanes.end(); ite++) {
			
			
			Plane chosenPlane = *ite;
			koordinates tragectory = nameToDirectionMap[chosenPlane.name]; //�ndret til second, s� man rammer koordinatet
			chosenPlane.prevKoor = chosenPlane.currKoor;
			chosenPlane.currKoor = chosenPlane.currKoor - tragectory;
			broadcastPlaneData(chosenPlane);
			i++;
		}

		Sleep(1000);
	}
}





