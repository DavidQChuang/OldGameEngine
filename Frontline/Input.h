#pragma once

#include "stdafx.h"
class Input {
public:
	Input();
	Input(const Input&);
	~Input();

	void Update();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	inline bool OnKeyDown(unsigned int);
	inline bool OnKeyUp(unsigned int);
	inline bool IsKeyDown(unsigned int);
	inline bool IsLMouseDown();

	long m_mouseX, m_mouseY;

private:
	POINT m_cursorPos;
	int m_keys[256];
};

bool Input::OnKeyDown(unsigned int key) {
	return m_keys[key] == 2;}

bool Input::OnKeyUp(unsigned int key) {
	return m_keys[key] == 3;}

bool Input::IsKeyDown(unsigned int key) {
	return m_keys[key] == 1 || m_keys[key] == 2;}

bool Input::IsLMouseDown() {
	return GetKeyState(VK_LBUTTON) < 0;}
