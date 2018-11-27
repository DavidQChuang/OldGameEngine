#pragma once

#include <windows.h>
class Timer {
public:
	Timer();
	void Start();
	inline float getTime();
	inline float getStart();
	LARGE_INTEGER freq;
	LARGE_INTEGER curr;
	LARGE_INTEGER strt;
	float last;
};

float Timer::getTime() {
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&curr);
	last = (curr.QuadPart - strt.QuadPart) * 1000.0f / freq.QuadPart;
	return last;
}
float Timer::getStart() {
	return (strt.QuadPart * 1000.0f) / freq.QuadPart;
}