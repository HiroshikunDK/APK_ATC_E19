
#pragma once
#include <iostream>
#include <stdlib.h>

#include "boost/signals2/signal.hpp"
#include "ControlTower.h"
#include "signals2.h"
#include "AirTrafficControl.h"


using namespace std;
string ControlTower::isPlanesTooClose() 
{
	int delta = 0;
	for (int i = 0; i < _objList.size(); i++)
	{

		for (int j = 0; j < _objList.size(); j++)
		{
			if ((i != j))
			{
				//TODO: think a operator overload on Plane here - could be nicer
				delta = _objList.at(i).currKoor._altitude - _objList.at(j).currKoor._altitude;
				if (delta > -5000 && delta < 5000)
				{
					delta = _objList.at(i).currKoor._longtitude - _objList.at(j).currKoor._longtitude;
					if (delta > -5000 && delta < 5000)
					{
						delta = _objList.at(i).currKoor._latitude - _objList.at(j).currKoor._latitude;
						if (delta > -5000 && delta < 5000)
						{
							return _objList.at(i).name;
						}
					}
				}
			}
		}
	}
	return "none";
}

vector<Plane> ControlTower::collisionDetection(vector<Plane> inVector)
{
	/*
	vector<Plane&> resultVec;
	vector<Plane> tempVec;

	int delta = 0;
	for (int i = 0 ; i < inVector->size(); i++)
	{

		for (int j = 0; j < inVector->size(); j++)
		{
			if ((i != j))
			{
				//TODO: think a operator overload on Plane here - could be nicer
				delta = inVector->at(i).currKoor._altitude - inVector->at(j).currKoor._altitude;
				if (delta > -500 && delta < 500)
				{
					delta = inVector->at(i).currKoor._longtitude - inVector->at(j).currKoor._longtitude;
					if (delta > -500 && delta < 500)
					{
						delta = inVector->at(i).currKoor._latitude - inVector->at(i).currKoor._latitude;
						if (delta > -500 && delta < 500)
						{
							//converts vector of Plane pointers to a vector of planes
							for (int k = 0; k < tempVec.size(); k++)
							{
								tempVec.push_back(inVector->at(i));
							}

							//conversion  over
							if (objExistInVec(tempVec, inVector->at(i)) != true)
							{
								//Skulle itinner ikke være lovligt at gemme i et vector<Plane&>
								//måske fordi det er en iterator pointer, men det objekt jeg caster 
								//til, stadig den samme som det i den originale vector? ¯\_(:/)_/¯ 
								resultVec.push_back(inVector->at(i));
							}
						}
					}
				}
			}
		}
	}*/
		/*
		vector<Plane>::iterator itinner;
		vector<Plane>::iterator itouter;
		vector<Plane&>::iterator itconv;
		vector<Plane&> resultVec;
		vector<Plane> tempVec;
		int delta = 0;
		for (itouter = inVector.begin(); itouter != inVector.end(); itouter++)
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
		}*/
	vector<Plane> pv = vector<Plane>();
	return pv;
}
//none specialized template function.
bool ControlTower::objExistInVec(const vector<Plane> inVector,const Plane obj)
{
	/*
	for (int i = 0; i > inVector.size(); i++)
	{
		if (inVector[i] == obj)
		{
			return true;
		}
	}

	return false;
	*/
	
	vector<Plane>::const_iterator it;

	for (it = inVector.begin(); it != inVector.end(); it++)
	{
		if (it->name == obj.name) 
		{
			return true;
		}
	}
	return false;

}

void ControlTower::changeCourse() {} //meta programming here?

void ControlTower::printAllObj()
{
	Plane temp = Plane("TEMP");
	for (int i = 0; i < _objList.size(); i++) 
	{
		cout << "Plane " << to_string(i) << ":" << endl;
		printObj(_objList[i]);
		cout << endl;
		
	}
}

void ControlTower::printObj(Plane obj) 
{
	cout << "Name: " << obj.name <<endl;
	//cout << "Type: " << obj.name << endl;
	cout << "Current Position: \n{\n" << myToString(obj.currKoor, printKoor) << "}" <<  endl; 
	//cout << "Previous Position: \n{\n" << obj.prevKoor.printKoor() << "}" << endl;
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
			//obj.prevKoor = _objList[i].currKoor;
			_objList[i] = obj;
			// no check of other mutations on the plane class eg. type
			//if (i == 0)
			//{
			//	printObj(obj);
			//}
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

bool ControlTower::checkInputChars(string rawstring) 
{
	cout << "Checking input string" << endl;
	int cnt =  0;
	for (char& c : rawstring) {
		cnt++;
		if ( c == '+' || c == '-' || c == '*' || c == '/')
		{
			throw "Mathematical Operations aren't Allowed";
			return false;
		}
		
	}
	if (cnt > 8) 
	{
		throw "Input too long";
		return false;
	}
	return true;
}

void ControlTower::objRemovebyName()
{
	try 
	{
		vector<Plane>::iterator ite;

		string InputString;
		cout << "Type Name of Plane to be removed: ";
		cin >> InputString;

		if (checkInputChars(InputString)) 
		{
			for (ite = _objList.begin(); ite != _objList.end(); ite++)
			{
				if (ite->name == InputString)
				{
					//this could be made better from Plane class.
					_objList.erase(ite);
					//is the pointer count now wrong if we were to delete multiple objects in this function?
					// no check of other mutations on the plane class eg. type
					return;
				}
			}
		}
	} catch (const char* msg) 
	{
		cerr << msg << endl;
		objRemovebyName();
	}
}

void ControlTower::changePlaneHeight(string name, int newHeight) 
{
	//try {
		for (int i = 0; i < _objList.size(); i++)
		{
			if (_objList[i].name == name)
			{
				_objList[i].currKoor._altitude = newHeight; 

				cout << "Name Found and Changed" << endl;

				printObj(_objList[i]);
				return;
			}
		}
		//throw name + ", Not found - Altitude Change failed";
	//} catch (const char* msg)
	//{
	//	cerr << msg << endl;
	//}
}


void ControlTower::broadcastHeightChange(string name, int newHeight) 
{
	//Broadcaster should notify all objects needed.
	broadcastAllHeightChange(name, newHeight);

}


string printKoor(koordinates k)
{
	string resString;
	resString.append("Longtitude:	" + to_string(k._longtitude) + "\n");
	resString.append("Latitude:		" + to_string(k._latitude) + "\n");
	resString.append("Altitude:		" + to_string(k._altitude) + "\n");
	return resString;
}

