#include "PlayerBS.h"
PlayerBulletSystem::PlayerBulletSystem() {
}
PlayerBulletSystem::~PlayerBulletSystem() {
}
PlayerBulletSystem::PlayerBulletSystem(int x) {
	m_Bullets = new MetatypeDataBullet[x];
	m_Max = x;
	m_Active = 0;
	m_Texture = 0;
}
const int firstThing = 2;
const int secondThing = 8;
const int thirdThing = 1;
void PlayerBulletSystem::BulletMovement(MetatypeDataBullet& b) {
	switch (b.type) {
	case 0:
		//480 pix/sec
		b.color.w = 1.f * (b.data / firstThing);
		b.velY = -7;
		b.velX = sin(b.y / 50) * 2;
		break;
	case 1:
		b.color.w = 1.f * (b.data / secondThing);
		b.velY = -14;
		break;
	case 2:
		b.color.w = 1.f * (b.data / thirdThing);
		b.velY = -10.5f;
		b.velX = b.metatype;
		break;
	}
}

float PlayerBulletSystem::BulletData(int x) {
	switch (m_Bullets[x].type) {
	case 0:
		return firstThing;
		break;
	case 1:
		return secondThing;
		break;
	case 2:
		return thirdThing;
		break;
	}
}