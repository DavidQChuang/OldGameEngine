#include "BulletSystem.h"
BulletSystem::BulletSystem() {
}
BulletSystem::BulletSystem(int x) {
	m_Max = x;
	m_Active = 0;
	m_Texture = 0;
	m_on = true;
}
BulletSystem::~BulletSystem() {
}

bool BulletSystem::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int imageWidth, int imageHeight, int images) {
	bool result;
	m_Bullets = new MetatypeDataBullet[m_Max];

	m_Texture = new TexturedSpritesheet();
	if (!m_Texture) {
		return false;
	}
	result = m_Texture->Initialize(device, deviceContext,
		textureFilename, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f),
		imageWidth, imageHeight, images);
	if (!result) {
		return false;
	}
	return true;
}
bool BulletSystem::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ColorTextureShader* shader, float elapsed) {
	DirectX::XMMATRIX matrix;
	for (int i = 0; i < m_Active; i++) {
		MetatypeDataBullet& bullet = m_Bullets[i];

		if (bullet.y <= -200 || bullet.y >= 800 || bullet.x <= -200 || bullet.y >= 1000) {
			DeleteInstance(i);
			continue;
		}
		if (m_on) {
			BulletMovement(bullet);
			//velX = pixels per 16.7ms(1 60fps frame) 
			//velX * 60 (distance traveled in 1 sec)
			//m_Timer->getTime() / 1000 (seconds passed)
			//simplified down
			bullet.x += bullet.velX * elapsed / 16;
			bullet.y += bullet.velY * elapsed / 16;
		}
		//(XM_PI/2)-(atan(bullet.velY/bullet.velX))
		float x = bullet.velX / sqrt((bullet.velX * bullet.velX) + (bullet.velY * bullet.velY));
		matrix = XMMatrixScaling(1.f, 1.f, 1.f);
		if (x != 0) matrix *= XMMatrixRotationZ(acos(x)-XM_PIDIV2);
		matrix *= XMMatrixTranslation(bullet.x - 400 + m_Texture->m_spriteWidth / 2, -bullet.y + 300 - m_Texture->m_imageHeight / 2, 0.f);

		m_Texture->SetSprite(direct3d->GetDeviceContext(), bullet.type);
		m_Texture->SetColor(direct3d->GetDeviceContext(), bullet.color);

		m_Texture->Render(direct3d->GetDeviceContext());
		shader->Render(direct3d->GetDeviceContext(), GetIndexCount(), matrix, viewMatrix, orthoMatrix, GetTextureResource());
	}
	return true;
}

void BulletSystem::Shutdown() {
	delete m_Bullets;
	m_Bullets = 0;

	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}
void BulletSystem::Create(float x, float y, DirectX::XMFLOAT4 color, int type) {
	if (m_Active < m_Max) {
		m_Bullets[m_Active].x = x;
		m_Bullets[m_Active].y = y;
		m_Bullets[m_Active].velX = 0;
		m_Bullets[m_Active].velY = 0;
		m_Bullets[m_Active].color = color;
		m_Bullets[m_Active].type = type;
		m_Bullets[m_Active].metatype = 0;
		m_Bullets[m_Active].data = BulletData(m_Active);
		m_Active++;
	}
}
void BulletSystem::Create(float x, float y, DirectX::XMFLOAT4 color, int type, int metatype) {
	if (m_Active < m_Max) {
		m_Bullets[m_Active].x = x;
		m_Bullets[m_Active].y = y;
		m_Bullets[m_Active].velX = 0;
		m_Bullets[m_Active].velY = 0;
		m_Bullets[m_Active].color = color;
		m_Bullets[m_Active].type = type;
		m_Bullets[m_Active].metatype = metatype;
		m_Bullets[m_Active].data = BulletData(m_Active);
		m_Active++;
	}
}
void BulletSystem::Create(float x, float y, float velX, float velY, DirectX::XMFLOAT4 color, int type) {
	if (m_Active < m_Max) {
		m_Bullets[m_Active].x = x;
		m_Bullets[m_Active].y = y;
		m_Bullets[m_Active].velX = velX;
		m_Bullets[m_Active].velY = velY;
		m_Bullets[m_Active].color = color;
		m_Bullets[m_Active].type = type;
		m_Bullets[m_Active].metatype = 0;
		m_Bullets[m_Active].data = BulletData(m_Active);

		m_Active++;
	}
}
void BulletSystem::Create(float x, float y, float velX, float velY, DirectX::XMFLOAT4 color, int type, int metatype) {
	if (m_Active < m_Max) {
		m_Bullets[m_Active].x = x;
		m_Bullets[m_Active].y = y;
		m_Bullets[m_Active].velX = velX;
		m_Bullets[m_Active].velY = velY;
		m_Bullets[m_Active].color = color;
		m_Bullets[m_Active].type = type;
		m_Bullets[m_Active].metatype = metatype;
		m_Bullets[m_Active].data = BulletData(m_Active);

		m_Active++;
	}
}
float BulletSystem::BulletData(int x) {
	return -1.f;
}