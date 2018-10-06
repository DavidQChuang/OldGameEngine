#ifndef _SHADERCLASS_H_
#define _SHADERCLASS_H_

#include "D3DClass.h"
#include "colorshader.h"
#include "LightShaderClass.h"
#include "RefractionShaderClass.h"
#include "TextureShaderClass.h"
#include "TransparencyShaderClass.h"
#include "WaterShaderClass.h"
#include "LightClass.h"

class ShaderClass {
public:
	ShaderClass(D3DClass*);
	ShaderClass(const ShaderClass&);
	~ShaderClass();

	bool Initialize(HWND);
	void Shutdown();
	// 0 = fullscreen, 1 = windowed with titlebar(default), 2 = windowed without titlebar
	ColorShaderClass* m_ColorShader;
	LightShaderClass* m_LightShader;
	RefractionShaderClass* m_RefractionShader;
	TextureShaderClass* m_TextureShader;
	TransparencyShaderClass* m_TransparencyShader;
	WaterShaderClass* m_WaterShader;
	LightClass* m_Light;
private:
	D3DClass* m_DirectX;
};
#endif