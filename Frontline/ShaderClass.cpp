#include "ShaderClass.h"
ShaderClass::ShaderClass(D3DClass* directX) {
	m_DirectX = directX;
	m_ColorShader = 0;
	m_LightShader = 0;
	m_RefractionShader = 0;
	m_TextureShader = 0;
	m_TransparencyShader = 0;
	m_WaterShader = 0;
	// 0 = fullscreen, 1 = windowed with titlebar(default), 2 = windowed without titlebar
}


ShaderClass::ShaderClass(const ShaderClass& other) {
}


ShaderClass::~ShaderClass() {
}


bool ShaderClass::Initialize(HWND hwnd) {
	bool result;
	// Create the texture shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader) {
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_DirectX->GetDevice(), hwnd);
	if (!result) {
		MessageBoxW(hwnd, L"Could not initialize the color shader.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader) {
		return false;
	}

	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_DirectX->GetDevice(), hwnd);
	if (!result) {
		MessageBoxW(hwnd, L"Could not initialize the texture shader.", L"Error", MB_OK);
		return false;
	}

	// Create the transparent shader object.
	m_TransparencyShader = new TransparencyShaderClass;
	if (!m_TransparencyShader) {
		return false;
	}

	// Initialize the transparent shader object.
	result = m_TransparencyShader->Initialize(m_DirectX->GetDevice(), hwnd);
	if (!result) {
		MessageBoxW(hwnd, L"Could not initialize the transparency shader.", L"Error", MB_OK);
		return false;
	}
	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader) {
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_DirectX->GetDevice(), hwnd);
	if (!result) {
		MessageBoxW(hwnd, L"Could not initialize the light shader.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light) {
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDirection(0.5f, 0.5f, 0.5f);

	return true;
}


void ShaderClass::Shutdown() {
	//Release the color shader object.
	if (m_ColorShader) {
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	//Release the light shader object.
	if (m_LightShader) {
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	//Release the refraction shader object.
	if (m_RefractionShader) {
		m_RefractionShader->Shutdown();
		delete m_RefractionShader;
		m_RefractionShader = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader) {
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	//Release the transparency shader object.
	if (m_TransparencyShader) {
		m_TransparencyShader->Shutdown();
		delete m_TransparencyShader;
		m_TransparencyShader = 0;
	}

	//Release the water shader object.
	if (m_WaterShader) {
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	//Release the Direct3D object.
	if (m_DirectX) {
		m_DirectX->Shutdown();
		delete m_DirectX;
		m_DirectX = 0;
	}

	// Release the light object.
	if (m_Light) {
		delete m_Light;
		m_Light = 0;
	}
	return;
}