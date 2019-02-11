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

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, Entity*);
	void Shutdown();

	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*, float);

	void CreateEntity(Entity);
	void DeleteEntity(int);

	virtual DirectX::XMFLOAT3 CreateData(Entity) = 0;

	/////////////
	// Inlines
	/////////////
	inline void SetActive(bool); // Sets if this EntitySystem is active or not.

	inline int GetCount();

	inline DirectX::XMFLOAT2 GetEntityCoords(int);

	inline TexturedSpritesheet* GetTexture();
	inline int GetIndexCount();
	inline ID3D11ShaderResourceView* GetTextureResource();

	inline void TimestepEntity(int, float);

	/////////////
	// Variables
	/////////////
	bool m_Active;

	int m_Count;
	int m_Max;

	Entity* m_Entities;
protected:
	TexturedSpritesheet* m_Texture;

	virtual bool deletion(Entity&) = 0;
	virtual void movement(Entity&) = 0;
	virtual void modification(D3DClass*, Entity&, DirectX::XMMATRIX&) = 0;
};

void EntitySystem::TimestepEntity(int id, float time) {
	movement(m_Entities[id]);
	m_Entities[id].x += m_Entities[id].velX * time / 16;
	m_Entities[id].y += m_Entities[id].velY * time / 16;
}


void EntitySystem::SetActive(bool on) { m_Active = on; }


int EntitySystem::GetCount() { return m_Count; }

DirectX::XMFLOAT2 EntitySystem::GetEntityCoords(int x) {
	return DirectX::XMFLOAT2(m_Entities[x].x, m_Entities[x].y);
}


TexturedSpritesheet* EntitySystem::GetTexture() { return m_Texture; }

int EntitySystem::GetIndexCount() { return m_Texture->m_indexCount; }

ID3D11ShaderResourceView* EntitySystem::GetTextureResource() { return m_Texture->m_Texture->GetTexture(); }