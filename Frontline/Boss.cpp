#include "Boss.h"
bool Boss::Frame(double time) {
	return false;
}

bool Boss::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename, char* bgFilename,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight, int spriteAmount) {
	bool result;
	m_Texture = new TexturedSpritesheet();
	if (!m_Texture) {
		return false;
	}
	result = m_Texture->Initialize(device, deviceContext,
		textureFilename,
		screenWidth, screenHeight, imageWidth, imageHeight, spriteAmount);
	if (!result) {
		return false;
	}
	m_Background = new TexturedSpritesheet();
	if (!m_Background) {
		return false;
	}
	result = m_Background->Initialize(device, deviceContext,
		textureFilename,
		screenWidth, screenHeight, imageWidth, imageHeight, spriteAmount);
	if (!result) {
		return false;
	}
	return true;
}
bool Boss::Render(ID3D11DeviceContext* deviceContext) {
	return m_Texture->Render(deviceContext, m_x, m_y);
}
void Boss::Shutdown() {
	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	if (m_Background) {
		m_Background->Shutdown();
		delete m_Background;
		m_Background = 0;
	}
}