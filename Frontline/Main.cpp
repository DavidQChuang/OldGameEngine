#include "System.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	System* system;
	bool result;

	system = new System();
	if (!system) {
		return false;
	}

	// Initialize and run the system object.
	result = system->Initialize();
	if (result) {
		system->Run();
	}
	// Shutdown and release the system object.
	system->Shutdown();

	delete system;
	system = 0;
	return false;
}