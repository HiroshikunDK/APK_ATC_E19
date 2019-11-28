#pragma once
#include <stdlib.h>
#include <iostream>
#include <boost/signals2/signal.hpp>
//https://www.boost.org/doc/libs/1_55_0/more/getting_started/windows.html
//Look at step 4.1 - this should make it work 

using namespace std;

struct koordinates
{
	double _longtitude = 5;
	double _latitude = 5;
	double _altitude = 5; // In Metric  

	inline bool operator <(const koordinates& rhs)
	{
		if ((_latitude < rhs._latitude) && (_longtitude < rhs._longtitude))
		{
			return true;
		}
		else { return false; }
	}
	inline bool operator <=(const koordinates& rhs)
	{
		if ((_latitude <= rhs._latitude) && (_longtitude <= rhs._longtitude))
		{
			return true;
		}
		else { return false; }
	}
	inline bool operator >(const koordinates& rhs)
	{
		if ((_latitude > rhs._latitude) && (_longtitude > rhs._longtitude))
		{
			return true;
		}
		else { return false; }
	}
	inline bool operator >=(const koordinates& rhs)
	{
		if ((_latitude >= rhs._latitude) && (_longtitude >= rhs._longtitude))
		{
			return true;
		}
		else { return false; }
	}
	inline bool operator ==(const koordinates& rhs)
	{
		if ((_latitude == rhs._latitude) && (_longtitude == rhs._longtitude))
		{
			return true;
		}
		else { return false; }
	}
};

class Plane
{
public:
	koordinates prevKoor;
	koordinates currKoor;
	
private:
	string name = "none";
	string type = "none";
};

class Airspace
{
public:
	Airspace() {}
	virtual bool isInsideAirSpace(Plane);
private:
	string name = "none";
	koordinates uppeKoor;
	koordinates loweKoor;
};

bool Airspace::isInsideAirSpace(const Plane k)
{
	if (this->loweKoor <= k.currKoor)
	{
		if (this->uppeKoor >= k.currKoor) { return true; }
		else { return false; }
	}
	else { return false; }
};

class ControlTower
{
public:
	ControlTower(vector<Plane> newObjList, Airspace newAirSpace)
	{
		_objList = newObjList;
		_airSpace = newAirSpace;
	};
	ControlTower() {};

	void collisionDetection();
	void changeCourse();
	void printObj();
	void objRecieve();
	void objUpdate();
	void objRemove();

private:
	Airspace _airSpace = Airspace();
	vector<Plane> _objList = vector<Plane>();
};