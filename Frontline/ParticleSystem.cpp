#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(int max) {
	particles = new Particle[max];

	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
	m_Lifetime = 0;
	m_LifeRandom = 0;
	m_Generate = 0;
	m_GenRandom = 0;
	m_pMax = max;

	m_Active = 0;

	m_Timer = new Timer();
	m_Texture = 0;
}

ParticleSystem::ParticleSystem(const ParticleSystem& other) {
}

ParticleSystem::~ParticleSystem() {

}

//(int x, int y, int lifetime, int lifeRandom, int gen, int genRand)
void ParticleSystem::SetParameters(int x, int y, int lifetime, int lifeRandom, int gen, int genRand) {
	m_x = x;
	m_y = y;
	m_width = 0;
	m_height = 0;
	m_Lifetime = lifetime;
	m_LifeRandom = lifeRandom;
	m_Generate = gen;
	m_GenRandom = genRand;
}
//(int x, int y, int width, int height, int lifetime, int lifeRandom, int gen, int genRand)
void ParticleSystem::SetParameters(int x, int y, int width, int height, int lifetime, int lifeRandom, int gen, int genRand) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_Lifetime = lifetime;
	m_LifeRandom = lifeRandom;
	m_Generate = gen;
	m_GenRandom = genRand;
}
bool ParticleSystem::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int imageWidth, int imageHeight) {
	bool result;
	m_Texture = new TexturedRect();
	if (!m_Texture) {
		return false;
	}
	result = m_Texture->Initialize(device, deviceContext,
		textureFilename, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f),
		imageWidth, imageHeight);
	if (!result) {
		return false;
	}
	m_Timer->Start();

	m_lastTime = m_Timer->getTime();
	return true;
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

		matrix = XMMatrixScaling(particle.width,particle.height, 1.f) * XMMatrixTranslation(particle.x - 400 + m_Texture->m_imageWidth / 2, -particle.y + 300 - m_Texture->m_imageHeight / 2, 0.f);
		//m_Texture->Resize(m_Texture->m_originalImageWidth * particle.width, m_Texture->m_originalImageHeight * particle.height);
		m_Texture->SetColor(direct3d->GetDeviceContext(),particle.color);
		particle.x += particle.velX * (m_Timer->getTime() - m_lastTime) / 16;
		particle.y += particle.velY * (m_Timer->getTime() - m_lastTime) / 16;
		m_Texture->Render(direct3d->GetDeviceContext());
		result = shader->m_ColorTextureShader->Render(direct3d->GetDeviceContext(), m_Texture->m_indexCount, matrix, viewMatrix, orthoMatrix, m_Texture->m_Texture->GetTexture());
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
		AdditionalCreate(distribution(generator), particles[m_Active]);
		m_Active++;
	}
}