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

	bool Frame(bool, double);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, int, int, int);

	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX);
	bool RenderBullets(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*);

	void Shutdown();

	int m_speed;

	int m_BulletType;
	int m_Ability;

	int m_hp, m_mp;

	Input* m_Input;

	float m_x, m_y;
	TexturedSpritesheet* m_Texture;

	int GetSpriteNumber();
	
	int GetIndexCount();
	int GetBulletIndexCount();

	ID3D11ShaderResourceView* GetBulletTextureResource();
	TexturedSpritesheet* GetBulletTexture();

	ID3D11ShaderResourceView* GetTextureResource();

	DirectX::XMFLOAT2* GetBullets();

	PlayerBulletSystem* m_Bullets;

	PlayerPS* m_PlayerParticles;
protected:
	double lastTime;
	double elapsedTime;
	double bulletTime;
	double lastEstTime;

	bool* m_keys;
	bool* m_lastKeys;

	int state;
	float gap;
	int bulletOffset;
};

