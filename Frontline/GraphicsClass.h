#pragma once

#include "CameraClass.h"
#include "ShaderClass.h"

#include "Input.h"
#include "SceneGame.h"
#include "SceneSplash.h"
#include "SceneMainMenu.h"

#include "RenderTexture.h"
#include "RenderedTexture.h"
#include "TextureShaderClass.h"

class GraphicsClass {
public:
	GraphicsClass(Input*);
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool Render();
	bool RenderScene();
	bool RenderToTexture();
	bool RenderTheTexture();
	// 0 = fullscreen, 1 = windowed with titlebar(default), 2 = windowed without titlebar

private:

	D3DClass* m_Direct3D;
	CameraClass* m_Camera;

	SceneSplash* m_splash;
	SceneMainMenu* m_menu;
	SceneGame* m_game;

	Input* m_Input;
	ShaderClass* m_shaders;
	RenderTexture* m_RenderTexture;
	RenderTexture* m_RenderrTexture;
	RenderedTexture* m_RenderedTexture;
};