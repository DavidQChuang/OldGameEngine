#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(int x, int y, int max, int lifetime, int lifeRandom, int gen, int genRand) {
	particles = new Particle[max];
	m_x = x;
	m_y = y;
	m_width = 0;
	m_height = 0;
	m_pMax = max;
	m_Active = 0;
	m_Lifetime = lifetime;
	m_LifeRandom = lifeRandom;
	m_Generate = gen;
	m_GenRandom = genRand;
	m_Timer = new Timer();
	m_Particle = 0;
	start = false;
}
ParticleSystem::ParticleSystem(int x, int y, int width, int height, int max, int lifetime, int lifeRandom, int gen, int genRand) {
	particles = new Particle[max];
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_pMax = max;
	m_Active = 0;
	m_Lifetime = lifetime;
	m_LifeRandom = lifeRandom;
	m_Generate = gen;
	m_GenRandom = genRand;
	m_Timer = new Timer();
	m_Particle = 0;
	start = false;
}

ParticleSystem::ParticleSystem(const ParticleSystem& other) {
}

ParticleSystem::~ParticleSystem() {
}

bool ParticleSystem::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight) {
	bool result;
	m_Particle = new TexturedRect();
	if (!m_Particle) {
		return false;
	}
	result = m_Particle->Initialize(device, deviceContext,
		textureFilename,
		screenWidth, screenHeight, imageWidth, imageHeight);
	if (!result) {
		return false;
	}
	return true;
}

void ParticleSystem::SetX(int x) {
	m_x = x;
}

void ParticleSystem::SetY(int y) {
	m_y = y;
}

bool ParticleSystem::Render(D3DClass* direct3d, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, TextureShaderClass* shader) {
	bool result;
	if (!start) {
		start = true;
		m_Timer->Start();
	}
	for (int i = 0; i < m_Active; i++) {
		Particle& particle = particles[i];

		result = ParticleMovement(particle);
		if (m_Timer->getTime() >= particle.lifestart + particle.lifetime || !result) {
			for (int x = i+1; x < m_Active; x++) {
				particles[x-1] = particles[x];
			}
			m_Active--;
			continue;
		}
		particle.x += particle.velX;
		particle.y += particle.velY;

		m_Particle->Resize(m_Particle->m_originalImageWidth * particle.width, m_Particle->m_originalImageHeight * particle.height);
		m_Particle->Render(direct3d->GetDeviceContext(), (int)particle.x, (int)particle.y, particle.color);
		result = shader->Render(direct3d->GetDeviceContext(), m_Particle->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Particle->GetTexture());
		if (!result) {
			return false;
		}

	}
	return true;
}

void ParticleSystem::Shutdown() {
	if (particles) {
		
	}
	if (m_Particle) {
		m_Particle->Shutdown();
		delete m_Particle;
		m_Particle = 0;
	}
}
void ParticleSystem::Create() {
	if (m_Active < m_pMax) {
		if (m_width > 0 && m_height > 0) {
			particles[m_Active].x = (rand() % (m_width)) + m_x;
			particles[m_Active].y = (rand() % (m_height)) + m_y;
		}
		else {
			particles[m_Active].x = m_x;
			particles[m_Active].y = m_y;
		}
		particles[m_Active].velX = 0;
		particles[m_Active].velY = 0;
		particles[m_Active].lifestart = m_Timer->getTime();
		particles[m_Active].lifetime = m_Lifetime;
		particles[m_Active].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		particles[m_Active].width = 1.0f;
		particles[m_Active].height = 1.0f;
		m_Active++;
	}
}

void ParticleSystem::Create(int velX, int velY) {
	if (m_Active < m_pMax) {
		if (m_width > 0 && m_height > 0) {
			particles[m_Active].x = (rand() % (m_width)) + m_x;
			particles[m_Active].y = (rand() % (m_height)) + m_y;
		}
		else {
			particles[m_Active].x = m_x;
			particles[m_Active].y = m_y;
		}
		particles[m_Active].velX = velX;
		particles[m_Active].velY = velY;
		particles[m_Active].lifestart = m_Timer->getTime();
		particles[m_Active].lifetime = m_Lifetime;
		particles[m_Active].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		particles[m_Active].width = 1.0f;
		particles[m_Active].height = 1.0f;
		m_Active++;
	}
}

void ParticleSystem::Create(int velX, int velY, int top) {
	std::random_device generator;
	std::uniform_real_distribution<float> distribution(0, top);
	if (m_Active < m_pMax) {
		if (m_width > 0 && m_height > 0) {
			particles[m_Active].x = (rand() % (m_width)) + m_x;
			particles[m_Active].y = (rand() % (m_height)) + m_y;
		}
		else {
			particles[m_Active].x = m_x;
			particles[m_Active].y = m_y;
		}
		particles[m_Active].velX = velX + distribution(generator);
		particles[m_Active].velY = velY + distribution(generator);
		particles[m_Active].lifestart = m_Timer->getTime();
		particles[m_Active].lifetime = m_Lifetime;
		particles[m_Active].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		particles[m_Active].width = 1.0f;
		particles[m_Active].height = 1.0f;
		m_Active++;
	}
}

void ParticleSystem::Create(int velX, int velY, int bottom, int top) {
	std::random_device generator;
	std::uniform_real_distribution<float> distribution(bottom, top);
	
	if (m_Active < m_pMax) {
		if (m_width > 0 && m_height > 0) {
			particles[m_Active].x = (rand() % (m_width + m_Particle->m_imageWidth)) + m_x - m_Particle->m_imageWidth;
			particles[m_Active].y = (rand() % (m_height)) + m_y;
		}
		else {
			particles[m_Active].x = m_x;
			particles[m_Active].y = m_y;
		}
		particles[m_Active].velX = velX + distribution(generator);
		particles[m_Active].velY = velY + distribution(generator);
		particles[m_Active].lifestart = m_Timer->getTime();
		particles[m_Active].lifetime = m_Lifetime;
		particles[m_Active].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		particles[m_Active].width = 1.0f;
		particles[m_Active].height = 1.0f;
		m_Active++;
	}
}