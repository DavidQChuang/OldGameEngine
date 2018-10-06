#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	System* systemclass;
	bool result;


	// Create the system object.
	systemclass = new System;
	if (!systemclass) {
		return 0;
	}

	// Initialize and run the system object.
	result = systemclass->Initialize();
	if (result) {
		systemclass->Run();
	}

	// Shutdown and release the system object.
	systemclass->Shutdown();
	delete systemclass;
	systemclass = 0;

	return 0;
}