#pragma once

#include "stdafx.h"
#include "TexturedRect.h"
#include "Timer.h"
#include "ShaderClass.h"
#include <random>
#include "D3DClass.h"
#include <sstream>

class ParticleSystem {
protected:
	struct Particle {
		float x;
		float y;
		float velX;
		float velY;
		float height;
		float width;
		double lifestart;
		int lifetime;
		DirectX::XMFLOAT4 color;
		float data;
	};
public:
	ParticleSystem(int);
	ParticleSystem(const ParticleSystem&);
	~ParticleSystem();

	void SetParameters(int, int, int, int, int, int);
	void SetParameters(int, int, int, int, int, int, int, int);

	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ShaderClass*);
	void Create();
	void Create(int, int);
	void Create(int, int, int);
	void Create(int, int, int, int);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int);
	void Shutdown();
	 
protected:
	virtual bool ParticleMovement(Particle&) = 0;
	virtual void AdditionalCreate(float, Particle&) = 0;
	int m_pMax, m_Active;
	Particle* particles;
	int m_x, m_y, m_width, m_height;
	int m_Lifetime, m_LifeRandom;
	int m_Generate, m_GenRandom;
	float m_Time;
	float m_lastTime;

	TexturedRect* m_Texture;
	Timer* m_Timer;
};