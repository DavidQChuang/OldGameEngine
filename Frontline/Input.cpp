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
	return;
}

void Input::KeyUp(unsigned int input) {
	m_keys[input] = 3;
	return;
}