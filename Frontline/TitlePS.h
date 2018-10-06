#pragma once
#include "ParticleSystem.h"

class TitlePS : public ParticleSystem {
public:
	TitlePS(int, int, int, int, int, int, int);
	TitlePS(int, int, int, int, int, int, int, int, int);
	bool ParticleMovement(Particle&);
};