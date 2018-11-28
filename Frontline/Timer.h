#pragma once

#include <windows.h>
class Timer {
public:
	Timer() {
		freq = { 0 };
		curr = { 0 };
		strt = { 0 };
	};
	void Start() {
		QueryPerformanceCounter(&strt);
		last = getTime();
	};
	inline float getTime() {
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&curr);
		return (curr.QuadPart - strt.QuadPart) * 1000.0f / freq.QuadPart;
	};
	inline float getStart() {
		return (strt.QuadPart * 1000.0f) / freq.QuadPart;
	};
	inline float getLast() {
		return last;
	};
	inline float getDelta() {
		return last - getTime();
	}
	void startFrame() {
		last = getTime();
	};
	inline float getSteps(float stepSize) {

	};
protected:
	LARGE_INTEGER freq;
	LARGE_INTEGER curr;
	LARGE_INTEGER strt;
	float last;
};
//constexpr Meters operator "" _m(long double mt){
//    return Meters{ Meters::PreventUsage{}, static_cast<double> mt };
//}