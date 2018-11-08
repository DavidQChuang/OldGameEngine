#pragma once

#include "TexturedRect.h"
class TexturedSpritesheet : public TexturedRect {
public:
	TexturedSpritesheet();
	TexturedSpritesheet(const TexturedSpritesheet&);
	~TexturedSpritesheet();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_DIMENSION, H_DIMENSION, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_COLORRGBA, H_DIMENSION, H_DIMENSION, int);

	void SetColor(ID3D11DeviceContext*, H_COLORRGBA);
	void SetSprite(ID3D11DeviceContext*, int);

	H_DIMENSION m_spriteWidth;

	int m_currentSprite;

	int m_spriteAmount;
protected:
	bool InitializeBuffers(ID3D11Device*);
	//bool UpdateBuffers(ID3D11DeviceContext*);
	//bool UpdateBuffers(ID3D11DeviceContext*, DirectX::XMFLOAT4);

	float m_spriteSize;
	inline DirectX::XMFLOAT2 TextureCoords(int);
};
DirectX::XMFLOAT2 TexturedSpritesheet::TextureCoords(int x) {
	switch (x) {
	case 0:
		return DirectX::XMFLOAT2(m_spriteSize * m_currentSprite,0.f);
		break;
	case 1:
		return DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 1.f);
		break;
	case 2:
		return DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 1.f);
		break;
	case 3:
		return DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 0.f);
		break;
	}
}