#include "SceneSplash.h"

//SceneSplash(HWND, D3DClass*, CameraClass*, ColorShaderClass*, TextureShaderClass*, TransparencyShaderClass*);
//SceneSplash(const SceneClass&);
//~SceneSplash();
SceneSplash::SceneSplash(HWND hwnd, D3DClass* d3dclass, CameraClass* cameraclass, ShaderClass* shaderclass)
	: SceneClass(hwnd, d3dclass, cameraclass, shaderclass) {
	m_active = false;

}

bool SceneSplash::Initialize() {
	bool result;
	m_Splash = new TexturedRect();
	if (!m_Splash) {
		return false;
	}

 	result = m_Splash->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Backgrounds\\DABDABSAVAGE.background",
		800, 600);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the splash screen. 1", L"Error", MB_OK);
		return false;
	}

	return true;
}


void SceneSplash::Shutdown() {
	m_active = false;
	// Release the model object.
	if (m_Splash) {
		m_Splash->Shutdown();
		delete m_Splash;
		m_Splash = 0;
	}
	return;
}

bool SceneSplash::Render(XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMMATRIX orthoMatrix) {
	bool result;
	float blendAmount = 1.0f;
	if (m_active == false) {
		ShowCursor(false);
		sm_Timer.Start();
		m_active = true;
	}
	float time = sm_Timer.getTime();
    blendAmount = (-0.11f*(time/1000))*((time / 1000) - 6.0f);
	// Turn off the Z buffer to begin all 2D rendering.
	sm_Direct3D->TurnZBufferOff();

	// Render the model using the texture shader.
	//m_Splash->Render(sm_Direct3D->GetDeviceContext(), ((Options::WIDTH / 2) - m_Splash->m_imageWidth / 2), 0, DirectX::XMFLOAT4(1.f,0.f,0.f,1.f));
	//result = sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), m_Splash->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Splash->GetTexture(), blendAmount);
	
	//if (time > 6000) {
	if (time > 000) {
		ShowCursor(true);
		Shutdown();
		Options::Scene = 1;
	}

	return true;
}
