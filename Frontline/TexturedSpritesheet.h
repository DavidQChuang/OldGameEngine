#pragma once

#include "TexturedRect.h"
class TexturedSpritesheet : public TexturedRect {
public:
	TexturedSpritesheet();
	TexturedSpritesheet(const TexturedSpritesheet&);
	~TexturedSpritesheet();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_DIMENSION, H_DIMENSION, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_COLORRGBA, H_DIMENSION, H_DIMENSION, int);
	bool Render(ID3D11DeviceContext*, int, int);
	bool Render(ID3D11DeviceContext*, int, int, DirectX::XMFLOAT4);
	
	void SetSprite(int);

	H_DIMENSION m_spriteWidth;

	int m_currentSprite;
	int m_previousSprite;

	int m_spriteAmount;
protected:
	bool UpdateBuffers(ID3D11DeviceContext*);
	bool UpdateBuffers(ID3D11DeviceContext*, DirectX::XMFLOAT4);

	float m_spriteSize;


};