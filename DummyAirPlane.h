#pragma once
#include <stdlib.h>
#include "../../boost_1_71_0/boost_1_71_0/libs/" //my filepath to downloaded boost

using namespace std;

struct koordinates
{
	double _longtitude = 5;
	double _latitude = 5;
	double _altitude = 5;
};

class Plane
{
public:
	koordinates previousKoordinates;
	koordinates currentKoordinates;
private:
	string name = "none";
	string type = "none";

};

/*
class ControlFunctions 
{
public:
	virtual bool collisionDetection();
	virtual void isInsideAirspace();
	virtual void changeCourse();
	virtual void printObj();
	virtual void objRecieve();
	virtual void objUpdate();
	virtual void objRemove();
}
*/

template <class T : Plane, class A>
class ControlTower : ControlFunctions
{
public:
	ControlTower(T newObjList, A newAirSpace) 
	{
		_objList = newObjList;
		_airSpace = newAirSpace;
	};

	bool collisionDetection();
	void isInsideAirspace();
	void changeCourse();
	void printObj();
	void objRecieve();
	void objUpdate();
	void objRemove();
	
private:
	A _airSpace = null;
	vector<T> _objList = null;
	vector<T>::iterator ptr; //brug af iterator.
}
