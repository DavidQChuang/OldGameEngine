#pragma once
#include "SceneClass.h"

class SceneSplash : public SceneClass {
public:
	SceneSplash(HWND, D3DClass*, CameraClass*, ShaderClass*);
	bool Initialize();
	void Shutdown();
	bool Render(XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	TexturedRect* m_Splash;
};