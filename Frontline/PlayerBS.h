#pragma once
#include "BulletSystem.h"
class PlayerBulletSystem : public BulletSystem {
public:
	PlayerBulletSystem();
	~PlayerBulletSystem();
	PlayerBulletSystem(int);
	void BulletMovement(Bullet&);
protected:
	int m_counter;
};