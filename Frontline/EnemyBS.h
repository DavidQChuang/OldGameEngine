#pragma once
#include "BulletSystem.h"
class EnemyBulletSystem : public BulletSystem {
public:
	EnemyBulletSystem();
	~EnemyBulletSystem();
	EnemyBulletSystem(int);
	void BulletMovement(MetatypeDataBullet&);
};
