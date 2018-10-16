#include "SceneGame.h"

//SceneGame(HWND, D3DClass*, CameraClass*, ColorShaderClass*, TextureShaderClass*, TransparencyShaderClass*);
//SceneGame(const SceneClass&);
//~SceneGame();
SceneGame::SceneGame(HWND hwnd, D3DClass* d3dclass, CameraClass* cameraclass, ShaderClass* shaderclass, Input* input)
	: SceneClass(hwnd, d3dclass, cameraclass, shaderclass) {
	m_active = false;
	m_Input = input;
	m_GameState = 0;
	m_Background = 0;
	m_Player = 0;
	m_Model = 0;
	m_BadBois = 0;
	m_DODGE = 0;
}

bool SceneGame::Initialize() {
	bool result;
	m_ParticleSystem = new TitlePS(0, 600, 800, 1, 2000, 3000, 100, 1, 0);
	if (!m_ParticleSystem) {
		return false;
	}

	result = m_ParticleSystem->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Particles\\Fire.sprite",
		800, 600, 16 * 4, 16 * 4);
	m_BadBois = new EnemySystem();
	m_BadBois->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Enemies\\Enemy1.sprites",
		800, 600, 9 * 3, 9 * 3, 4);

	m_DODGE = new EnemyBulletSystem(600);
	m_DODGE->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Bullets\\Bullets.sprites",
		800, 600, 6 * 3, 6 * 3, 3);

	m_HUD = new TexturedRect();
	if (!m_HUD) {
		return false;
	}

	result = m_HUD->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\GUI\\HUD.sprite",
		800, 600, 14*3, 85*3);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the game HUD. 1", L"Error", MB_OK);
		return false;
	}

	m_BulletKeys = new TexturedRect();
	if (!m_BulletKeys) {
		return false;
	}

	result = m_BulletKeys->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\GUI\\SelectKey.sprite",
		800, 600, 14 * 3, 36 * 3);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the game HUD. 1", L"Error", MB_OK);
		return false;
	}
	m_AbilityContainers = new TexturedRect();
	if (!m_AbilityContainers) {
		return false;
	}

	result = m_AbilityContainers->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\GUI\\BulletContainer.sprite",
		800, 600, 14 * 3, 42 * 3);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the game HUD. 1", L"Error", MB_OK);
		return false;
	}

	m_BulletSelect = new TexturedSpritesheet();
	if (!m_BulletSelect) {
		return false;
	}

	result = m_BulletSelect->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Bullets\\Bullets.sprites",
		800, 600, 12*3, 12*3,3);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the game HUD. 2", L"Error", MB_OK);
		return false;
	}

	m_Background = new TexturedRect();
	if (!m_Background) {
		return false;
	}

	result = m_Background->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Backgrounds\\DABDABSAVAGE.background",
		800, 600, 800, 600);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the game background. 1", L"Error", MB_OK);
		return false;
	}

	m_Player = new Player(m_Input, 384, 350);
	if (!m_Player) {
		return false;
	}

	result = m_Player->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Character\\Player.sprites",
		".\\Data\\Images\\Sprites\\Bullets\\Bullets.sprites",
		800, 600, 16*3, 18*3, 8);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the player sprite. 1", L"Error", MB_OK);
		return false;
	}
	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model) {
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(), 
		".\\Data\\Models\\Cube.model", 
		".\\Data\\Models\\Face.texture");
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	}

	return true;
}


