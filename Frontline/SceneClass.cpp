#include "SceneClass.h"


SceneClass::SceneClass(HWND hwnd, D3DClass* d3dclass, CameraClass* cameraclass, TextureShaderClass* textureshaderclass, TransparencyShaderClass* transparencyshaderclass) {
	sm_hwnd = hwnd;
	sm_Direct3D = d3dclass;
	sm_Camera = cameraclass;
	sm_TextureShader = textureshaderclass;
	sm_TransparencyShader = transparencyshaderclass;
	m_active = false;
	sm_Timer = new Timer();
}


SceneClass::SceneClass(const SceneClass& other) {
}


SceneClass::~SceneClass() {
}