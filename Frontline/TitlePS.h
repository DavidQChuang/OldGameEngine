#pragma once
#include "ParticleSystem.h"

class TitlePS : public ParticleSystem {
public:
	TitlePS(int);
	bool ParticleMovement(Particle&);
	void AdditionalCreate(float, Particle&);
};