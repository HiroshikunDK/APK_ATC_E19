﻿#pragma once

#include <condition_variable>
#include <thread>
#include "./DummyAirPlane.h"
#include "Signals2.h"
#include "RandomPlaneGenerator.h"

// AirTrafficControl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//Setup af kontrol objekter - skal være global
vector<Plane> tmpList;
Airspace tmpAir = Airspace();
ControlTower CT = ControlTower(tmpList, tmpAir);

//oprettelse af signal og dets parameter -skal være global
boost::signals2::signal<void(ControlTower*, string, int)> sig;
boost::signals2::signal<void(ControlTower*, Plane)> PlaneSignal;


//disse funktioner kaldes og wrapper andre klassers implementering af  change height. 
void changeHeightFunction(ControlTower* ptrCT1, string name, int newheight)
{
    cout << "Hello world" << endl;
    ptrCT1->changePlaneHeight(name, newheight);
    ptrCT1->printAllObj();
    cout << "Test ended" << endl;
}

void transmitPlaneData(ControlTower* ptrCT, Plane newPlane)
{
    //cout << "Hello world" << endl;
    ptrCT->objHandle(newPlane);
    //ptrCT->printAllObj();
    cout << "New plane handled" << endl;
}

// 
void broadcastAllHeightChange(string name, int newheigh)
{
    sig(&CT, "DC123", 9001);
}

void broadcastPlaneData(Plane newPlane)
{
    PlaneSignal(&CT, newPlane);
}

void InitializeSystem() 
{   
    //forbind en funktion til signalet
    sig.connect(&changeHeightFunction);
    PlaneSignal.connect(&transmitPlaneData);
    
    RandomPlaneGenerator rpg("");
    cout << "The test" << endl;
    rpg.GeneratePlanes();
    //Communications com(&CT);
    //com.ChangeHeightSignal.connect(&changeHeightFunction);
    /*
    signalfunctor func;
    func.ct = &CT;
    func.name = "DC123";
    func.newhieght = 9001;
    */
    //sigAlt.connect(func()); 

    /*
    Plane P1 = Plane("DC123");
    Plane P2 = Plane("AC130");
    Plane P3 = Plane("RCXD10");

    broadcastPlaneData(P1);
    broadcastPlaneData(P2);
    broadcastPlaneData(P3);

    CT.objRemovebyName();
    */
    //CT.printAllObj();

   

    //CT.changePlaneHeight("DC123", 9001);
    //sig(&CT,"DC123", 9001);
    //sigAlt("DC123", 9001);
    //CT.broadcastHeightChange("DC123", 9001);
    //boost::detail::Sleep(200);
    //CT.printAllObj();

}

int main()
{
    std::cout << "Start Air Traffic Control\n";

    InitializeSystem();


    


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
