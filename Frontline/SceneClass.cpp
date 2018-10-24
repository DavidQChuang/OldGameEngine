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
//  
//  
inline bool SceneClass::RenderRectMatrix(TexturedRect* object, XMMATRIX matrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	switch (shaderType) {
	case H_2D_COLOR_SHADERTYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix);
		break;
	case H_2D_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case H_2D_COLOR_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case H_2D_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case H_2D_COLOR_SHADERTYPE | H_2D_INSTANCE_SHADERMOD:
		break;
	case H_2D_TEXTURE_SHADERTYPE | H_2D_INSTANCE_SHADERMOD:
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE | H_2D_INSTANCE_SHADERMOD:
		break;
	}
	return false;
}

inline bool SceneClass::RenderRect(TexturedRect* object, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

inline bool SceneClass::RenderRect(TexturedRect* object, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = 
		DirectX::XMMatrixRotationZ(XMConvertToRadians(rot)) * 
		DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

inline bool SceneClass::RenderRect(TexturedRect* object, float scaleX, float scaleY, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = 
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) * 
		DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
inline bool SceneClass::RenderRect(TexturedRect* object, float scaleX, float scaleY, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = 
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) * 
		DirectX::XMMatrixRotationZ((XMConvertToRadians(rot))) * 
		DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = 
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = 
		DirectX::XMMatrixRotationZ(XMConvertToRadians(rot)) * 
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, float scaleX, float scaleY, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = 
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) * 
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, float scaleX, float scaleY, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = 
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) * 
		DirectX::XMMatrixRotationZ(XMConvertToRadians(rot)) * 
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
inline bool SceneClass::RenderSpritesheetMatrix(TexturedSpritesheet* object, XMMATRIX matrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	switch (shaderType) {
	case H_2D_COLOR_SHADERTYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix);
		break;
	case H_2D_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
		break;
	case H_2D_COLOR_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case H_2D_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture(), 1.f);
		break;
	case H_2D_COLOR_SHADERTYPE | H_2D_INSTANCE_SHADERMOD:
		break;
	case H_2D_TEXTURE_SHADERTYPE | H_2D_INSTANCE_SHADERMOD:
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE | H_2D_INSTANCE_SHADERMOD:
		break;
	}
	return false;
}
//
//  Second layer of abstraction for rendering a spritesheet using a certain shader. (creates a transformation matrix and feeds it as a world matrix to RenderRectMatrix)
//  int x, int y: X and Y coords (self explanatory)
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderSpritesheetMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

//
//  Abstraction for rendering a spritesheet using a certain shader. 
//  int x, int y: X and Y coords (self explanatory) 
//  int sprite: Sprite number (calls TexturedSpritesheet::SetSprite(sprite))
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, int sprite, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->SetSprite(sprite);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderSpritesheetMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

//
//  Abstraction for rendering a spritesheet using a certain shader. 
//  int x, int y: X and Y coords (self explanatory) 
//  float rot: Clockwise rotation in degrees
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(rot)) * DirectX::XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderSpritesheetMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
}

//
//  Abstraction for rendering a spritesheet using a certain shader. 
//  int x, int y: X and Y coords (self explanatory) 
//  float rot: Clockwise rotation in degrees
//  int sprite: Switches sprite number (calls TexturedSpritesheet::SetSprite(sprite))
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, float rot, int sprite, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixRotationZ(rot) * DirectX::XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->SetSprite(sprite);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderSpritesheetMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
inline bool SceneClass::RenderModel(ModelClass* object, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(1.f, 1.f, 1.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), matrix, viewMatrix, orthoMatrix, object->GetTexture());
}