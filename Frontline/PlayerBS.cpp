#include "PlayerBS.h"
PlayerBulletSystem::PlayerBulletSystem() {
	m_Count = 0;
	m_Texture = 0;
	m_Max = 0;
	m_Active = true;
}
PlayerBulletSystem::~PlayerBulletSystem() {
}
const int pierce1 = 2;
const int pierce2 = 8;
const int pierce3 = 1;
void PlayerBulletSystem::movement(Entity& b) {
	switch (b.type) {
	case 0:
		//480 pix/sec
		b.color.w = 1.f * (b.data.x / pierce1);
		b.velY = -7;
		b.velX = sin(b.y / 50) * 2;
		break;
	case 1:
		b.color.w = 1.f * (b.data.x / pierce2);
		b.velY = -14;
		break;
	case 2:
		b.color.w = 1.f * (b.data.x / pierce3);
		b.velY = -10.5f;
		b.velX = b.data.y;
		break;
	}
}

Entity PlayerBulletSystem::data(Entity& entity) {
	switch (entity.type) {
	case 0:
		entity.data.x = pierce1;
		break;
	case 1:
		entity.data.x = pierce2;
		break;
	case 2:
		entity.data.x = pierce3;
		break;
	}
	return entity;
}