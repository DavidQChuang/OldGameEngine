#include "Player.h"

Player::Player(Input* input, int xp, int yp) {
	m_x = xp;
	m_y = yp;
	m_speed = 5;
	m_Input = input;
	m_Bullets = 0;
	m_Texture = 0;
	m_BulletType = 0;
	m_PlayerParticles = 0;

	lastTime = -1;
	elapsedTime = 0;
	bulletTime = 0;

	state = 0;
	m_hp = 2;
	m_mp = 4;
	m_keys = new bool[4];
}

bool Player::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename, char* bulletFilename,
	int imageWidth, int imageHeight, int spriteAmount) {
	bool result;
	m_Texture = new TexturedSpritesheet();
	if (!m_Texture) {
		return false;
	}
	result = m_Texture->Initialize(device, deviceContext,
		textureFilename,
		imageWidth, imageHeight, spriteAmount);
	if (!result) return false;

	m_Bullets = new PlayerBulletSystem(150);
	result = m_Bullets->Initialize(device, deviceContext,
		bulletFilename,
		6 * 3, 6 * 3, 3);
	if (!result) return false;

	m_PlayerParticles = new PlayerPS(150);
	if (!m_PlayerParticles) {
		return false;
	}
	m_PlayerParticles->SetParameters(0, 600, 800, 1, 3000, 100, 1, 0);
	result = m_PlayerParticles->Initialize(device, deviceContext,
		".\\Data\\Images\\Sprites\\Particles\\Fire.sprite",
		16 * 4, 16 * 4);
	if (!result) return false;

	return true;
}
bool Player::Frame(bool enableInput, float time) {
	bool result;
	if (lastTime == -1) {
		lastTime = time;
	}
	elapsedTime = time - lastTime;
	if (enableInput) {

		if (m_Input->OnKeyDown(81)) {
			if (m_BulletType == 2) {
				m_BulletType = 0;
			}
			else {
				m_BulletType += 1;
			}
		}
		if (m_Input->IsKeyDown(VK_SHIFT)) m_speed = 2; else m_speed = 4;
		//W87 A65 S83 D68 
		if (m_Input->IsKeyDown(VK_RIGHT) || m_Input->IsKeyDown(68)) m_keys[0] = true; else m_keys[0] = false;
		if (m_Input->IsKeyDown(VK_LEFT) || m_Input->IsKeyDown(65)) m_keys[1] = true; else m_keys[1] = false;
		if (m_Input->IsKeyDown(VK_UP) || m_Input->IsKeyDown(87)) m_keys[2] = true; else m_keys[2] = false;
		if (m_Input->IsKeyDown(VK_DOWN) || m_Input->IsKeyDown(83)) m_keys[3] = true; else m_keys[3] = false;
		for (int k = 0; k < 4; k++) {
			if (m_keys[k] == true) {
				switch (k) {
				case 0:
					m_x += m_speed * elapsedTime / 10;
					break;
				case 1:
					m_x -= m_speed * elapsedTime / 10;
					break;
				case 2:
					m_y -= m_speed * elapsedTime / 10;
					break;
				case 3:
					m_y += m_speed * elapsedTime / 10;
					break;
				}
			}
		}
		if (bulletTime == 0) {
			bulletTime = lastTime;
		}
		//if 2 frames (@60hz) have passed

		switch (m_BulletType) {
		case 0:
			gap = 1.f;
			bulletOffset = 55;
			break;
		case 1:
			gap = 0.7f;
			bulletOffset = 115;
			break;
		case 2:
			gap = 1.25f;
			bulletOffset = 85;
			break;
		}
		if (time - bulletTime > 66) {
			int bullets = floor((time - bulletTime) / 66);
			float remainder = time - bulletTime - bullets * 66;
			for (int intergar = 0; intergar < bullets; intergar++) {
				//for every 2 frames (~33ms with error margin) passed move the bullet the amount it would have moved
				m_Bullets->Create(m_x + m_Bullets->GetTexture()->m_spriteWidth * (1 - gap),
					m_y + bulletOffset,
					DirectX::XMFLOAT4(0.7f, 0.7f, 0.7f, 0.8f), m_BulletType);
				m_Bullets->Create(m_x + m_Texture->m_spriteWidth - m_Bullets->GetTexture()->m_spriteWidth - m_Bullets->GetTexture()->m_spriteWidth * (1 - gap),
					m_y + bulletOffset,
					DirectX::XMFLOAT4(0.7f, 0.7f, 0.7f, 0.8f), m_BulletType);
				m_Bullets->MoveBullet(m_Bullets->GetActive() - 2, (time - bulletTime) - intergar * 33);
				m_Bullets->MoveBullet(m_Bullets->GetActive() - 1, (time - bulletTime) - intergar * 33);
				if (m_BulletType == 2) {
					m_Bullets->Create(m_x + m_Bullets->GetTexture()->m_spriteWidth * (1 - gap - 2),
						m_y + bulletOffset,
						DirectX::XMFLOAT4(0.7f, 0.7f, 0.7f, 0.8f), m_BulletType);
					m_Bullets->Create(m_x + m_Texture->m_spriteWidth - m_Bullets->GetTexture()->m_spriteWidth - m_Bullets->GetTexture()->m_spriteWidth * (1 - gap - 2),
						m_y + bulletOffset,
						DirectX::XMFLOAT4(0.7f, 0.7f, 0.7f, 0.8f), m_BulletType);
					m_Bullets->MoveBullet(m_Bullets->GetActive() - 2, (time - bulletTime) - intergar * 33);
					m_Bullets->MoveBullet(m_Bullets->GetActive() - 1, (time - bulletTime) - intergar * 33);
					m_Bullets->SetData(m_Bullets->GetActive() - 2, 1);
					m_Bullets->SetData(m_Bullets->GetActive() - 1, 2);
				}
			}
			bulletTime = time - remainder;
		}

		if (m_y < -(m_Texture->m_imageHeight / 2)) {
			m_y = -(m_Texture->m_imageHeight / 2);
		}
		else if (m_y > Options::HEIGHT - (m_Texture->m_imageHeight / 2)) {
			m_y = Options::HEIGHT - (m_Texture->m_imageHeight / 2);
		}

		if (m_x < -(m_Texture->m_spriteWidth / 2)) {
			m_x = -(m_Texture->m_spriteWidth / 2);
		}
		else if (m_x > Options::WIDTH - (m_Texture->m_spriteWidth / 2) - 75) {
			m_x = Options::WIDTH - (m_Texture->m_spriteWidth / 2) - 75;
		}
	}
	lastTime = time;
	return true;
}

int Player::GetSpriteNumber() {
	return m_Texture->m_currentSprite;
}

bool Player::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix) {
	m_Texture->Render(direct3d->GetDeviceContext());
	return true;
}
bool Player::RenderBullets(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ColorTextureShader* shader) {
	return m_Bullets->Render(direct3d, viewMatrix, orthoMatrix, shader, elapsedTime);
}

int Player::GetIndexCount() {
	return m_Texture->m_indexCount;
}
int Player::GetBulletIndexCount() {
	return m_Bullets->GetIndexCount();
}
ID3D11ShaderResourceView* Player::GetTextureResource() {
	return m_Texture->m_Texture->GetTexture();
}
ID3D11ShaderResourceView* Player::GetBulletTextureResource() {
	return m_Bullets->GetTextureResource();
}
TexturedSpritesheet* Player::GetBulletTexture() {
	return m_Bullets->GetTexture();
}
DirectX::XMFLOAT2* Player::GetBullets() {
	return m_Bullets->GetBulletsCoords();
}
void Player::Shutdown() {
	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	if (m_Bullets) {
		m_Bullets->Shutdown();
		delete m_Bullets;
		m_Bullets = 0;
	}
}