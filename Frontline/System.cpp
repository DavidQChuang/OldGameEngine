#include "system.h"

System::System() {
	m_Input = 0;
	m_Graphics = 0;
}

System::System(const System& other) {
}

System::~System() {
}

bool System::Initialize() {
	int Width, Height;
	bool result;

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	Width = 0;
	Height = 0;

	// Initialize the windows api.
	InitializeWindows(Width, Height);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new Input;
	if (!m_Input) {
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass(m_Input);
	if (!m_Graphics) {
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(Width, Height, m_hwnd);
	if (!result) {
		return false;
	}

	return true;
}
void System::Shutdown() {
	// Release the graphics object.
	if (m_Graphics) {
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if (m_Input) {
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();

	return;
}

void Run(System system) {
	MSG msg;
	bool done;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done) {
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			// Otherwise do the frame processing.
			done = system.Frame() ? true : false;
		}

	}

	return;
}

bool System::Frame() {
	bool result;

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE)) {
		//return false;
	}

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if (!result) {
		return false;
	}

	m_Input->Update();
	return true;
}

LRESULT CALLBACK System::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
		// If a key is pressed send it to the input object so it can record that state.
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
		break;

		// Check if a key has been released on the keyboard.
	case WM_KEYUP:
		// If a key is released then send it to the input object so it can unset the state for that key.
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
		break;

		// Any other messages send to the default message handler as our application won't make use of them.
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
		break;
	}
}
void System::InitializeWindows(int& screenWidth, int& screenHeight) {
	WNDCLASSEXW wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	RECT wr;    // set the size, but not the position


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"B O I";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = static_cast<HICON>(LoadImage(wc.hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, LR_DEFAULTCOLOR));
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(wc.hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassExW(&wc);

	int windowstate = 1;

	wr = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	//m_Options->GetOption("WINDOW_STATE", windowstate);
	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (windowstate == 0) {
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;

		// Create the window with the screen settings and get the handle to it.
		AdjustWindowRect(&wr, WS_POPUP, FALSE);    // adjust the size
		m_hwnd = CreateWindowExW(WS_EX_APPWINDOW,
			m_applicationName,
			m_applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY,
			wr.right - wr.left, wr.bottom - wr.top,
			NULL,
			NULL,
			m_hinstance,
			NULL);
	}
	else if (windowstate == 1) {
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;
		wr = { 0, 0, 800, 600 };
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - (wr.right - wr.left)) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - (wr.bottom - wr.top)) / 2;

		// Create the window with the screen settings and get the handle to it.
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size
		m_hwnd = CreateWindowExW(WS_EX_APPWINDOW,
			m_applicationName,
			m_applicationName,
			WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
			posX, posY,
			wr.right - wr.left, wr.bottom - wr.top,
			NULL,
			NULL,
			m_hinstance,
			NULL);
	}
	else if (windowstate == 2) {
		// If borderless windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;
		wr = { 0, 0, 800, 600 };

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - (wr.right - wr.left)) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - (wr.bottom - wr.top)) / 2;

		// Create the window with the screen settings and get the handle to it.
		AdjustWindowRect(&wr, WS_POPUP, FALSE);    // adjust the size
		m_hwnd = CreateWindowExW(WS_EX_APPWINDOW,
			m_applicationName,
			m_applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY,
			wr.right - wr.left, wr.bottom - wr.top,
			NULL,
			NULL,
			m_hinstance,
			NULL);
	}
	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);

	return;
}
void System::ShutdownWindows() {
	// Show the mouse cursor.
	ShowCursor(true);
	int windowstate;
	//m_Options->GetOption("WINDOW_STATE", windowstate);
	windowstate = 1;
	// Fix the display settings if leaving full screen mode.
	if (windowstate == 0) {
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClassW(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {
		// Check if the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

		// Check if the window is being closed.
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;

		// All other messages pass to the message handler in the system class.
	default:
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		break;
	}
}
