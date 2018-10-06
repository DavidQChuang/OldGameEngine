#include "Input.h"

Input::Input() {
}


Input::Input(const Input& other) {
}


Input::~Input() {
}

void Input::Update() {
	int i;
	for (i = 0; i<256; i++)
	{
		if(m_keys[i] == 2){
			m_keys[i] = 1;
		}
		if (m_keys[i] == 3) {
			m_keys[i] = 0;
		}
	}
}
void Input::Initialize() {
	int i;

	//Create a place for all of the keys.
	for (i = 0; i<256; i++)
	{
		m_keys[i] = 0;
	}

	return;
}


void Input::KeyDown(unsigned int input) {
	if (m_keys[input] == 1) {
		return;
	}
	else {
		m_keys[input] = 2;
	}
	/*
	std::wstringstream noob;
	noob << input;
	OutputDebugString(noob.str().c_str());*/
	return;
}

void Input::KeyUp(unsigned int input) {
	m_keys[input] = 3;
	return;
}
bool Input::OnKeyDown(unsigned int key) {
	if (m_keys[key] == 2) {
		return m_keys[key];
	}
	else return false;
}
bool Input::OnKeyUp(unsigned int key) {
	if (m_keys[key] == 3) {
		return m_keys[key];
	}
	else return false;
}
bool Input::IsKeyDown(unsigned int key) {
	if (m_keys[key] == 1 || m_keys[key] == 2) {
		return m_keys[key];
	}
	else return false;
}

bool Input::IsLMouseDown() {
	if (GetKeyState(VK_LBUTTON) < 0) return true;
}
