#include "PlayerPS.h"
PlayerPS::PlayerPS(int max)
	: ParticleSystem::ParticleSystem(max) {
}
bool PlayerPS::ParticleMovement(Particle& particle) {
	particle.width = particle.height = (-2)*((m_Timer->getTime() - particle.lifestart) / 1100) + 2;
	particle.velX = sin((particle.lifestart - m_Timer->getTime()) / 100) * 3 + 2;
	if (particle.y > 400) {
		//((particle.y - 600) / 120) + 1.f - particle.data
		particle.color = DirectX::XMFLOAT4((m_Timer->getTime() - particle.lifestart)/1000, (m_Timer->getTime() - particle.lifestart)/1000, 1.f, 1.0f);
	}
	else {
		float n = -((particle.y - 470) / 600);
		if (n < 0) n = 0;
		particle.color = DirectX::XMFLOAT4(n, n, n, 1.0f);
	}
	if (((-2)*((m_Timer->getTime() - particle.lifestart) / 1000) + 2) <= 0) {
		return false;
	}

	return true;
}
void PlayerPS::AdditionalCreate(float random, Particle& particle) {
}