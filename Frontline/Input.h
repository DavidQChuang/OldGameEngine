#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_
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

	bool OnKeyDown(unsigned int);
	bool OnKeyUp(unsigned int);
	bool IsKeyDown(unsigned int);
	bool IsLMouseDown();

	long m_mouseX, m_mouseY;

private:
	POINT m_cursorPos;
	int m_keys[256];
};

#endif