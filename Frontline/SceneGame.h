#pragma once
#include "SceneClass.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyBS.h"
#include "Timer.h"
class SceneGame : public SceneClass {
protected:
public:
	SceneGame(HWND, D3DClass*, CameraClass*, ColorShaderClass*, TextureShaderClass*, TransparencyShaderClass*, LightShaderClass*, LightClass*, Input*);
	bool Initialize();
	void Shutdown();
	bool Render(XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	POINT m_CursorPos;
	Player* m_Player;
	TexturedRect* m_Background;
	TexturedRect* m_HUD;
	TexturedRect* m_BulletKeys;
	TexturedRect* m_AbilityContainers;
	TexturedSpritesheet* m_BulletSelect;
	TexturedSpritesheet* m_AbilitySelect;

	EnemySystem* m_BadBois;
	EnemyBulletSystem* m_DODGE;

	ModelClass* m_Model;

	LightClass* m_Light;
	LightShaderClass* m_LightShader;
	ColorShaderClass* m_ColorShader;

	Input* m_Input;

	int m_GameState;

	bool m_TimerStart;

	int m_Counter;
};
