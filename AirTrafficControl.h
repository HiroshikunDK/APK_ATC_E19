#pragma once


void InitializeSystem();
void changeHeightFunction(ControlTower*, string, int);
void transmitPlaneData(ControlTower* ptrCT, Plane newPlane);
void broadcastAllHeightChange(string, int);
void broadcastPlaneData(Plane newPlane);