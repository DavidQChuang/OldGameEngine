#pragma once
#include "BulletSystem.h"
class PlayerBulletSystem : public BulletSystem {
public:
	PlayerBulletSystem();
	~PlayerBulletSystem();
	PlayerBulletSystem(int);
	void BulletMovement(MetatypeDataBullet&);
	float BulletData(int);
};