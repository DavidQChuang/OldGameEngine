#include "PlayerBS.h"
PlayerBulletSystem::PlayerBulletSystem() {
}
PlayerBulletSystem::~PlayerBulletSystem() {
}
PlayerBulletSystem::PlayerBulletSystem(int x) {
	m_Bullets = new Bullet[x];
	m_bMax = x;
	m_Active = 0;
	m_Texture = 0;
}
void PlayerBulletSystem::BulletMovement(Bullet& b) {
	switch (b.type) {
	case 0:
		//480 pix/sec
		b.velY = -10;
		break;
	case 1:
		b.velY = -20;
		break;
	case 2:
		if (b.data == 1) {
			b.velX = -5;
		} else if (b.data == 2){
			b.velX = 5;
		}
		b.velY = -15;
		break;
	}
}