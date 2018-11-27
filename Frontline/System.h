#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#define WIN32_HEADERS

//#include "Options.h"
#include "GraphicsClass.h"

#include "resource.h"

class System {
public:
	System();
	System(const System&);
	~System();

	bool Initialize();
	void Shutdown();
	friend void Run(System);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input* m_Input;
	GraphicsClass* m_Graphics;
	Options* m_Options;
};
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static System* ApplicationHandle = 0;


#endif