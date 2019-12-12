#include <iostream>
#include <stdlib.h>

#include "boost/signals2/signal.hpp"
#include "./DummyAirPlane.h"

using namespace std;

vector<Plane&> ControlTower::collisionDetection(vector<Plane>* inVector)
{
		vector<Plane>::iterator itinner;
		vector<Plane>::iterator itouter;
		vector<Plane&>::iterator itconv;
		vector<Plane&> resultVec;
		vector<Plane> tempVec;
		int delta = 0;
		for (itouter = inVector->begin(); itouter != inVector->end(); itouter++)
		{
			for (itinner = inVector->begin(); itinner != inVector->end(); itinner++)
			{
				if ((itouter->name != itinner->name)) 
				{
					//TODO: think a operator overload on Plane here - could be nicer
					delta = itouter->currKoor._altitude - itouter->currKoor._altitude;
					if (delta > -500 && delta < 500) 
					{
						delta = itouter->currKoor._longtitude - itinner->currKoor._longtitude;
						if (delta > -500 && delta < 500) 
						{
							delta = itouter->currKoor._latitude - itinner->currKoor._latitude;
							if (delta > -500 && delta < 500)
							{
								//converts vector of Plane pointers to a vector of planes
								for (itconv = resultVec.begin(); itconv != resultVec.end(); itconv++) 
								{
									tempVec.push_back(*itconv);
								}
								//conversion  over
								if (objExistInVec(tempVec, *itinner)!=true) 
								{
									//Skulle itinner ikke være lovligt at gemme i et vector<Plane&>
									//måske fordi det er en iterator pointer, men det objekt jeg caster 
									//til, stadig den samme som det i den originale vector? ¯\_(:/)_/¯ 
									resultVec.push_back(*itinner);
								}
							}
						}
					}
				}
			}
		}
}
template<class T>
bool ControlTower::objExistInVec(const vector<T> inVector,const T obj)
{
	vector<T>::const_iterator it;

	for (it = inVector->begin(); it != inVector->end(); it++) 
	{
		if (it == obj) 
		{
			return true;
		}
	}
	return false;
}

void ControlTower::changeCourse() {} //meta programming here?

void ControlTower::printAllObj()
{
	Plane temp;
	for (int i = 0; i > _objList.size(); i++) 
	{
		cout << "Plane " << to_string(i) << ":" << endl;
		printObj(_objList[i]);
		cout << endl;
		
	}
}

void ControlTower::printObj(Plane obj) 
{
	cout << "Name: " << obj.name <<endl;
	cout << "Type: " << obj.name << endl;
	cout << "Current Position: \n{\n" << obj.currKoor.printKoor() << "}" <<  endl;
	cout << "Previous Position: \n{\n" << obj.prevKoor.printKoor() << "}" << endl;
}

void ControlTower::objHandle(Plane obj)
{
	if (objExistInVec(_objList, obj)!=true)
	{
		objRecieve(obj);
	}
	else 
	{
		objUpdate(obj);
	}
}
void ControlTower::objRecieve(Plane obj) 
{
	// what else to do?
	_objList.push_back(obj);
}
void ControlTower::objUpdate(Plane obj)
{
	//the normal loop of a vector
	for (int i = 0; i < _objList.size(); i++) 
	{
		if (_objList[i].name == obj.name) 
		{
			//this could be made better from Plane class.
			obj.prevKoor = _objList[i].currKoor;
			_objList[i] = obj;
			// no check of other mutations on the plane class eg. type
			return;
		}
	}
}
void ControlTower::objRemove(Plane obj) 
{
	vector<Plane>::iterator ite;

	for (ite = _objList.begin(); ite !=_objList.end(); ite++)
	{
		if (ite->name == obj.name)
		{
			//this could be made better from Plane class.
			_objList.erase(ite);
			//is the pointer count now wrong if we were to delete multiple objects in this function?
			// no check of other mutations on the plane class eg. type
			return;
		}
		else 
		{
			cout << "Can't find the object to remove" << endl;
		}
	}
}