#include "TitlePS.h"
TitlePS::TitlePS(int x, int y, int max, int lifetime, int lifeRandom, int gen, int genRand)
	: ParticleSystem::ParticleSystem(x, y, max, lifetime, lifeRandom, gen, genRand) {
}
TitlePS::TitlePS(int x, int y, int width, int height, int max, int lifetime, int lifeRandom, int gen, int genRand)
	: ParticleSystem::ParticleSystem(x, y, width, height, max, lifetime, lifeRandom, gen, genRand) {
}
bool TitlePS::ParticleMovement(Particle& particle) {
	particle.velX = sin((particle.lifestart-m_Timer->getTime())/100)*3 + 2;
	particle.color = DirectX::XMFLOAT4(((particle.y - 600) / 240) + 0.1f, 1.0f - ((int)particle.lifestart % 10) / 20, 0.f, 1.0f);
	if (((-2)*((m_Timer->getTime() - particle.lifestart) / 1000) + 2) <= 0) {
		return false;
	}
	particle.width = particle.height = (-2)*((m_Timer->getTime() - particle.lifestart)/1000) + 2;
	return true;
}