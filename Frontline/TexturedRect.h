#pragma once

#include "TextureClass.h"
#include "Engine.h"
class TexturedRect {
public:
	TexturedRect();
	TexturedRect(const TexturedRect&);
	~TexturedRect();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, DirectX::XMFLOAT4, int, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, DirectX::XMFLOAT4, int, int);

	void Shutdown();

	bool Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	int m_imageWidth, m_imageHeight;
	int m_screenWidth, m_screenHeight;

	void SetShaderType(int);
	int m_shaderType;

	void SetPos(H_POS, H_POS);
	void SetSize(H_SCALE, H_SCALE);
	void SetRot(H_ROT);
	void SetColor(H_COLORRGBA);
	//void ChangeColor(DirectX::XMFLOAT4);

	H_POS m_posX, m_posY;
	H_SCALE m_scaleX, m_scaleY;
	H_ROT m_rot;
	H_COLORRGBA m_Color;
protected:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	virtual bool UpdateBuffers(ID3D11DeviceContext*);
	virtual bool UpdateBuffers(ID3D11DeviceContext*, DirectX::XMFLOAT4);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	DirectX::XMFLOAT4 m_previousColor;
};