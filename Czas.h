#pragma once
#ifndef CZAS_H
#define CZAS_H


#include <iostream>
#include <chrono>



using namespace std;
using namespace std::chrono;

class Czas {
public:
	high_resolution_clock::time_point czasPoczatkowy;
	high_resolution_clock::time_point czasKoncowy;

	void czasStart();

	void czasStop();

	long czasWykonania();
};


#endif 
