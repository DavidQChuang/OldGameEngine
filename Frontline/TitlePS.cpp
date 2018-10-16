#include "TitlePS.h"
TitlePS::TitlePS(int x, int y, int max, int lifetime, int lifeRandom, int gen, int genRand)
	: ParticleSystem::ParticleSystem(x, y, max, lifetime, lifeRandom, gen, genRand) {
}
TitlePS::TitlePS(int x, int y, int width, int height, int max, int lifetime, int lifeRandom, int gen, int genRand)
	: ParticleSystem::ParticleSystem(x, y, width, height, max, lifetime, lifeRandom, gen, genRand) {
}
bool TitlePS::ParticleMovement(Particle& particle) {
	particle.velX = sin((particle.lifestart - m_Timer->getTime()) / 100) * 3 + 2;
	if (particle.y > 300) {
		//((particle.y - 600) / 120) + 1.f - particle.data
		particle.color = DirectX::XMFLOAT4(((particle.y - 600) / 240) + 1.f, ((particle.y - 600) / 120) + 1.f - particle.data, 0.2f - particle.data, 1.0f);
	}
	else {
		float n = -((particle.y - 470) / 600);
		if (n < 0) n = 0;
		particle.color = DirectX::XMFLOAT4(n, n, n, 1.0f);
	}
	if (((-2)*((m_Timer->getTime() - particle.lifestart) / 1000) + 2) <= 0) {
		return false;
	}

	particle.width = particle.height = (-2)*((m_Timer->getTime() - particle.lifestart) / 1100) + 2;
	return true;
}
void TitlePS::AdditionalCreate(float random, Particle& particle) {
	particle.data = random / -40;
}