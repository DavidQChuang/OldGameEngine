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
	virtual bool Initialize()=0;
	virtual void Shutdown()=0;
	virtual bool Render(XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX)=0;
	bool m_active;

	bool RenderRect(TexturedRect*, int, int, XMMATRIX, XMMATRIX, XMMATRIX, int);
	bool RenderSpritesheet(TexturedSpritesheet*, int, int, XMMATRIX, XMMATRIX, XMMATRIX, int);
	bool RenderSpritesheet(TexturedSpritesheet*, int, int, int, XMMATRIX, XMMATRIX, XMMATRIX, int);
	//void RenderObject(ModelClass*, XMMATRIX, XMMATRIX, XMMATRIX, int);



protected:
	HWND sm_hwnd;
	D3DClass* sm_Direct3D;
	CameraClass* sm_Camera;
	ShaderClass* sm_ShaderClass;
	Timer* sm_Timer;
};
