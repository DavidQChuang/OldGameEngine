#pragma once

#include "stdafx.h"
#include "TextureClass.h"

class TexturedRect {
protected:
	struct VertexType {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
		DirectX::XMFLOAT4 color;
	};
	struct ColoredVertexType {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
		DirectX::XMFLOAT4 color;
	};
	struct ColorVertexType {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};
public:
	enum ShaderType {
		COLOR_TYPE = 1,
		TEXTURE_TYPE = 2,
		COLOR_TEXTURE_TYPE = 4
	};
	TexturedRect();
	TexturedRect(int);
	TexturedRect(const TexturedRect&);
	~TexturedRect();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);
	bool Render(ID3D11DeviceContext*, int, int, DirectX::XMFLOAT4);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	int m_screenWidth, m_screenHeight;
	int m_imageWidth, m_imageHeight;
	int m_originalImageWidth, m_originalImageHeight;

	int m_shaderType;

	virtual void Resize();
	virtual void Resize(int, int);
protected:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	virtual bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	virtual bool UpdateBuffers(ID3D11DeviceContext*, int, int, DirectX::XMFLOAT4);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	DirectX::XMFLOAT4 m_Color;

	int m_posX, m_posY;
	int m_previousPosX, m_previousPosY;
};