#pragma once
#include <stdlib.h>
#include <iostream>
#include <boost/signals2/signal.hpp>
//https://www.boost.org/doc/libs/1_55_0/more/getting_started/windows.html
//Look at step 4.1 - this should make it work 

using namespace std;

struct koordinates
{
	double _longtitude = 0; // In Metric?
	double _latitude = 0; // In Metric?
	double _altitude = 0; // In Metric?

	inline bool operator <(const koordinates& rhs)
	{
		if ((_latitude < rhs._latitude) && (_longtitude < rhs._longtitude))
		{
			return true;
		}
		else { return false; }
	}

	koordinates operator -(const koordinates& rhs)
	{
		koordinates res;
		res._latitude = subtract(_latitude, rhs._latitude);
		res._longtitude = subtract(_longtitude, rhs._longtitude);
		res._altitude = _altitude;
		return res;
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

	template<typename T> T subtract(T a, T b)  //Template Metaprogramming
	{
		return (a - b);
	}
};


class Plane
{
	friend class ControlTower;
public:
	Plane(string nm)
	{
		name = nm;
		koordinates kp;
		kp._altitude = 12345;
		kp._latitude = 12345;
		kp._longtitude = 12345;

		prevKoor = kp;

		koordinates kc;
		kc._altitude = 98745;
		kc._latitude = 98745;
		kc._longtitude = 98745;

		prevKoor = kc;
	};
	void commandPlane(string cmd) 
	{
		cout << "Command: " << cmd << ", by Plane: " << name << endl;
	}

	koordinates prevKoor;
	koordinates currKoor;
	string name = "none";
private:
	string type = "none";
};


class Airspace
{
public:
	Airspace() 
	{
		koordinates LowKoor;
		LowKoor._altitude = 1000;
		LowKoor._latitude = 1000;
		LowKoor._longtitude = 1000;

		loweKoor = LowKoor;

		koordinates HighKoor;
		HighKoor._altitude = 99999;
		HighKoor._latitude = 99999;
		HighKoor._longtitude = 99999;

		uppeKoor = HighKoor;
	}

	bool isInsideAirSpace(const Plane k)
	{
		if (this->loweKoor <= k.currKoor)
		{
			if (this->uppeKoor >= k.currKoor) { return true; }
			else { return false; }
		}
		else { return false; }
	};

private:
	string name = "none";
	koordinates uppeKoor;
	koordinates loweKoor;
};



class ControlTower
{
	//friend class Communications;
public:
	ControlTower(vector<Plane> newObjList, Airspace newAirSpace)
	{
		_objList = newObjList;
		_airSpace = newAirSpace;
	};
	ControlTower() {};


	string isPlanesTooClose();
	vector<Plane> collisionDetection(vector<Plane> inVector); //iterator
	//void initilizeCom(planespawner)
	bool objExistInVec(const vector<Plane> inVector, Plane obj); //  
	void changeCourse(); //metaprogrammering?
	void printObj(Plane obj); // 
	void printAllObj();
	void objHandle(Plane obj); //c
	void objRecieve(Plane obj);
	void objUpdate(Plane obj);
	void objRemove(Plane obj);
	bool checkInputChars(string rawS);
	void objRemovebyName();
	void changePlaneHeight(string name, int newHeight);
	void broadcastHeightChange(string name, int newHeight);

private:
	Airspace _airSpace = Airspace();
	vector<Plane> _objList = vector<Plane>();
	
	
};

string printKoor(koordinates k);
//Kan bruges overalt
template<typename t1, class Func>
string myToString(t1 obj, Func f)
{
	string res = f(obj);
	return res;
};