#pragma once
#include "SceneClass.h"
#include "TitlePS.h"
class SceneMainMenu : public SceneClass {
public:
	SceneMainMenu(HWND, D3DClass*, CameraClass*, ShaderClass*);
	bool Initialize();
	void Shutdown();
	bool Render(XMMATRIX, XMMATRIX, XMMATRIX);

private:
	POINT m_cursorPos;
	TexturedRect* m_Background;
	TexturedRect* m_Title;
	TexturedButton* m_Play;
	TitlePS* m_Flame;
};
