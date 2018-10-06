#include "Timer.h"
Timer::Timer() {
	freq = { 0 };
	curr = { 0 };
	strt = { 0 };
}
void Timer::Start() {
	QueryPerformanceCounter(&strt);
}
double Timer::getTime() {
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&curr);
	return (curr.QuadPart - strt.QuadPart) * 1000.0 / freq.QuadPart;
}
double Timer::getStart() {
	return (strt.QuadPart * 1000.0) / freq.QuadPart;
}