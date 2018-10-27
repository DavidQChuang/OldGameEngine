#pragma once
#include "D3DClass.h"
#include "CameraClass.h"
#include "ShaderClass.h"
#include "Options.h"
#include "Timer.h"
#include "TexturedRect.h"
#include "TexturedButton.h"
#include "TexturedSpritesheet.h"
#include "ModelClass.h"
#include "ParticleSystem.h"
#include <cmath>
#pragma warning(disable : 4244)
class SceneClass {
public:
	SceneClass(HWND hwnd, D3DClass*, CameraClass*, ShaderClass*);
	SceneClass(const SceneClass&);
	~SceneClass();
	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual bool Render(XMMATRIX, XMMATRIX, XMMATRIX) = 0;
	bool m_active;

	inline bool RenderRectMatrix(TexturedRect*, XMMATRIX, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, float, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, float, float, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, float, float, float, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, int, int, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, int, int, float, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, int, int, float, float, XMMATRIX, XMMATRIX, int);
	inline bool RenderRect(TexturedRect*, int, int, float, float, float, XMMATRIX, XMMATRIX, int);

	inline bool RenderSpritesheetMatrix(TexturedSpritesheet*, XMMATRIX, XMMATRIX, XMMATRIX, int);
	//  Rotation
	//inline bool RenderSpritesheet(TexturedSpritesheet*, float, XMMATRIX, XMMATRIX, int);
	//  Scaling
	//inline bool RenderSpritesheet(TexturedSpritesheet*, float, float, XMMATRIX, XMMATRIX, int);
	//  Scaling and Rotation
	//inline bool RenderSpritesheet(TexturedSpritesheet*, float, float, float, XMMATRIX, XMMATRIX, int);
	//  Rotation and Sprite number
	//inline bool RenderSpritesheet(TexturedSpritesheet*, float, int, XMMATRIX, XMMATRIX, int);
	//  Scaling and Sprite number
	//inline bool RenderSpritesheet(TexturedSpritesheet*, float, float, int, XMMATRIX, XMMATRIX, int);
	//  Scaling, Rotation, and Sprite number
	//inline bool RenderSpritesheet(TexturedSpritesheet*, float, float, float, int, XMMATRIX, XMMATRIX, int);
	//  Sprite number
	//inline bool RenderSpritesheet(TexturedSpritesheet*, int, XMMATRIX, XMMATRIX, int);
	//  Position
	inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, XMMATRIX, XMMATRIX, int);
	//  Position and Sprite number
	inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, int, XMMATRIX, XMMATRIX, int);
	//  Position and Rotation
	inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, XMMATRIX, XMMATRIX, int);
	//  Position and Scaling
	//inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, float, XMMATRIX, XMMATRIX, int);
	//  Position, Scaling, and Rotation
	//inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, float, float, XMMATRIX, XMMATRIX, int);
	//  Position, Rotation, and Sprite number
	inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, int, XMMATRIX, XMMATRIX, int);
	//  Position, Scaling, and Sprite number
	//inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, float, int, XMMATRIX, XMMATRIX, int);
	//  Position, Scaling, Rotation, and Sprite number
	//inline bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, float, float, int, XMMATRIX, XMMATRIX, int);

	inline bool RenderModel(ModelClass*, XMMATRIX, XMMATRIX, int);
private:
protected:
	HWND sm_hwnd;
	D3DClass* sm_Direct3D;
	CameraClass* sm_Camera;
	ShaderClass* sm_ShaderClass;
	Timer* sm_Timer;
};

//  
//  Renders a TexturedRect from the buffer using a shader and passing a translation matrix as the world matrix.
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

//
//  Abstraction for writing a TexturedRect to buffer. 
//  Uses TexturedRect.m_posX and m_posY
//
inline bool SceneClass::RenderRect(TexturedRect* object, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

//
//  Abstraction for writing a TexturedRect to buffer. 
//  float rot: Clockwise rotation in degrees
//
inline bool SceneClass::RenderRect(TexturedRect* object, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix =
		DirectX::XMMatrixRotationZ(XMConvertToRadians(rot)) *
		DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

//
//  Abstraction for writing a TexturedRect to buffer. 
//  float scaleX, float scaleY: Scale multiplier
//
inline bool SceneClass::RenderRect(TexturedRect* object, float scaleX, float scaleY, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix =
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) *
		DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
//
//  Abstraction for writing a TexturedRect to buffer. 
//  float scaleX, float scaleY: Scale multiplier
//  float rot: Clockwise rotation in degrees
//
inline bool SceneClass::RenderRect(TexturedRect* object, float scaleX, float scaleY, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix =
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) *
		DirectX::XMMatrixRotationZ((XMConvertToRadians(rot))) *
		DirectX::XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
//
//  Abstraction for writing a TexturedRect to buffer. 
//  int x, int y: X and Y coords (self explanatory) 
//
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix =
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	return RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
//
//  Abstraction for writing a TexturedRect to buffer. 
//  int x, int y: X and Y coords (self explanatory) 
//  float rot: Clockwise rotation in degrees
//
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix =
		DirectX::XMMatrixRotationZ(XMConvertToRadians(rot)) *
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
//
//  Abstraction for writing a TexturedRect to buffer. 
//  int x, int y: X and Y coords (self explanatory) 
//  float scaleX, float scaleY: Scale multiplier
//
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, float scaleX, float scaleY, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix =
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) *
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}
//
//  Abstraction for writing a TexturedRect to buffer. 
//  int x, int y: X and Y coords (self explanatory) 
//  float scaleX, float scaleY: Scale multiplier
//  float rot: Clockwise rotation in degrees
//
inline bool SceneClass::RenderRect(TexturedRect* object, int x, int y, float scaleX, float scaleY, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix =
		DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) *
		DirectX::XMMatrixRotationZ(XMConvertToRadians(rot)) *
		DirectX::XMMatrixTranslation(x - 400 + object->m_imageWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderRectMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

//
//  Renders a TexturedRect from the buffer using a shader and passing a translation matrix as the world matrix.
//
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
//  Abstraction for writing a TexturedSpritesheet to buffer. 
//  int x, int y: X and Y coords (self explanatory)
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderSpritesheetMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
	return false;
}

//
//  Abstraction for writing a TexturedSpritesheet to buffer.  
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
//  Abstraction for writing a TexturedSpritesheet to buffer. 
//  int x, int y: X and Y coords (self explanatory) 
//  float rot: Clockwise rotation in degrees
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, float rot, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(rot)) * DirectX::XMMatrixTranslation(x - 400 + object->m_spriteWidth / 2, -y + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	RenderSpritesheetMatrix(object, matrix, viewMatrix, orthoMatrix, shaderType);
}

//
//  Abstraction for writing a TexturedSpritesheet to buffer. 
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