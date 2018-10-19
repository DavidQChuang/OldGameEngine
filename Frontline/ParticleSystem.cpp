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
	m_Texture = 0;
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
	m_Texture = 0;
}

ParticleSystem::ParticleSystem(const ParticleSystem& other) {
}

ParticleSystem::~ParticleSystem() {
}

bool ParticleSystem::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight) {
	bool result;
	m_Texture = new TexturedRect();
	if (!m_Texture) {
		return false;
	}
	result = m_Texture->Initialize(device, deviceContext,
		textureFilename, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f),
		screenWidth, screenHeight, imageWidth, imageHeight);
	if (!result) {
		return false;
	}
	m_Timer->Start();

	m_lastTime = m_Timer->getTime();
	return true;
}

void ParticleSystem::SetX(int x) {
	m_x = x;
}

void ParticleSystem::SetY(int y) {
	m_y = y;
}

bool ParticleSystem::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ShaderClass* shader) {
	DirectX::XMMATRIX matrix;
	bool result;
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
		particle.x += particle.velX * (m_Timer->getTime() - m_lastTime) / 16;
		particle.y += particle.velY * (m_Timer->getTime() - m_lastTime) / 16;

		matrix = XMMatrixScaling(particle.width,particle.height, 1.f) * XMMatrixTranslation(particle.x - 400 + m_Texture->m_imageWidth / 2, -particle.y + 300 - m_Texture->m_imageHeight / 2, 0.f);
		//m_Texture->Resize(m_Texture->m_originalImageWidth * particle.width, m_Texture->m_originalImageHeight * particle.height);
		m_Texture->Render(direct3d->GetDeviceContext(), (int)particle.x, (int)particle.y, particle.color);
		result = shader->m_ColorTextureShader->Render(direct3d->GetDeviceContext(), m_Texture->GetIndexCount(), matrix, viewMatrix, orthoMatrix, m_Texture->GetTexture());
		if (!result) {
			return false;
		}
	}
	m_lastTime = m_Timer->getTime();
	return true;
}

void ParticleSystem::Shutdown() {
	if (particles) {
		delete particles;
	}
	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
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
		AdditionalCreate(distribution(generator), particles[m_Active]);
		m_Active++;
	}
}

void ParticleSystem::Create(int velX, int velY, int bottom, int top) {
	std::random_device generator;
	std::uniform_real_distribution<float> distribution(bottom, top);
	
	if (m_Active < m_pMax) {
		if (m_width > 0 && m_height > 0) {
			particles[m_Active].x = (rand() % (m_width + m_Texture->m_imageWidth)) + m_x - m_Texture->m_imageWidth;
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
		particles[m_Active].data = distribution(generator) / 32;
		m_Active++;
	}
}