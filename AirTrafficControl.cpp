#pragma once

#include "./DummyAirPlane.h"
#include "Signals2.h"

// AirTrafficControl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

vector<Plane> tmpList;
Airspace tmpAir = Airspace();
ControlTower CT = ControlTower(tmpList, tmpAir);
//ControlTower* ptrCT= &CT;

void changeHeightFunction(ControlTower* ptrCT,string name, int newheight)
{
    cout << "Hello world" << endl;
    ptrCT->changePlaneHeight(name, newheight);
    ptrCT->printAllObj();
    cout << "Test ended" << endl;
}


int main()
{
    std::cout << "Start Air Traffic Control\n";

    vector<Plane> tmpList;
    Airspace tmpAir = Airspace(); 
    ControlTower CT = ControlTower(tmpList, tmpAir);

    boost::signals2::signal<void(ControlTower*,string, int)> sig;
    sig.connect(&changeHeightFunction);

    Communications com(&CT);
    //com.ChangeHeightSignal.connect(&changeHeightFunction);
    /*
    signalfunctor func;
    func.ct = &CT;
    func.name = "DC123";
    func.newhieght = 9001;
    */

    Plane P1 = Plane("DC123");
    Plane P2 = Plane("AC130");
    Plane P3 = Plane("RCXD10");
    
    CT.objHandle(P1);
    CT.objHandle(P2);
    CT.objHandle(P3);
    CT.objRemovebyName();
    //CT.printAllObj();

    cout << "The test" << endl;

    //CT.changePlaneHeight("DC123", 9001);
    sig(&CT,"DC123", 9001);

    //boost::detail::Sleep(200);
    CT.printAllObj();


}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
