#include "SceneClass.h"


SceneClass::SceneClass(HWND hwnd, D3DClass* d3dclass, CameraClass* cameraclass, ShaderClass* shaderclass) {
	sm_hwnd = hwnd;
	sm_Direct3D = d3dclass;
	sm_Camera = cameraclass;
	sm_ShaderClass = shaderclass;
	m_active = false;
	sm_Timer = new Timer();
}


SceneClass::SceneClass(const SceneClass& other) {
}


SceneClass::~SceneClass() {
}

bool SceneClass::RenderRect(TexturedRect* object, int x, int y, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	switch (shaderType) {
	case COLOR_TYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix);
		break;
	case TEXTURE_TYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TEXTURE_TYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case TEXTURE_TYPE | TRANSPARENCY:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TEXTURE_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TYPE | INSTANCE:
		break;
	case TEXTURE_TYPE | INSTANCE:
		break;
	case COLOR_TEXTURE_TYPE | INSTANCE:
		break;
	}
	return false;
}
bool SceneClass::RenderRect(TexturedRect* object, int x, int y, float rot, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = XMMatrixRotationZ(XMConvertToRadians(rot))* XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	switch (shaderType) {
	case COLOR_TYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix);
		break;
	case TEXTURE_TYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TEXTURE_TYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case TEXTURE_TYPE | TRANSPARENCY:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TEXTURE_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TYPE | INSTANCE:
		break;
	case TEXTURE_TYPE | INSTANCE:
		break;
	case COLOR_TEXTURE_TYPE | INSTANCE:
		break;
	}
	return false;
}


bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	switch (shaderType) {
	case COLOR_TYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix);
		break;
	case TEXTURE_TYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TEXTURE_TYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case TEXTURE_TYPE | TRANSPARENCY:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TEXTURE_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TYPE | INSTANCE:
		break;
	case TEXTURE_TYPE | INSTANCE:
		break;
	case COLOR_TEXTURE_TYPE | INSTANCE:
		break;
	}
	return false;
}

bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, int sprite, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->SetSprite(sprite);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	switch (shaderType) {
	case COLOR_TYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix);
		break;
	case TEXTURE_TYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TEXTURE_TYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case TEXTURE_TYPE | TRANSPARENCY:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TEXTURE_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TYPE | INSTANCE:
		break;
	case TEXTURE_TYPE | INSTANCE:
		break;
	case COLOR_TEXTURE_TYPE | INSTANCE:
		break;
	}
	return false;
}
bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, float rot, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = XMMatrixRotationZ(rot) * XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	switch (shaderType) {
	case COLOR_TYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix);
		break;
	case TEXTURE_TYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TEXTURE_TYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case TEXTURE_TYPE | TRANSPARENCY:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TEXTURE_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TYPE | INSTANCE:
		break;
	case TEXTURE_TYPE | INSTANCE:
		break;
	case COLOR_TEXTURE_TYPE | INSTANCE:
		break;
	}
}
bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, float rot, int spritenumber, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = XMMatrixRotationZ(rot) * XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->SetSprite(spritenumber);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	switch (shaderType) {
	case COLOR_TYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix);
		break;
	case TEXTURE_TYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TEXTURE_TYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case COLOR_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case TEXTURE_TYPE | TRANSPARENCY:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TEXTURE_TYPE | TRANSPARENCY:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case COLOR_TYPE | INSTANCE:
		break;
	case TEXTURE_TYPE | INSTANCE:
		break;
	case COLOR_TEXTURE_TYPE | INSTANCE:
		break;
	}
	return false;
}
bool SceneClass::RenderModel(ModelClass* object, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	object->Render(sm_Direct3D->GetDeviceContext());
	return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture());
}