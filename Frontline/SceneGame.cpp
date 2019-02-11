#include "SceneGame.h"


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
	m_lastTime = 0;
}

bool SceneGame::Initialize() {
	bool result;
	//(int x, int y, int width, int height, int max, int lifetime, int lifeRandom, int gen, int genRand)
	m_ParticleSystem = new TitlePS(3000);
	if (!m_ParticleSystem) {
		return false;
	}
	m_ParticleSystem->SetParameters(0, 600, 800, 1, 3000, 100, 1, 0);
	result = m_ParticleSystem->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Particles\\Fire.sprite",
		16 * 4, 16 * 4);

	m_BadBois = new EnemySystem();
	m_BadBois->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Enemies\\Enemy1.sprites",
		18 * 3, 18 * 3, 4);
	m_BadBois->SetRatePerFrame(0.05);

	m_DODGE = new EnemyBulletSystem(600);
	m_DODGE->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Bullets\\Bullets.sprites",
		6 * 3, 6 * 3, 3);

	m_HealthBar = InitializeRect(m_HealthBar, DirectX::XMFLOAT4(213.f / 255.f, 29.f / 255.f, 29.f / 255.f, 1.f), 
		(8 * 3) - 1, 31 * 3);
	m_HealthBar->SetPos(750, 20 * 3);

	m_MagicBar = InitializeRect(m_MagicBar, DirectX::XMFLOAT4(30.f / 255.f, 151.f / 255.f, 195.f / 255.f, 1.f),
		(8 * 3) - 1, 31 * 3);
	m_MagicBar->SetPos(750, 66 * 3);

	m_HealthBarBackground = InitializeRect(m_HealthBarBackground, DirectX::XMFLOAT4(155.f / 255.f, 44.f / 255.f, 44.f / 255.f, 1.f),
		(8 * 3) - 1, 31 * 3);
	m_HealthBarBackground->SetPos(750, 20 * 3);

	m_MagicBarBackground = InitializeRect(m_MagicBarBackground, DirectX::XMFLOAT4(25.f / 255.f, 110.f / 255.f, 150.f / 255.f, 1.f),
		(8 * 3) - 1, 31 * 3);
	m_MagicBarBackground->SetPos(750, 66 * 3);

	m_HUD = InitializeRect(m_HUD, ".\\Data\\Images\\GUI\\HUD.sprite",
		14 * 3, 85 * 3);
	m_HUD->SetPos(740, 12 * 3);
	
	///m_FPS = new TexturedText();
	///m_FPS->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
	///	800,600,FONT_PIX_FIVE,5*3);

	m_BulletKeys = InitializeRect(m_BulletKeys, ".\\Data\\Images\\GUI\\SelectKey.sprite",
		14 * 3, 36 * 3);
	m_BulletKeys->SetPos(740, 36 + 97 * 3);

	m_AbilityContainers = InitializeRect(m_AbilityContainers, ".\\Data\\Images\\GUI\\BulletContainer.sprite",
		14 * 3, 42 * 3);
	m_AbilityContainers->SetPos(740, 36 + 106 * 3);

	m_BulletSelect = InitializeSpritesheet(m_BulletSelect, ".\\Data\\Images\\Sprites\\Bullets\\Bullets.sprites",
		12 * 3, 12 * 3, 3);
	m_BulletSelect->SetPos(740 + 3, 36 + 107 * 3);

	m_Background = new TexturedRect();
	if (!m_Background) {
		return false;
	}

	result = m_Background->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Backgrounds\\DABDABSAVAGE.background",
		800, 600);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the game background. 1", L"Error", MB_OK);
		return false;
	}
	m_Background->SetPos(740, 36 + 97 * 3);

	m_Player = new Player(m_Input, 384, 350);
	if (!m_Player) {
		return false;
	}

	result = m_Player->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		".\\Data\\Images\\Sprites\\Character\\Player.sprites",
		".\\Data\\Images\\Sprites\\Bullets\\Bullets.sprites",
		16 * 3, 18 * 3, 8);
	if (!result) {
		MessageBoxW(sm_hwnd, L"Could not initialize the player sprite. 1", L"Error", MB_OK);
		return false;
	}
	m_Player->m_Texture->SetPos(m_Player->coords.x, m_Player->coords.y);

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

	sm_Timer.Start();
	sm_ShaderClass->m_Light->SetAmbientColor(0.2f, 0.2f, 0.2f, 1.0f);
	sm_ShaderClass->m_Light->SetDiffuseColor(0.f, 0.f, 0.f, 1.0f);

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

	if (m_HealthBar) {
		m_HealthBar->Shutdown();
		delete m_HealthBar;
		m_HealthBar = 0;
	}

	if (m_MagicBar) {
		m_MagicBar->Shutdown();
		delete m_MagicBar;
		m_MagicBar = 0;
	}

	if (m_HealthBarBackground) {
		m_HealthBarBackground->Shutdown();
		delete m_HealthBarBackground;
		m_HealthBarBackground = 0;
	}

	if (m_MagicBarBackground) {
		m_MagicBarBackground->Shutdown();
		delete m_MagicBarBackground;
		m_MagicBarBackground = 0;
	}

	if (m_DODGE) {
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
bool SceneGame::Render(XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMMATRIX orthoMatrix) {
	if (m_lastTime == 0) m_lastTime = sm_Timer.getTime();
	bool result;
	switch (m_GameState) {
	case 0:
		rotation += (sm_Timer.getTime() - m_lastTime) / 4;
		if (rotation > 360)
			rotation = 0;

		m_Player->Frame(true, sm_Timer.getTime());
		m_Player->m_Texture->SetSprite(sm_Direct3D->GetDeviceContext(), static_cast<int>(sm_Timer.getTime() / 90) % 6);

		m_Player->m_Bullets->SetState(true);

		m_BadBois->SetState(true);
		if (m_Player->m_Texture->m_currentSprite == 1) {
			m_BadBois->Create(300, -100, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f), 0, sm_Timer.getTime());
		}

		if (m_Input->OnKeyDown(VK_ESCAPE))
			m_GameState = 1;
		break;
	case 1:
		m_Player->m_Bullets->SetState(false);
		m_BadBois->SetState(false);
		m_Player->Frame(false, sm_Timer.getTime());

		if (m_Input->OnKeyDown(VK_ESCAPE))
			m_GameState = 0;
		break;
	}
	m_Model->Render(sm_Direct3D->GetDeviceContext());

	XMMATRIX rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(0, XMConvertToRadians(rotation), XMConvertToRadians(rotation));
	XMMATRIX cubeMatrix = rotMatrix * DirectX::XMMatrixTranslation(0.f, 1.f, 0.f);
	// Render the model using the light shader.
	result = sm_ShaderClass->m_LightShader->Render(sm_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), cubeMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), sm_ShaderClass->m_Light->GetDirection(), sm_ShaderClass->m_Light->GetAmbientColor(), sm_ShaderClass->m_Light->GetDiffuseColor());
	if (!result) {
		return false;
	}

	sm_Direct3D->TurnZBufferOff();

	for (int bigoof = 0; bigoof < 6; bigoof++) {
		m_ParticleSystem->Create(0, 0, -5, -3);
		if (bigoof == 0) {
			m_ParticleSystem->Create(0, 0, -8, -5);
		}
	}
	//m_ParticleSystem->Render(sm_Direct3D, viewMatrix, orthoMatrix, sm_ShaderClass);

	m_BadBois->Render(sm_Direct3D, viewMatrix, orthoMatrix, sm_ShaderClass->m_ColorTextureShader, m_Player->m_Bullets->GetTexture(), m_Player->m_Bullets->m_Bullets, m_Player->m_Bullets->m_Max, sm_Timer.getTime() - m_lastTime);

	m_Player->m_Texture->SetPos(m_Player->coords.x, m_Player->coords.y);
	result = RenderSpritesheet(m_Player->m_Texture, viewMatrix, orthoMatrix, H_2D_TEXTURE_SHADERTYPE);
	if (!result) return false;

	m_Player->RenderBullets(sm_Direct3D, viewMatrix, orthoMatrix, sm_ShaderClass->m_ColorTextureShader);
	
	RenderRect(m_HealthBarBackground, viewMatrix, orthoMatrix, H_2D_COLOR_SHADERTYPE);
	RenderRect(m_MagicBarBackground, viewMatrix, orthoMatrix, H_2D_COLOR_SHADERTYPE);

	m_HealthBar->SetSize(1.f, m_Player->m_hp / 3);
	RenderRect(m_HealthBar, viewMatrix, orthoMatrix, H_2D_COLOR_SHADERTYPE);

	m_MagicBar->SetSize(1.f, m_Player->m_mp / 6);
	RenderRect(m_MagicBar, viewMatrix, orthoMatrix, H_2D_COLOR_SHADERTYPE);

	RenderRect(m_HUD, viewMatrix, orthoMatrix, H_2D_TEXTURE_SHADERTYPE);
	RenderRect(m_BulletKeys, viewMatrix, orthoMatrix, H_2D_TEXTURE_SHADERTYPE);
	RenderRect(m_AbilityContainers, viewMatrix, orthoMatrix, H_2D_TEXTURE_SHADERTYPE);

	RenderSpritesheet(m_BulletSelect, m_Player->m_BulletType, viewMatrix, orthoMatrix, H_2D_TEXTURE_SHADERTYPE);
	
	m_Input->Update();
	m_lastTime = sm_Timer.getTime();
	return true;
}
