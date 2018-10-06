#ifndef _OPTIONSCLASS_H_
#define _OPTIONSCLASS_H_
#define WIN32_HEADERS
#include <windows.h>
#include <sstream>
#include <iostream>
#include <fstream>
class Options {
public:
	Options();

	void SetDefaults();

	int GetOptionI(std::string);
	float GetOptionF(std::string);
	bool GetOptionB(std::string);

	void SetOption(std::string, std::string);
	static int Scene;
	static int WIDTH;
	static int HEIGHT;
private:
	int WINDOWS_STATE = 1;
	bool VSYNC = true;
	float SCREENDEPTH = 1000.0f;
	float SCREEN_NEAR = 0.1f;
	std::fstream config;

};
#endif