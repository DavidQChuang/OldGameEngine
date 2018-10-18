#pragma once

#include "TextureClass.h"
#include "Engine.h"
class TexturedRect {
protected:
	struct ColorVertexType {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};
	struct VertexType {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};
	struct ColoredVertexType {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
		DirectX::XMFLOAT4 color;
	};
public:
	TexturedRect();
	TexturedRect(const TexturedRect&);
	~TexturedRect();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, DirectX::XMFLOAT4, int, int, int, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, DirectX::XMFLOAT4, int, int, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);
	bool Render(ID3D11DeviceContext*, int, int, DirectX::XMFLOAT4);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	int m_screenWidth, m_screenHeight;
	int m_imageWidth, m_imageHeight;
	int m_originalImageWidth, m_originalImageHeight;

	void SetShaderType(int);
	int m_shaderType;

	virtual void Resize();
	virtual void Resize(int, int);
	//void ChangeColor(DirectX::XMFLOAT4);
	int m_posX, m_posY;
	DirectX::XMFLOAT4 m_Color;
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
	DirectX::XMFLOAT4 m_previousColor;

	int m_previousPosX, m_previousPosY;
};