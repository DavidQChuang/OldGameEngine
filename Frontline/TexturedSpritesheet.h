#pragma once

#include "stdafx.h"
#include "TextureClass.h"
#include "TexturedRect.h"
class TexturedSpritesheet : public TexturedRect {
public:
	TexturedSpritesheet();
	TexturedSpritesheet(const TexturedSpritesheet&);
	~TexturedSpritesheet();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, int, int);
	bool Render(ID3D11DeviceContext*, int, int);
	bool Render(ID3D11DeviceContext*, int, int, DirectX::XMFLOAT4);
	
	void SetSprite(int);

	void Resize();
	void Resize(int, int);

	int m_spriteWidth;
	int m_originalSpriteWidth;

	int m_currentSprite;
	int m_previousSprite;

	int m_spriteAmount;
protected:
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	bool UpdateBuffers(ID3D11DeviceContext*, int, int, DirectX::XMFLOAT4);

	float m_spriteSize;


};