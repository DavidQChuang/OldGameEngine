#pragma once
#include "SceneClass.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyBS.h"
#include "Timer.h"
#include "TitlePS.h"
class SceneGame : public SceneClass {
protected:
public:
	SceneGame(HWND, D3DClass*, CameraClass*, ShaderClass*, Input*);
	bool Initialize();
	void Shutdown();
	bool Render(XMMATRIX, XMMATRIX, XMMATRIX);

private:
	POINT m_CursorPos;
	Player* m_Player;
	TexturedRect* m_Background;
	TexturedRect* m_HUD;
	TexturedRect* m_BulletKeys;
	TexturedRect* m_AbilityContainers;
	TexturedRect* m_HealthBar;
	TexturedRect* m_MagicBar;
	TexturedRect* m_HealthBarBackground;
	TexturedRect* m_MagicBarBackground;
	TexturedSpritesheet* m_BulletSelect;
	TexturedSpritesheet* m_AbilitySelect;

	TitlePS* m_ParticleSystem;

	EnemySystem* m_BadBois;
	EnemyBulletSystem* m_DODGE;

	ModelClass* m_Model;

	Input* m_Input;

	int m_GameState;

	bool m_TimerStart;

	double m_lastTime;
	int m_Counter;
};
