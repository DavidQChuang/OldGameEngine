#pragma once

#include "stdafx.h"
#include "TextureClass.h"

class InstancedTexturedRect {
protected:
	struct InstanceType {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};
	struct VertexType {
		DirectX::XMFLOAT2 texture;
	};
public:
	InstancedTexturedRect(int);
	InstancedTexturedRect(const InstancedTexturedRect&);
	~InstancedTexturedRect();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);
	bool Render(ID3D11DeviceContext*, int, int);

	void AddInstance(int, int);
	//void CheckInstances();

	int GetIndexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView* GetTexture();

	virtual void Resize();
	virtual void Resize(int, int);
	//void ChangeColor(DirectX::XMFLOAT4);

	int m_screenWidth, m_screenHeight;
	int m_imageWidth, m_imageHeight;
	int m_originalImageWidth, m_originalImageHeight;
protected:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	virtual bool UpdateBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
	int m_vertexCount, m_indexCount, m_instanceCount;

	InstanceType* m_Instances;

	TextureClass* m_Texture;
	DirectX::XMFLOAT4 m_Color;
	DirectX::XMFLOAT4 m_PreviousColor;

	int m_instanceCountMax;
	//int m_previousPosX, m_previousPosY;
};