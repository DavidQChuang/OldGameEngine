#pragma once
#include "stdafx.h"
#include "Input.h"
#include "Options.h"
#include "PlayerBS.h"
#include "TexturedSpritesheet.h"
class Boss {
public:
	bool Frame(double);
	bool Render(ID3D11DeviceContext*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, int, int, int, int, int);

	void Shutdown();

	void Spawn();

	int phase;

	int hp;
	int lives;

	float m_x;
	float m_y;

	TexturedSpritesheet* m_Texture;
	TexturedSpritesheet* m_Background;
};

