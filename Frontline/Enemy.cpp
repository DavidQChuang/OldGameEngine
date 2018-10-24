#include "Enemy.h"
EnemySystem::EnemySystem() {
	m_Enemies = new Enemy[50];
	m_bMax = 50;
	m_Active = 0;
	m_Texture = 0;
	m_on = true;
}
EnemySystem::~EnemySystem() {
}

bool EnemySystem::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight, int images) {
	bool result;
	m_Texture = new TexturedSpritesheet();
	if (!m_Texture) {
		return false;
	}
	result = m_Texture->Initialize(device, deviceContext,
		textureFilename, DirectX::XMFLOAT4(1.f,1.f,1.f,1.f),
		screenWidth, screenHeight, imageWidth, imageHeight, images);
	if (!result) {
		return false;
	}
	return true;
}
bool EnemySystem::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ColorTextureShader* shader, TexturedSpritesheet* bullet, BulletSystem::Bullet* bullets, int max, double elapsed) {
	bool result;
	DirectX::XMMATRIX matrix;
	if (m_Active != 0) {
		for (int i = 0; i < m_Active; i++) {
			Enemy& enemy = m_Enemies[i];
			//for(int b = )
			//if(CheckCollision(i,))
			
			if (enemy.y <= -200 || enemy.y >= 800 || enemy.x <= -200 || enemy.y >= 1000 || enemy.health <= 0 || CheckCollision(i,bullet,bullets,max)) {
				Delete(i);
				continue;
			}
			if (m_on) {
				DirectX::XMFLOAT2 movement = EnemyMovement(i);
				//velX = pixels per 16.7ms(1 60fps frame) 
				//velX * 60 (distance traveled in 1 sec)
				//m_Timer->getTime() / 1000 (seconds passed)
				//simplified down
				enemy.x += movement.x * elapsed / 10;
				enemy.y += movement.y * elapsed / 10;
			}

			matrix = XMMatrixTranslation(enemy.x - 400 + m_Texture->m_spriteWidth / 2, -enemy.y + 300 - m_Texture->m_imageHeight / 2, 0.f);
			m_Texture->SetSprite(enemy.type);
			m_Texture->Render(direct3d->GetDeviceContext(), enemy.x, enemy.y, enemy.color);
			result = shader->Render(direct3d->GetDeviceContext(), GetIndexCount(), matrix, viewMatrix, orthoMatrix, GetTextureResource());
			if (!result) {
				return false;
			}
		}
	}
	return true;
}
void EnemySystem::SetRatePerFrame(float rate) {
	m_delta = (1 /rate)*16;
}
bool EnemySystem::CheckCollision(int number, TexturedSpritesheet* bullet, BulletSystem::Bullet* bullets, int max) {
	for (int b = 0; b < max; b++) {
		if (m_Enemies[number].x > bullets[b].x + bullet->m_spriteWidth &&
			m_Enemies[number].y > bullets[b].y + bullet->m_imageHeight &&
			m_Enemies[number].x + m_Texture->m_spriteWidth < bullets[b].x &&
			m_Enemies[number].y + m_Texture->m_imageHeight < bullets[b].y) {
			return true;
		}
	}
	return false;
}

void EnemySystem::SetState(bool on) {
	m_on = on;
}

DirectX::XMFLOAT2 EnemySystem::EnemyMovement(int enemy) {
	float x = 0;
	float y = 0;
	switch (m_Enemies[enemy].type) {
	case 0:
		y++;
		break;
	}
	return DirectX::XMFLOAT2(x, y);
}
void EnemySystem::MoveEnemy(int enemy, float delta) {
	DirectX::XMFLOAT2 movement = EnemyMovement(enemy);
	m_Enemies[enemy].x += movement.x * delta / 10;
	m_Enemies[enemy].y += movement.y * delta / 10;
}

void EnemySystem::Delete(int b) {
	for (int x = b + 1; x < m_Active; x++) {
		m_Enemies[x - 1] = m_Enemies[x];
	}
	m_Active--;
}

void EnemySystem::Shutdown() {
	delete m_Enemies;
	m_Enemies = new Enemy[0];

	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}
void EnemySystem::Create(float x, float y, DirectX::XMFLOAT4 color, int type, double time) {
	if (time - m_lastSpawnTime > m_delta) {
		int enemies = floor((time - m_lastSpawnTime) / m_delta);
		double remainder = time - m_lastSpawnTime - enemies * m_delta;
		for (int intergar = 0; intergar < enemies; intergar++) {
			if (m_Active < m_bMax) {
				m_Enemies[m_Active].x = x;
				m_Enemies[m_Active].y = y;
				m_Enemies[m_Active].color = color;
				m_Enemies[m_Active].type = type;
				switch (type) {
				case 0:
					m_Enemies[m_Active].health = 10;
					break;
				}
				MoveEnemy(m_Active, (time - m_lastSpawnTime) - intergar * 33);
				m_Active++;
			}
		}
		m_lastSpawnTime = time - remainder;
	}
}

int EnemySystem::GetIndexCount() {
	return m_Texture->GetIndexCount();
}

ID3D11ShaderResourceView* EnemySystem::GetTextureResource() {
	return m_Texture->GetTexture();
}

TexturedSpritesheet* EnemySystem::GetTexture() {
	return m_Texture;
}

int EnemySystem::GetActive() {
	return m_Active;
}

EnemySystem::Enemy EnemySystem::GetEnemy(int x) {
	return m_Enemies[x];
}

EnemySystem::Enemy* EnemySystem::GetEnemies() {
	return m_Enemies;
}

DirectX::XMFLOAT2* EnemySystem::GetEnemiesCoords() {
	DirectX::XMFLOAT2* list = new DirectX::XMFLOAT2[m_Active];
	for (int i = 0; i < m_Active; i++) {
		list[i] = DirectX::XMFLOAT2(m_Enemies[i].x, m_Enemies[i].y);
	}
	return list;
}