#pragma once

#include "TextureClass.h"
#include "Engine.h"
class TexturedRect {
public:
	TexturedRect();
	TexturedRect(const TexturedRect&);
	~TexturedRect();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, H_RGBA, H_DIMENSION, H_DIMENSION);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_DIMENSION, H_DIMENSION);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_RGBA, H_DIMENSION, H_DIMENSION);

	void Shutdown();

	void Render(ID3D11DeviceContext*);

	// Get m_screenWidth & height from Engine.h instead of recieving it and storing it.
	// int m_screenWidth, m_screenHeight;

	H_2DSHADERTYPE m_shaderType;

	void SetPos(H_POS, H_POS);
	void SetSize(H_SCALE, H_SCALE);
	void SetRot(H_ROT);
	virtual void SetColor(ID3D11DeviceContext*, H_RGBA);
	// void ChangeColor(DirectX::XMFLOAT4);

	int m_vertexCount, m_indexCount;
	// Constant - size of original image.
	H_DIMENSION m_imageWidth, m_imageHeight;
	// Variable - properties of image to be rendered.
	// Stored
	H_POS m_posX, m_posY;
	H_SCALE m_scaleX, m_scaleY;
	H_ROT m_rot;
	H_RGBA m_Color;

	TextureClass* m_Texture;
protected:
	virtual bool InitializeBuffers(ID3D11Device*);

	void ShutdownBuffers();

	// Loads image texture from file.
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
};