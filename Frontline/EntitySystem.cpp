#include "EntitySystem.h"
EntitySystem::EntitySystem() {
	m_Count = 0;
	m_Texture = 0;
	m_Max = 0;
	m_Active = true;
}
EntitySystem::~EntitySystem() {
}

bool EntitySystem::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int imageWidth, int imageHeight, int images, Entity* list) {
	m_Entities = list;
	m_Max = sizeof(m_Entities) / sizeof(Entity);

	m_Texture = new TexturedSpritesheet();
	if (!m_Texture ||
		!m_Texture->Initialize(device, deviceContext,
		textureFilename, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f),
		imageWidth, imageHeight, images)) {
		return false;
	}
	return true;
}
bool EntitySystem::Render(D3DClass* direct3d, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix, ColorTextureShader* shader, float elapsed) {
	DirectX::XMMATRIX matrix;
	for (int i = 0; i < m_Count; i++) {
		Entity& entity = m_Entities[i];
		if (deletion(entity)) {
			DeleteEntity(i);
			continue;
		}
		if (m_Active) {
			TimestepEntity(i, elapsed);
		}
		modification(direct3d, entity, matrix);

		m_Texture->Render(direct3d->GetDeviceContext());
		shader->Render(direct3d->GetDeviceContext(), GetIndexCount(), matrix, viewMatrix, orthoMatrix, GetTextureResource());
	}
	return true;
}

void EntitySystem::Shutdown() {
	delete m_Entities;
	m_Entities = 0;

	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}
void EntitySystem::CreateEntity(Entity entity) {
	if (m_Count < m_Max) {
		m_Entities[m_Count].data[0] = CreateData(entity).x;
		m_Entities[m_Count].data[1] = CreateData(entity).y;
		m_Entities[m_Count].data[2] = CreateData(entity).z;
		m_Count++;
	}
}

void EntitySystem::DeleteEntity(int i) {
	for (int x = i + 1; x < m_Count; x++) {
		m_Entities[x - 1] = m_Entities[x];
	}
	m_Count--;
}