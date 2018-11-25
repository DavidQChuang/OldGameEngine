#pragma once

#include "stdafx.h"
#include "TexturedSpritesheet.h"
#include "Timer.h"
#include "ColorTextureShader.h"
#include "D3DClass.h"
class BulletSystem {
public:
	struct MetatypeDataBullet {
		int type;
		int metatype;
		float x;
		float y;
		float velX;
		float velY;
		float data;
		DirectX::XMFLOAT4 color;
	};
	struct DoubleDataBullet {
		int type;
		float x;
		float y;
		float velX;
		float velY;
		float data;
		DirectX::XMFLOAT4 color;
	};
	BulletSystem();
	BulletSystem(int);
	~BulletSystem();
	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*, float);
	void Create(float, float, DirectX::XMFLOAT4, int);
	void Create(float, float, DirectX::XMFLOAT4, int, int);
	void Create(float, float, float, float, DirectX::XMFLOAT4, int);
	void Create(float, float, float, float, DirectX::XMFLOAT4, int, int);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int);
	void Shutdown();

	/////////////
	// Inlines
	/////////////
	inline void SetState(bool); // Sets if this BulletSystem is active (moving bullets) or not.

	inline int GetIndexCount();

	inline DirectX::XMFLOAT2 GetBulletCoords(int);

	inline ID3D11ShaderResourceView* GetTextureResource();
	inline TexturedSpritesheet* GetTexture();

	virtual float BulletData(int);
	inline void SetData(int, float);
	inline void MoveBullet(int, float);
	inline int GetActive();
	inline void DeleteInstance(int); // Deletes a bullet.

	/////////////
	// Variables
	/////////////
	bool m_on;
	MetatypeDataBullet* m_Bullets;
	int m_Max, m_Active;
protected:
	TexturedSpritesheet* m_Texture;

	virtual void BulletMovement(MetatypeDataBullet&) = 0;
};

void BulletSystem::SetData(int id, float data) {
	m_Bullets[id].data = data;
}
void BulletSystem::MoveBullet(int id, float time) {
	MetatypeDataBullet& bullet = m_Bullets[id];
	BulletMovement(m_Bullets[id]);
	bullet.x += bullet.velX * time / 10;
	bullet.y += bullet.velY * time / 10;
}

int BulletSystem::GetActive() {
	return m_Active; }

void BulletSystem::DeleteInstance(int b) {
	for (int x = b + 1; x < m_Active; x++) {
		m_Bullets[x - 1] = m_Bullets[x];
	}
	m_Active--;
}

DirectX::XMFLOAT2 BulletSystem::GetBulletCoords(int x) {
	return DirectX::XMFLOAT2(m_Bullets[x].x, m_Bullets[x].y); }

void BulletSystem::SetState(bool on) {
	m_on = on; }

int BulletSystem::GetIndexCount() {
	return m_Texture->m_indexCount; }

TexturedSpritesheet* BulletSystem::GetTexture() {
	return m_Texture; }

ID3D11ShaderResourceView* BulletSystem::GetTextureResource() {
	return m_Texture->m_Texture->GetTexture(); }