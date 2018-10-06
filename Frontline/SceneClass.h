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
	SceneClass(HWND hwnd, D3DClass*, CameraClass*, TextureShaderClass*, TransparencyShaderClass*);
	SceneClass(const SceneClass&);
	~SceneClass();
	virtual bool Initialize()=0;
	virtual void Shutdown()=0;
	virtual bool Render(XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX)=0;
	bool m_active;

protected:
	HWND sm_hwnd;
	D3DClass* sm_Direct3D;
	CameraClass* sm_Camera;
	TextureShaderClass* sm_TextureShader;
	TransparencyShaderClass* sm_TransparencyShader;
	Timer* sm_Timer;
};
