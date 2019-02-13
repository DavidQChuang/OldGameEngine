#pragma once
#include "BulletSystem.h"
class PlayerBulletSystem : public BulletSystem {
public:
	PlayerBulletSystem();
	~PlayerBulletSystem();
	void movement(Entity&);
	DirectX::XMFLOAT3 setdata(Entity);
};