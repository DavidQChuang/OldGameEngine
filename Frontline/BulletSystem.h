#pragma once

#include "stdafx.h"
#include "TexturedSpritesheet.h"
#include "Timer.h"
#include "ColorTextureShader.h"
#include "D3DClass.h"
#include "EntitySystem.h"
class BulletSystem : public EntitySystem {
public:
	BulletSystem();
	~BulletSystem();

	bool deletion(Entity&);
	virtual void movement(Entity&) = 0;
	void modification(D3DClass*, Entity&, DirectX::XMMATRIX&);

	virtual DirectX::XMFLOAT3 setdata(Entity) = 0;
};