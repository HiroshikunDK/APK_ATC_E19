#include <iostream>
#include <stdlib.h>
#include <map>
#include "boost/signals2/signal.hpp"
#include "./DummyAirPlane.h"
#include"./ControlTower.cpp"


using namespace std;

class RandomPlaneGenerator {


private:
	ControlTower* _ controlTower;
	std::map<std::string, koordinates > nameToDirectionMap;
	vector<Plane>::iterator existingPlanes;
	int maXAmountOfPlanes = 20;

	template<typename T> T subtract(T a, T b)  //Template Metaprogramming
	{
		return (a - b);
	}

public:

RandomPlaneGenerator(ControlTower* controlTower) {
	_controlTower = controlTower;
}


void RandomPlaneGenerator::GeneratePlane()
{
	while (true) {

	}
}



	
};




