#pragma once
#include <stdlib.h>
#include <map>
#include "./DummyAirPlane.h"
#include "AirTrafficControl.h"
#include <Rpc.h>
#include <random>
#include <string>

using namespace std;

class RandomPlaneGenerator {

private:
	map<string, koordinates > nameToDirectionMap;
	vector<Plane> existingPlanes;
	vector<Plane>::iterator ite;
public:
	const string enviroment = "Production";
	void GeneratePlanes();

	RandomPlaneGenerator(string envir) {
		enviroment = envir;
		existingPlanes.assign(7, Plane("default"));
	}

	//https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c Based on the answers in this thread
	std::string random_string(std::string::size_type length)
	{
		static auto& chrs = "0123456789"
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		thread_local static std::mt19937 rg{ std::random_device{}() };
		thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

		std::string s;

		s.reserve(length);

		while (length--)
			s += chrs[pick(rg)];

		return s;
	}

};