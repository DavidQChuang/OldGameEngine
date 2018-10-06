#pragma once

#include <windows.h>
class Timer {
public:
	Timer();
	void Start();
	double getTime();
	double getStart();
	LARGE_INTEGER freq;
	LARGE_INTEGER curr;
	LARGE_INTEGER strt;
protected:
};