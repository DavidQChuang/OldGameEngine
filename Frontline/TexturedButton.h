#ifndef _GUIBUTTON_H_
#define _GUIBUTTON_H_
#include "stdafx.h"
#include <sstream>
#include "TexturedSpritesheet.h"

class TexturedButton : public TexturedSpritesheet {
public:
	bool Clicked(HWND, long, long);
	bool Hovered(HWND, long, long);

	ID3D11ShaderResourceView* GetTexture(HWND, long, long);
private:
	POINT m_cursorPos;
	HWND m_hwnd;
};
#endif