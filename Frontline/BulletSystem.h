#pragma once

#include "stdafx.h"
#include "TexturedSpritesheet.h"
#include "Timer.h"
#include "ColorTextureShader.h"
#include "D3DClass.h"
class BulletSystem {
public:
	struct Bullet {
		int type;
		float x;
		float y;
		float velX;
		float velY;
		int data;
		DirectX::XMFLOAT4 color;
	};
	BulletSystem();
	BulletSystem(int);
	~BulletSystem();
	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*, float);
	void Create(float, float, DirectX::XMFLOAT4, int);
	void Create(float, float, float, float, DirectX::XMFLOAT4, int);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, int, int);
	void Shutdown();

	void Delete(int);

	int GetActive();

	int GetIndexCount();

	Bullet GetBullet(int);
	DirectX::XMFLOAT2* GetBulletsCoords();

	ID3D11ShaderResourceView* GetTextureResource();
	TexturedSpritesheet* GetTexture();

	void MoveBullet(int, float);

	void SetState(bool);
	bool m_on;
protected:
	int m_bMax, m_Active;

	TexturedSpritesheet* m_Texture;
	Bullet* m_Bullets;

	virtual void BulletMovement(Bullet&) = 0;
};