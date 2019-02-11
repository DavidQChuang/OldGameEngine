#pragma once

#include "stdafx.h"
#include "TexturedSpritesheet.h"
#include "Timer.h"
#include "ColorTextureShader.h"
#include "D3DClass.h"

// This class is not meant to be like ParticleSystem or any UI elements. It uses a list in its SceneClass as storage for each instance.
class EntitySystem {
public:
	EntitySystem();
	~EntitySystem();
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
	inline void SetState(bool); // Sets if this EntitySystem is active (moving bullets) or not.

	inline int GetIndexCount();

	inline DirectX::XMFLOAT2 GetBulletCoords(int);

	inline ID3D11ShaderResourceView* GetTextureResource();
	inline TexturedSpritesheet* GetTexture();

	/*virtual float BulletData(int);
	inline void SetData(int, float);
	inline void MoveBullet(int, float);
	inline int GetActive();
	inline void DeleteInstance(int); // Deletes a bullet.*/

	inline int GetActive();
	template <class entityType>
	inline void DeleteInstance(int,	entityType*);
	/////////////
	// Variables
	/////////////
	bool m_on;

	int m_Active;
protected:
	TexturedSpritesheet* m_Texture;

	virtual void BulletMovement(MetatypeDataBullet&) = 0;
};

void EntitySystem::SetData(int id, float data) {
	m_Bullets[id].data = data;
}
void EntitySystem::MoveBullet(int id, float time) {
	MetatypeDataBullet& bullet = m_Bullets[id];
	BulletMovement(m_Bullets[id]);
	bullet.x += bullet.velX * time / 10;
	bullet.y += bullet.velY * time / 10;
}

int EntitySystem::GetActive() {
	return m_Active;
}

template <class entityType>
void EntitySystem::DeleteInstance(int i, entityType* list) {
	for (int x = i + 1; x < m_Active; x++) {
		list[x - 1] = list[x];
	}
	m_Active--;
}

DirectX::XMFLOAT2 EntitySystem::GetBulletCoords(int x) {
	return DirectX::XMFLOAT2(m_Bullets[x].x, m_Bullets[x].y);
}

void EntitySystem::SetState(bool on) {
	m_on = on;
}

int EntitySystem::GetIndexCount() {
	return m_Texture->m_indexCount;
}

TexturedSpritesheet* EntitySystem::GetTexture() {
	return m_Texture;
}

ID3D11ShaderResourceView* EntitySystem::GetTextureResource() {
	return m_Texture->m_Texture->GetTexture();
}