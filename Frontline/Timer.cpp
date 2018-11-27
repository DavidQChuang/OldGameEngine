#include "Timer.h"
Timer::Timer() {
	freq = { 0 };
	curr = { 0 };
	strt = { 0 };
}

void Timer::Start() {
	QueryPerformanceCounter(&strt);
	last = getTime();
}