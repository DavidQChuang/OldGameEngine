#pragma once
#include "ParticleSystem.h"

class PlayerPS : public ParticleSystem {
public:
	PlayerPS(int);
	bool ParticleMovement(Particle&);
	void AdditionalCreate(float, Particle&);
};