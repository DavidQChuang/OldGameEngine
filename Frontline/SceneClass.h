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

	inline bool InitializeRect(TexturedRect*, char*, H_DIMENSION, H_DIMENSION);
	inline bool RenderRect(TexturedRect*, XMMATRIX, XMMATRIX, int);

	inline bool RenderSpritesheet(TexturedSpritesheet*, XMMATRIX, XMMATRIX, int);
	inline bool RenderSpritesheet(TexturedSpritesheet*, int, XMMATRIX, XMMATRIX, int);

	//inline bool RenderModel(ModelClass*, XMMATRIX, XMMATRIX, int);
private:
protected:
	HWND sm_hwnd;
	D3DClass* sm_Direct3D;
	CameraClass* sm_Camera;
	ShaderClass* sm_ShaderClass;
	Timer* sm_Timer;
};
inline bool SceneClass::InitializeRect(TexturedRect* object, char* filename, H_DIMENSION x, H_DIMENSION y) {
	bool result;

	object = new TexturedRect();
	if (!object) {
		std::wstring string = L"Could not initialize " + (wchar_t)filename;
		LPCWSTR lpcwstr = string.c_str();
		MessageBoxW(sm_hwnd, lpcwstr, L"Error", MB_OK);
		return false;
	}

	result = object->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		filename,
		x, y);
	if (!result) {
		std::wstring string = L"Could not initialize " + (wchar_t)filename;
		LPCWSTR lpcwstr = string.c_str();
		MessageBoxW(sm_hwnd, lpcwstr, L"Error", MB_OK);
		return false;
	}
}
//  
//  Renders a TexturedRect from the buffer using a shader and passing a translation matrix as the world matrix.
//  
inline bool SceneClass::RenderRect(TexturedRect* object, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	XMMATRIX matrix = XMMatrixScaling(object->m_scaleX, object->m_scaleY, 0) * XMMatrixRotationZ(object->m_rot) * XMMatrixTranslation(object->m_posX, object->m_posY, 0);
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
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	XMMATRIX matrix = XMMatrixScaling(object->m_scaleX, object->m_scaleY, 0) * XMMatrixRotationZ(object->m_rot) * XMMatrixTranslation(object->m_posX, object->m_posY, 0);
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
inline bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int spriteNumber, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	XMMATRIX matrix = XMMatrixScaling(object->m_scaleX, object->m_scaleY, 0) * XMMatrixRotationZ(object->m_rot) * XMMatrixTranslation(object->m_posX, object->m_posY, 0);
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