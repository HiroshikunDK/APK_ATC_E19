#pragma once

#include <condition_variable>
#include <thread>
#include <chrono>
#include <mutex>
#include "ControlTower.h"
#include "Signals2.h"
#include "RandomPlaneGenerator.h"

// AirTrafficControl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

void ClearScreen()
{
    cout << string(50, '\n');
}

#include <iostream>

//Setup af kontrol objekter - skal være global
vector<Plane> tmpList;
Airspace tmpAir = Airspace();
ControlTower CT = ControlTower(tmpList, tmpAir);

//oprettelse af den globale generator
RandomPlaneGenerator rpg("");

//oprettelse af signal og dets parameter -skal være global
boost::signals2::signal<void(ControlTower*, string, int)> ChangeHieghtSignal;
boost::signals2::signal<void(RandomPlaneGenerator*, string, int)> ChangeHieghtSignalRanGen;
boost::signals2::signal<void(ControlTower*, Plane)> PlaneSignal;


//disse funktioner kaldes og wrapper andre klassers implementering af  change height. 
void changeHeightFunction(ControlTower* ptrCT1, string name, int newheight)
{
    //cout << "Hello world" << endl;
    ptrCT1->changePlaneHeight(name, newheight);
    ptrCT1->printAllObj();
    //cout << "Test ended" << endl;
}

void changeHeightFunctionRanGen(RandomPlaneGenerator* ptrCT1, string name, int newheight)
{
    //cout << "Hello world" << endl;
    ptrCT1->ChangeAltitude(name, newheight);
    //ptrCT1->printAllObj();
    //cout << "Test ended" << endl;
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
    ChangeHieghtSignal(&CT, name, newheigh);
    ChangeHieghtSignalRanGen(&rpg, name, newheigh);
}

void broadcastPlaneData(Plane newPlane)
{
    PlaneSignal(&CT, newPlane);
}


// Starting Thread functions and Conditional Waits

void threadPrint(mutex& m, condition_variable& cond, condition_variable& inputcond, bool& flag, ControlTower& CTR)
{
    while (1) {
        unique_lock<mutex> ul(m);
        cond.wait(ul, [&] {return flag; }); // hvis flaget er falsk lad koden passere
        //flag = true;
        cout << "Print T called" << endl;
        //if(colission is true){flag = true}
        ClearScreen();
        CTR.printAllObj();
        string com = CTR.isPlanesTooClose();
        if(com !="none") 
        {
            cout << "Suggested to change height on Plane: " << com << endl;
            inputcond.notify_all();
        }
        else 
        {
            cond.notify_all();
            flag = false;
        }
    }
}

void threadPlaneSignals(mutex& m, condition_variable& cond, condition_variable& inputcond, bool& flag)
{
    while (1) 
    {
        unique_lock<mutex> ul(m);
        cond.wait(ul, [&] {return !flag; }); // hvis flaget er falsk lad koden passere
        
        cout << "Plane sig T called" << endl;
        //if(colission is true){flag = true}
        rpg.GeneratePlanes(); //sikkert at generer fly
    
        flag = true;
        cond.notify_all();
    }
}

void threadChangeHeight(mutex& m, condition_variable& cond, condition_variable& inputcond, bool& flag, ControlTower& CTR)
{
    while (1) 
    {

    unique_lock<mutex> ul(m);
    inputcond.wait(ul, [&] {return flag; });
    //flag = false;
    cout << "Height Change T called" << endl;

    vector<Plane> tmpList;
    //flag = CTR.isPlanesTooClose(tmpList);

    string name;
    cout << "Handle colliding airplanes" << endl;
    cout << "Plane Name: ";
    cin >> name;

    int delta;
    cout<< endl << "Plane ascend(+)/decend(-): ";
    cin >> delta;

    CTR.broadcastHeightChange(name, delta);
    flag = false;
    //flag = false;
    cond.notify_all();
    }
}

void InitializeSystem() 
{   
    //forbind en funktion til signalet
    ChangeHieghtSignal.connect(&changeHeightFunction);
    ChangeHieghtSignalRanGen.connect(&changeHeightFunctionRanGen);
    PlaneSignal.connect(&transmitPlaneData);

    mutex m;
    mutex inM;
    condition_variable cond;
    condition_variable inputCond;
    bool flag = false;
  
    thread t0(threadPrint, ref(m), ref(cond), ref(inputCond), ref(flag),ref(CT));
    thread t1(threadPlaneSignals, ref(m), ref(cond), ref(inputCond), ref(flag));
    thread t2(threadChangeHeight, ref(m), ref(cond), ref(inputCond), ref(flag), ref(CT));
    
    t0.join();
    t1.join();
    t2.join();
    //CT.printAllObj();
    

    /*
    while (cond.wait_for(lck, chrono::seconds(1)) == cv_status::timeout) 
    { 
        cout << "No Input detected " << endl;
        rpg.GeneratePlanes();
    }*/


    cout << "The test Ended" << endl;
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
