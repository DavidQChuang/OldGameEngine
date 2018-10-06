#include "SceneClass.h"

class SceneSSSSSS : public SceneClass {
public:
	SceneSSSSSS(HWND, D3DClass*, CameraClass*, TextureShaderClass*, TransparencyShaderClass*);
	bool Initialize();
	void Shutdown();
	bool Render(XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	TexturedRect* m_Splash;
};
