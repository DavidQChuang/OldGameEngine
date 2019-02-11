#pragma once
#include "BulletSystem.h"
class PlayerBulletSystem : public BulletSystem {
public:
	// Extends Entity, contains a additional variables XMFLOAT4 color, float velX, and float velY.

	PlayerBulletSystem();
	~PlayerBulletSystem();
	PlayerBulletSystem(int);
	void BulletMovement(MetatypeDataBullet&);
	float BulletData(int);
};