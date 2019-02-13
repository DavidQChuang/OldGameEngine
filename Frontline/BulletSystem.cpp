#include "BulletSystem.h"
BulletSystem::BulletSystem() {
	m_Count = 0;
	m_Texture = 0;
	m_Max = 0;
	m_Active = true;
}
BulletSystem::~BulletSystem() {
}

/*bool BulletSystem::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ColorTextureShader* shader, float elapsed) {
	DirectX::XMMATRIX matrix;
	for (int i = 0; i < m_Active; i++) {
		MetatypeDataBullet& bullet = m_Bullets[i];

		if (bullet.y <= -200 || bullet.y >= 800 || bullet.x <= -200 || bullet.y >= 1000) {
			DeleteInstance(i);
			continue;
		}
		if (m_on) {
			movement(bullet);
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
}*/
bool BulletSystem::deletion(Entity& bullet) { return (bullet.y <= -200 || bullet.y >= 800 || bullet.x <= -200 || bullet.y >= 1000); }

void BulletSystem::modification(D3DClass* direct3d, Entity& bullet, DirectX::XMMATRIX& matrix) {
	float x = bullet.velX / sqrt((bullet.velX * bullet.velX) + (bullet.velY * bullet.velY));
	matrix = XMMatrixScaling(1.f, 1.f, 1.f);
	if (x != 0) matrix *= XMMatrixRotationZ(acos(x) - XM_PIDIV2);
	matrix *= XMMatrixTranslation(bullet.x - 400 + m_Texture->m_spriteWidth / 2, -bullet.y + 300 - m_Texture->m_imageHeight / 2, 0.f);
	// In bullets data[0] is type.
	m_Texture->SetSprite(direct3d->GetDeviceContext(), bullet.type);
	m_Texture->SetColor(direct3d->GetDeviceContext(), bullet.color);
}