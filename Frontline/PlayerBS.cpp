#include "PlayerBS.h"
PlayerBulletSystem::PlayerBulletSystem() {
	m_Count = 0;
	m_Texture = 0;
	m_Max = 0;
	m_Active = true;
}
PlayerBulletSystem::~PlayerBulletSystem() {
}
const int firstThing = 2;
const int secondThing = 8;
const int thirdThing = 1;
void PlayerBulletSystem::movement(Entity& b) {
	switch (b.type) {
	case 0:
		//480 pix/sec
		b.color.w = 1.f * (b.data[0] / firstThing);
		b.velY = -7;
		b.velX = sin(b.y / 50) * 2;
		break;
	case 1:
		b.color.w = 1.f * (b.data[0] / secondThing);
		b.velY = -14;
		break;
	case 2:
		b.color.w = 1.f * (b.data[0] / thirdThing);
		b.velY = -10.5f;
		b.velX = b.data[1];
		break;
	}
}

float PlayerBulletSystem::BulletData(int x) {
	switch (m_Bullets[x].data[1]) {
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