void SceneGame::Shutdown() {
	m_active = false;
	// Release the model object.
	if (m_BadBois) {
		m_BadBois->Shutdown();
		delete m_BadBois;
		m_BadBois = 0;
	}
	if (m_HUD) {
		m_HUD->Shutdown();
		delete m_HUD;
		m_HUD = 0;
	}

	if (m_AbilityContainers) {
		m_AbilityContainers->Shutdown();
		delete m_AbilityContainers;
		m_AbilityContainers = 0;
	}

	if (m_BulletKeys) {
		m_BulletKeys->Shutdown();
		delete m_BulletKeys;
		m_BulletKeys = 0;
	}

	if (m_BulletSelect) {
		m_BulletSelect->Shutdown();
		delete m_BulletSelect;
		m_BulletSelect = 0;
	}

	if (m_AbilitySelect) {
		m_AbilitySelect->Shutdown();
		delete m_AbilitySelect;
		m_AbilitySelect = 0;
	}

	if (m_DODGE){
		m_DODGE->Shutdown();
		delete m_DODGE;
		m_DODGE = 0;
	}
	if (m_Player) {
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
	}

	if (m_Background) {
		m_Background->Shutdown();
		delete m_Background;
		m_Background = 0;
	}

	if (m_Model) {
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	return;
}
float rotation = 90;
XMMATRIX cubeMatrix;
XMMATRIX rotMatrix;
double lastTime;
bool SceneGame::Render(XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMMATRIX orthoMatrix) {
	bool result;
	if (!m_active) {
		m_active = true;
		sm_Timer->Start();
		sm_ShaderClass->m_Light->SetAmbientColor(0.2f, 0.2f, 0.2f, 1.0f);
		sm_ShaderClass->m_Light->SetDiffuseColor(0.f, 0.f, 0.f, 1.0f);
		lastTime = sm_Timer->getTime();
	}
	switch (m_GameState) {
	case 0:
		rotation += (sm_Timer->getTime() - lastTime) / 4;
		if (rotation > 360) rotation = 0;

		m_Player->Frame(true, sm_Timer->getTime());
		m_Player->m_Texture->SetSprite(static_cast<int>(round(sm_Timer->getTime() / 90)) % 6);

		if (m_Input->OnKeyDown(VK_ESCAPE)) m_GameState = 1;
		break;
	case 1:
		m_Player->Frame(false, sm_Timer->getTime());

		if (m_Input->OnKeyDown(VK_ESCAPE)) m_GameState = 0;
		break;
	}
	m_Model->Render(sm_Direct3D->GetDeviceContext());

	rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(0, XMConvertToRadians(rotation), XMConvertToRadians(rotation));
	cubeMatrix = rotMatrix * DirectX::XMMatrixTranslation(0.f,1.f,0.f);
	// Render the model using the light shader.
	result = sm_ShaderClass->m_LightShader->Render(sm_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), cubeMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), sm_ShaderClass->m_Light->GetDirection(), sm_ShaderClass->m_Light->GetAmbientColor(), sm_ShaderClass->m_Light->GetDiffuseColor());
	if (!result) {
		return false;
	}

	sm_Direct3D->TurnZBufferOff();

	RenderRect(m_HUD, 740, 36, viewMatrix, orthoMatrix, TEXTURE_TYPE);
	RenderRect(m_BulletKeys, 740, 36 + 97 * 3, viewMatrix, orthoMatrix, TEXTURE_TYPE);
	RenderRect(m_AbilityContainers, 740, 36 + 106 * 3, viewMatrix, orthoMatrix, TEXTURE_TYPE);
	RenderSpritesheet(m_BulletSelect, 740 + 3, 36 + 107 * 3, m_Player->m_BulletType, viewMatrix, orthoMatrix, TEXTURE_TYPE);

	for (int bigoof = 0; bigoof < 10; bigoof++) {
		m_ParticleSystem->Create(0, 0, -5, -3);
		if (bigoof % 6 == 0) {
			m_ParticleSystem->Create(0, 0, -8, -5);
		}
	}
	//m_ParticleSystem->Render(sm_Direct3D, viewMatrix, orthoMatrix, sm_ShaderClass->m_ColorTextureShader);

	RenderSpritesheet(m_Player->m_Texture, m_Player->m_x, m_Player->m_y, viewMatrix, orthoMatrix, TEXTURE_TYPE);
	m_Player->RenderBullets(sm_Direct3D, viewMatrix, orthoMatrix, sm_ShaderClass->m_ColorTextureShader);

	m_BadBois->SetRatePerFrame(0.05);
	m_BadBois->Create(300, -100, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f), 0, sm_Timer->getTime());
	m_BadBois->Render(sm_Direct3D, viewMatrix, orthoMatrix, sm_ShaderClass->m_ColorTextureShader, sm_Timer->getTime() - lastTime);

	m_Input->Update();
	lastTime = sm_Timer->getTime();
	return true;
}