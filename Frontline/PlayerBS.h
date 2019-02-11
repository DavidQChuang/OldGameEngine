#pragma once
#include "BulletSystem.h"
class PlayerBulletSystem : public BulletSystem {
public:
	PlayerBulletSystem();
	~PlayerBulletSystem();
	void movement(Entity&);
	float[3] CreateData(Entity);
};