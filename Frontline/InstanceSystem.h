#pragma once

#include "stdafx.h"
#include "TexturedSpritesheet.h"
#include "Timer.h"
#include "colortextureshader.h"
#include "D3DClass.h"
class InstanceSystem {
	virtual struct Instance {
		float x;
		float y;
	};
	virtual struct ColorInstance {
		float x;
		float y;
		H_RGBA color;
	};
public:
	InstanceSystem();
	~InstanceSystem();
	virtual bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*, double);
	void Create(Instance);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_DIMENSION, H_DIMENSION, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, H_RGBA, H_DIMENSION, H_DIMENSION, int);
	void Shutdown();

	void MoveEnemy(int, float);

	void Delete(int);

	int GetActive();

	int GetIndexCount();

	void SetState(bool);
	void SetRatePerFrame(float);

	DirectX::XMINT2 GetInstanceCoords(int);

	ID3D11ShaderResourceView* GetTextureResource();
	TexturedSpritesheet* GetTexture();

	bool m_on;
protected:
	int m_bMax, m_Active;

	TexturedSpritesheet* m_Texture;
	Enemy* m_Enemies;

	int m_lastSpawnTime;
	int m_delta;
};