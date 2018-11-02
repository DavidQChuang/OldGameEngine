#include "TexturedButton.h"
bool TexturedButton::Clicked(HWND hwnd, long mouseX, long mouseY) {
	if (GetKeyState(VK_LBUTTON) < 0 && Hovered(hwnd, mouseX, mouseY)) return true; else return false;
}

bool TexturedButton::Hovered(HWND hwnd, long mouseX, long mouseY) {
	if (mouseX >= m_posX && mouseX <= (m_posX + m_spriteWidth) && mouseY >= m_posY && mouseY <= (m_posY + m_imageHeight)) return true; else return false;
}

ID3D11ShaderResourceView* TexturedButton::GetTexture(HWND hwnd, long mouseX, long mouseY) {
	//if (Hovered(hwnd, mouseX, mouseY)) SetSprite(2); else SetSprite(1);
	return m_Texture->GetTexture();
}