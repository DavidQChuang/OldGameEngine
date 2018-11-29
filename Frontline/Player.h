#pragma once
#include "stdafx.h"
#include "Input.h"
#include "Options.h"
#include "PlayerBS.h"
#include "TexturedSpritesheet.h"
#include "PlayerPS.h"

class Player {
public:
	Player(Input*, int, int);

	bool Frame(bool, float);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, int, int, int);

	inline bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX);
	inline bool RenderBullets(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*);

	void Shutdown();

	int m_speed;

	int m_BulletType;
	int m_Ability;

	int m_hp, m_mp;

	Input* m_Input;

	float m_x, m_y;
	TexturedSpritesheet* m_Texture;

	inline int GetSpriteNumber();
	
	inline int GetIndexCount();
	inline int GetBulletIndexCount();

	inline ID3D11ShaderResourceView* GetBulletTextureResource();
	inline TexturedSpritesheet* GetBulletTexture();

	inline ID3D11ShaderResourceView* GetTextureResource();

	inline DirectX::XMFLOAT2 GetBulletCoords(int);

	PlayerBulletSystem* m_Bullets;

	PlayerPS* m_PlayerParticles;
protected:
	float lastTime;
	float elapsedTime;
	float bulletTime;

	bool* m_keys;
	bool* m_lastKeys;

	int state;
	float gap;
	int bulletOffset;
	milliseconds bulletSpawn;
};


int Player::GetSpriteNumber() {
	return m_Texture->m_currentSprite;
}

bool Player::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix) {
	m_Texture->Render(direct3d->GetDeviceContext());
	return true;
}
bool Player::RenderBullets(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ColorTextureShader* shader) {
	return m_Bullets->Render(direct3d, viewMatrix, orthoMatrix, shader, elapsedTime);
}

int Player::GetIndexCount() {
	return m_Texture->m_indexCount;
}
int Player::GetBulletIndexCount() {
	return m_Bullets->GetIndexCount();
}
ID3D11ShaderResourceView* Player::GetTextureResource() {
	return m_Texture->m_Texture->GetTexture();
}
ID3D11ShaderResourceView* Player::GetBulletTextureResource() {
	return m_Bullets->GetTextureResource();
}
TexturedSpritesheet* Player::GetBulletTexture() {
	return m_Bullets->GetTexture();
}
DirectX::XMFLOAT2 Player::GetBulletCoords(int x) {
	return m_Bullets->GetBulletCoords(x);
}