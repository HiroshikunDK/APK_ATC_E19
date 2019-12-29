#pragma once
#include <stdlib.h>
#include <iostream>
#include <boost/signals2/signal.hpp>
#include "DummyAirPlane.h"

//https://www.boost.org/doc/libs/1_55_0/more/getting_started/windows.html
//Look at step 4.1 - this should make it work 

using namespace std;

struct signalfunctor
{
	ControlTower* ct;
	int newhieght;
	string name;
	void operator()() const
	{
		cout << "Testing Functor" << endl;
		ct->changePlaneHeight(name, newhieght);
	}
};


class Communications 
{
public:
	Communications(ControlTower* ctPtr)
	{
		ct = ctPtr;
	}
	boost::signals2::signal<void(ControlTower,string, int)> ChangeHeightSignal;
	boost::signals2::signal<Plane()> ObjectDataSignal; //use whatever implementation you want

	void ctChangeHeight(string, int);

private:
	ControlTower* ct;
};
