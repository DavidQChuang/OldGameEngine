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
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture());
}

bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture());
}

bool SceneClass::RenderSpritesheet(TexturedSpritesheet* object, int x, int y, int sprite, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix, int shaderType) {
	object->SetSprite(sprite);
	object->Render(sm_Direct3D->GetDeviceContext(), x, y);
	return sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), object->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, object->GetTexture());
}