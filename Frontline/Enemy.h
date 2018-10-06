#pragma once

#include "stdafx.h"
#include "TexturedSpritesheet.h"
#include "Timer.h"
#include "textureshaderclass.h"
#include "D3DClass.h"
class EnemySystem {
public:
	struct Enemy {
		int type;
		float x;
		float y;
		DirectX::XMFLOAT4 color;
		int health;
	};
	EnemySystem();
	~EnemySystem();
	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, TextureShaderClass*, double);
	void Create(float, float, DirectX::XMFLOAT4, int);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, int, int);
	void Shutdown();

	void Delete(int);

	int GetActive();

	int GetIndexCount();


	Enemy GetEnemy(int);
	Enemy* GetEnemies();
	DirectX::XMFLOAT2* GetEnemiesCoords();

	ID3D11ShaderResourceView* GetTextureResource();
	TexturedSpritesheet* GetTexture();
protected:
	int m_bMax, m_Active;

	TexturedSpritesheet* m_Texture;
	Enemy* m_Enemies;

	DirectX::XMFLOAT2 EnemyMovement(Enemy&);
	bool CheckCollision(DirectX::XMFLOAT2);
};