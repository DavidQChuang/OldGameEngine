#pragma once

#include "stdafx.h"
#include "TexturedRect.h"
#include "Timer.h"
#include "ColorTextureShader.h"
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
		int data;
	};
public:
	ParticleSystem(int, int, int, int, int, int, int);
	ParticleSystem(int, int, int, int, int, int, int, int, int);
	ParticleSystem(const ParticleSystem&);
	~ParticleSystem();
	bool Render(D3DClass*, DirectX::XMMATRIX, DirectX::XMMATRIX, ColorTextureShader*);
	void Create();
	void Create(int, int);
	void Create(int, int, int);
	void Create(int, int, int, int);

	void SetX(int);
	void SetY(int);

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, int, int, int, int);
	void Shutdown();
	 
protected:
	virtual bool ParticleMovement(Particle&) = 0;

	int m_pMax, m_Active;
	Particle* particles;
	int m_x, m_y, m_width, m_height;
	int m_Lifetime, m_LifeRandom;
	int m_Generate, m_GenRandom;
	double m_Time;
	bool start;

	TexturedRect* m_Texture;
	Timer* m_Timer;
};