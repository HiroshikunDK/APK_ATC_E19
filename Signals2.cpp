#pragma once
#include "Signals2.h"

using namespace std;

void Communications::ctChangeHeight(string name, int newHeight)
{
	ct->changePlaneHeight(name, newHeight);
}
