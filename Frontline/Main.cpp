#include "System.h"
#include <thread>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	System system;
	bool result;

	// Initialize and run the system object.
	result = system.Initialize();
	if (result) {
		Run(system);
	}
	// Shutdown and release the system object.
	system.Shutdown();
	return false;
}