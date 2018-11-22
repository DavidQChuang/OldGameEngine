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

	TexturedRect* InitializeRect(TexturedRect*, H_COLORRGBA, H_DIMENSION, H_DIMENSION);
	TexturedRect* InitializeRect(TexturedRect*, char*, H_DIMENSION, H_DIMENSION);
	TexturedRect* InitializeRect(TexturedRect*, char*, H_COLORRGBA, H_DIMENSION, H_DIMENSION);
	TexturedSpritesheet* InitializeSpritesheet(TexturedSpritesheet*, char*, H_DIMENSION, H_DIMENSION, int);
	TexturedSpritesheet* InitializeSpritesheet(TexturedSpritesheet*, char*, H_COLORRGBA, H_DIMENSION, H_DIMENSION, int);
	
	inline bool RenderRect(TexturedRect*, H_VIEWMATRIX, H_ORTHOMATRIX, int);

	inline bool RenderSpritesheet(TexturedSpritesheet*, H_VIEWMATRIX, H_ORTHOMATRIX, int);
	inline bool RenderSpritesheet(TexturedSpritesheet*, int, H_VIEWMATRIX, H_ORTHOMATRIX, int);

	inline friend std::string DecatenateColors(H_COLORRGBA);

	//inline bool RenderModel(ModelClass*, XMMATRIX, XMMATRIX, int);
private:
protected:
	HWND sm_hwnd;
	D3DClass* sm_Direct3D;
	CameraClass* sm_Camera;
	ShaderClass* sm_ShaderClass;
	Timer* sm_Timer;
};
inline std::string DecatenateColors(H_COLORRGBA color) {
	return to_string(color.x * 255) + ", " + to_string(color.y * 255) + ", " + to_string(color.z * 255) + ", " + to_string(color.w * 255);
}
//
//  Renders a TexturedRect from the buffer using a shader and passing a translation matrix as the world matrix.
//
inline bool SceneClass::RenderRect(TexturedRect* object, H_VIEWMATRIX viewMatrix, H_ORTHOMATRIX orthoMatrix, int shaderType) {
	XMMATRIX matrix =
		XMMatrixScaling(object->m_scaleX, object->m_scaleY, 1.f) *
		XMMatrixRotationZ(object->m_rot) *
		XMMatrixTranslation(object->m_posX - 400 + object->m_imageWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	//XMMATRIX matrix = XMMatrixTranslation(0.f, 0.f, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	switch (shaderType) {
	case H_2D_COLOR_SHADERTYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix);
		break;
	case H_2D_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture());
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture());
		break;
	case H_2D_COLOR_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
		break;
	case H_2D_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
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
//  Renders a TexturedRect from the buffer using a shader and passing a translation matrix as the world matrix.
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, H_VIEWMATRIX viewMatrix, H_ORTHOMATRIX orthoMatrix, int shaderType) {
	XMMATRIX matrix =
		XMMatrixScaling(object->m_scaleX, object->m_scaleY, 1.f) *
		XMMatrixRotationZ(object->m_rot) *
		XMMatrixTranslation(object->m_posX - 400 + object->m_spriteWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	switch (shaderType) {
	case H_2D_COLOR_SHADERTYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix);
		break;
	case H_2D_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture());
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture());
		break;
	case H_2D_COLOR_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
		break;
	case H_2D_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
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
//  Renders a TexturedRect from the buffer using a shader and passing a translation matrix as the world matrix.
//  @param object any t h o t?
//
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int spriteNumber, H_VIEWMATRIX viewMatrix, H_ORTHOMATRIX orthoMatrix, int shaderType) {
	XMMATRIX matrix =
		XMMatrixScaling(object->m_scaleX, object->m_scaleY, 1.f) *
		XMMatrixRotationZ(object->m_rot) *
		XMMatrixTranslation(object->m_posX - 400 + object->m_spriteWidth / 2, -object->m_posY + 300 - object->m_imageHeight / 2, 0.f);
	object->SetSprite(sm_Direct3D->GetDeviceContext(), spriteNumber);
	object->Render(sm_Direct3D->GetDeviceContext());
	switch (shaderType) {
	case H_2D_COLOR_SHADERTYPE:
		return sm_ShaderClass->m_ColorShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix);
		break;
	case H_2D_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture());
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE:
		return sm_ShaderClass->m_ColorTextureShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture());
		break;
	case H_2D_COLOR_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
		break;
	case H_2D_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE | H_2D_TRANSPARENCY_SHADERMOD:
		//return sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture(), 1.f);
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
/*inline bool SceneClass::RenderModel(ModelClass* object, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranslation(1.f, 1.f, 1.f);
	object->Render(sm_Direct3D->GetDeviceContext());
	return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->m_indexCount, matrix, viewMatrix, orthoMatrix, object->m_Texture->GetTexture());
}*/
