#include "SceneMainMenu.h"

//SceneMainMenu(HWND, D3DClass*, CameraClass*, ColorShaderClass*, TextureShaderClass*, TransparencyShaderClass*);
//SceneMainMenu(const SceneClass&);
//~SceneMainMenu();
SceneMainMenu::SceneMainMenu(HWND hwnd, D3DClass* d3dclass, CameraClass* cameraclass, ShaderClass* shaderclass)
	: SceneClass(hwnd, d3dclass, cameraclass, shaderclass) {
	m_active = false;
	m_Background = 0;
	m_Title = 0;
	m_Play = 0;
	m_Flame = 0;
}

bool SceneMainMenu::Initialize() {
	bool result;
	m_Flame = new TitlePS(0, 600, 800, 1, 2000, 3000, 100, 1, 0);
	if (!m_Flame) {
		return false;
	}

	result = m_Flame->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Particles\\Fire.sprite",
		800, 600, 16 * 4, 16 * 4);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the main menu particle system. 1", L"Error", MB_OK);
		return false;
	}

	m_Background = new TexturedRect();
	if (!m_Background) {
		return false;
	}

	result = m_Background->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Backgrounds\\MainMenu.background",
		800, 600, 800, 600);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the main menu background image. 1", L"Error", MB_OK);
		return false;
	}

	m_Title = new TexturedRect();
	if (!m_Title) {
		return false;
	}

	result = m_Title->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Title.image",
		800, 600, 176*4, 18*4);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the title image. 1", L"Error", MB_OK);
		return false;
	}

	m_Play = new TexturedButton();
	if (!m_Play) {
		return false;
	}

	result = m_Play->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\GUI\\Buttons\\Play.images",
		800, 600, 40*4, 12*4, 2);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the play button. 1", L"Error", MB_OK);
		return false;
	}

	return true;
}


void SceneMainMenu::Shutdown() {
	m_active = false;
	// Release the model object.
	if (m_Background) {
		m_Background->Shutdown();
		delete m_Background;
		m_Background = 0;
	}
	if (m_Title) {
		m_Title->Shutdown();
		delete m_Title;
		m_Title = 0;
	}
	if (m_Play) {
		m_Play->Shutdown();
		delete m_Play;
		m_Play = 0;
	}
	if (m_Flame) {
		m_Flame->Shutdown();
		delete m_Flame;
		m_Flame = 0;
	}
	return;
}
float pressCount = 0.f;
float increase = 1.f;
bool start = false; 
bool SceneMainMenu::Render(XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMMATRIX orthoMatrix) {
	bool result;
	float blendAmount = 0.f;
	if (m_active == false) {
		ShowCursor(false);
		sm_Timer->Start();
		m_active = true;
	}
	float time = sm_Timer->getTime();
	if (blendAmount < 1.0f) {
		blendAmount = time / 500;
	}
	if (start == true) { 
		pressCount += increase;
		blendAmount = -((pressCount) / 200) + 1;
	}
	/*
	// Turn off the Z buffer to begin all 2D rendering.
	sm_Direct3D->TurnZBufferOff();
	// Render the model using the texture shader.
	m_Background->Render(sm_Direct3D->GetDeviceContext(), ((Options::WIDTH / 2) - m_Background->m_imageWidth / 2), 0);
	result = sm_ShaderClass->m_TransparencyShader->Render(sm_Direct3D->GetDeviceContext(), m_Background->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Background->GetTexture(), blendAmount);
	if (!result) {
		return false;
	}

	m_Title->Render(sm_Direct3D->GetDeviceContext(), ((Options::WIDTH / 2) - m_Title->m_imageWidth / 2), 100-m_Title->m_imageHeight / 2);
	result = sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), m_Title->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Title->GetTexture());
	if (!result) {
		return false;
	}
	
	GetCursorPos(&m_cursorPos);
	ScreenToClient(sm_hwnd, &m_cursorPos);

	m_Flame->Render(sm_Direct3D, worldMatrix, viewMatrix, orthoMatrix, sm_ShaderClass->m_ColorTextureShader);
	for (int bigoof = 0; bigoof < 10; bigoof++) {
		m_Flame->Create(0, 0, -5, -3);
		if (bigoof % 6 == 0) {
			m_Flame->Create(0, 0, -8, -5);
		}
	}

	m_Play->Render(sm_Direct3D->GetDeviceContext(), ((Options::WIDTH / 2) - m_Play->m_spriteWidth / 2), ((Options::WIDTH / 2) - m_Play->m_imageHeight / 2));
	if (m_Play->Hovered(sm_hwnd, m_cursorPos.x, m_cursorPos.y)) {
		m_Play->Resize(m_Play->m_originalSpriteWidth * 1.1, m_Play->m_originalImageHeight * 1.1);
	}
	else {
		m_Play->Resize();
	}
	result = sm_ShaderClass->m_TextureShader->Render(sm_Direct3D->GetDeviceContext(), m_Play->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Play->GetTexture(sm_hwnd, m_cursorPos.x, m_cursorPos.y));
	if (!result) {
		return false;
	}

	if (m_Play->Clicked(sm_hwnd, m_cursorPos.x, m_cursorPos.y)) {
		start = true;
	}*/
	Options::Scene = 2;
	Shutdown();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	if (pressCount >= 200) {
		Options::Scene = 2;
		Shutdown();
	}
	return true;
}