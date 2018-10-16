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
	virtual bool Render(XMMATRIX, XMMATRIX, XMMATRIX)=0;
	bool m_active;

	bool RenderRect(TexturedRect*, XMMATRIX, XMMATRIX, int);
	bool RenderRect(TexturedRect*, float, XMMATRIX, XMMATRIX, int);
	bool RenderRect(TexturedRect*, int, int, XMMATRIX, XMMATRIX, int);
	bool RenderRect(TexturedRect*, int, int, float, XMMATRIX, XMMATRIX, int);
	//int x, int y, [float rot], [int spritenumber]
	//after matrices, shader info
	bool RenderSpritesheet(TexturedSpritesheet*, int, int, XMMATRIX, XMMATRIX, int);
	bool RenderSpritesheet(TexturedSpritesheet*, int, int, int, XMMATRIX, XMMATRIX, int);
	bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, XMMATRIX, XMMATRIX, int);
	bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, int, XMMATRIX, XMMATRIX, int);
	//bool RenderSpritesheet(TexturedSpritesheet*, int, int, float, int, XMMATRIX, XMMATRIX, int);

	bool RenderModel(ModelClass*, XMMATRIX, XMMATRIX, int);
private:
protected:
	HWND sm_hwnd;
	D3DClass* sm_Direct3D;
	CameraClass* sm_Camera;
	ShaderClass* sm_ShaderClass;
	Timer* sm_Timer;
};
