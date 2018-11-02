#pragma once

#include "InstanceSystem.h"
class EntitySystem : public EntitySystem {
	virtual struct Instance {
		int type;
		float x;
		float y;
		H_COLORRGBA color;
	};
public:
	EntitySystem();
	~EntitySystem();
	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*, double);
	void Create(float, float, DirectX::XMFLOAT4, int, double);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, DirectX::XMFLOAT4(), int, int, int);
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

	DirectX::XMFLOAT2 EnemyMovement(int);
	bool CheckCollision(int, DirectX::XMFLOAT2, int);
	int m_lastSpawnTime;
	int m_delta;
};