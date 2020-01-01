#include <iostream>
#include <stdlib.h>
#include <map>
#include "boost/signals2/signal.hpp"
#include "ControlTower.h"
#include "AirTrafficControl.h"
#include "RandomPlaneGenerator.h"
//#include <Rpc.h>
#include <random>
#include <string>
#pragma comment(lib, "Rpcrt4.lib")


using namespace std;

void RandomPlaneGenerator::GeneratePlanes()
{
	
	//while (true) {
		int planeAmount = 0;
		for (int j = 0; j < existingPlanes.size(); j++) {
			planeAmount++;
			
			koordinates coords = koordinates();


			if(existingPlanes[j].name == "default")
			{
				auto ranName = random_string(4);
				existingPlanes[j].name = ranName; //= new Plane(name);
			
				coords._longtitude = (rand() % 999) + 100000;
				coords._latitude = (rand() % 999) + 100000;
				coords._altitude = 6000;

				existingPlanes[j].currKoor = coords;
				existingPlanes[j].prevKoor = koordinates();
			}
			

			if /*constexpr*/ (enviroment == "Test") //constexpr virker kun hvis enviroment er const
			{
				coords._longtitude = 2000;
				coords._latitude = 2000;
				coords._altitude = 6000;
			}
			
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
		//cout << "Updates loaded into maps: " << to_string(existingPlanes.size()) << endl;

		//int i = 0;
		for (auto ite = existingPlanes.begin(); ite < existingPlanes.end(); ite++) {
			
			
			Plane chosenPlane = *ite;
			koordinates tragectory = nameToDirectionMap[chosenPlane.name];
			chosenPlane.prevKoor = chosenPlane.currKoor;
			chosenPlane.currKoor = chosenPlane.currKoor - tragectory;
			*ite = chosenPlane;
			broadcastPlaneData(chosenPlane);
			//i++;
		}

		sleep(1); 
	//}
}

void RandomPlaneGenerator::ChangeAltitude(string name, int altitude) 
{
	for (int i = 0; i < existingPlanes.size(); i++)
	{
		if (existingPlanes[i].name == name)
		{
			existingPlanes[i].currKoor._altitude = altitude;

			cout << "Plane " << name <<", Found and Changed to: " << to_string(altitude) << endl;

			return;
		}
	}
}




