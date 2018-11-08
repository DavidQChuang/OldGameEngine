#include "BulletSystem.h"
BulletSystem::BulletSystem() {
}
BulletSystem::BulletSystem(int x) {
	m_Bullets = new Bullet[x];
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
	m_Texture = new TexturedSpritesheet();
	if (!m_Texture) {
		return false;
	}
	result = m_Texture->Initialize(device, deviceContext,
		textureFilename, DirectX::XMFLOAT4(1.f,1.f,1.f,1.f),
		imageWidth, imageHeight, images);
	if (!result) {
		return false;
	}
	return true;
}
bool BulletSystem::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ColorTextureShader* shader, float elapsed) {
	DirectX::XMMATRIX matrix;
	for (int i = 0; i < m_Active; i++) {
		Bullet& bullet = m_Bullets[i];

		if (bullet.y <= -200 || bullet.y >= 800 || bullet.x <= -200 || bullet.y >= 1000) {
			Delete(i);
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
			
		matrix = XMMatrixScaling(1.f,1.f,1.f) * XMMatrixRotationZ((XM_PI/2)-(atan(bullet.velY/bullet.velX))) * XMMatrixTranslation(bullet.x - 400 + m_Texture->m_spriteWidth / 2, -bullet.y + 300 - m_Texture->m_imageHeight / 2, 0.f);
		m_Texture->SetSprite(direct3d->GetDeviceContext(), bullet.type);
		m_Texture->Render(direct3d->GetDeviceContext());
		shader->Render(direct3d->GetDeviceContext(), GetIndexCount(), matrix, viewMatrix, orthoMatrix, GetTextureResource());
	}
	return true;
}
void BulletSystem::SetState(bool on) {
	m_on = on;
}
int BulletSystem::GetIndexCount() {
	return m_Texture->m_indexCount;
}
ID3D11ShaderResourceView* BulletSystem::GetTextureResource() {
	return m_Texture->m_Texture->GetTexture();
}
TexturedSpritesheet* BulletSystem::GetTexture() {
	return m_Texture;
}
void BulletSystem::Delete(int b) {
	for (int x = b + 1; x < m_Active; x++) {
		m_Bullets[x - 1] = m_Bullets[x];
	}
	m_Active--;
}

void BulletSystem::Shutdown() {
	delete m_Bullets;
	m_Bullets = new Bullet[150];

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
		m_Bullets[m_Active].data = 0;
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
		m_Bullets[m_Active].data = 0;

		m_Active++;
	}
}
void BulletSystem::SetData(int id, float data) {
	m_Bullets[id].data = data;
}
void BulletSystem::MoveBullet(int id, float time) {
	Bullet& bullet = m_Bullets[id];
	BulletMovement(m_Bullets[id]);
	bullet.x += bullet.velX * time / 10;
	bullet.y += bullet.velY * time / 10;
}

int BulletSystem::GetActive() {
	return m_Active;
}

DirectX::XMFLOAT2* BulletSystem::GetBulletsCoords() {
	DirectX::XMFLOAT2* list = new DirectX::XMFLOAT2[m_Active];
	for (int i = 0; i < m_Active; i++) {
		list[i] = DirectX::XMFLOAT2(m_Bullets[i].x, m_Bullets[i].y);
	}
	return list;
}