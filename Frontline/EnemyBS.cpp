#include "EnemyBS.h"
EnemyBulletSystem::EnemyBulletSystem() {
}
EnemyBulletSystem::~EnemyBulletSystem() {
}
EnemyBulletSystem::EnemyBulletSystem(int c) {
	m_Bullets = new MetatypeDataBullet[c];
	m_Active = 0;
	m_Texture = 0;
}
void EnemyBulletSystem::BulletMovement(MetatypeDataBullet& b) {
	switch(b.type) {
	case 0:
		b.velY += 1;
		break;
	}
}