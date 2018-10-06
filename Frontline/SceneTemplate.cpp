#include "SceneTemplate.h"

//SceneSSSSSS(HWND, D3DClass*, CameraClass*, ColorShaderClass*, TextureShaderClass*, TransparencyShaderClass*);
//SceneSSSSSS(const SceneClass&);
//~SceneSSSSSS();
SceneSSSSSS::SceneSSSSSS(HWND hwnd, D3DClass* d3dclass, CameraClass* cameraclass, ColorShaderClass* colorshaderclass, TextureShaderClass* textureshaderclass, TransparencyShaderClass* transparencyshaderclass)
	: SceneClass(hwnd, d3dclass, cameraclass, colorshaderclass, textureshaderclass, transparencyshaderclass) {
	m_active = false;

}

bool SceneSSSSSS::Initialize() {
	bool result;
	m_Splash = new TexturedRect();
	if (!m_Splash) {
		return false;
	}

	result = m_Splash->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Assets\\Images\\GUI\\Untitled.tga",
		800, 600, 800, 600);
	if (!result) {
		MessageBox(sm_hwnd, L"Could not initialize the splash screen. 1", L"Error", MB_OK);
		return false;
	}

	return true;
}


void SceneSSSSSS::Shutdown() {
	m_active = false;
	// Release the model object.
	if (m_Splash) {
		m_Splash->Shutdown();
		delete m_Splash;
		m_Splash = 0;
	}
	return;
}

bool SceneSSSSSS::Render(XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMMATRIX orthoMatrix) {
	bool result;
	// Turn off the Z buffer to begin all 2D rendering.
	sm_Direct3D->TurnZBufferOff();

	// Render the model using the texture shader.
	m_Splash->Render(sm_Direct3D->GetDeviceContext(), (400 - m_Splash->m_imageWidth / 2), 0);
	result = sm_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), m_Splash->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Splash->GetTexture(), blendAmount);
	if (!result) {
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	sm_Direct3D->TurnZBufferOn();

	return true;
}
