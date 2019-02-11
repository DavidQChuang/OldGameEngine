#include "SceneClass.h"


SceneClass::SceneClass(HWND hwnd, D3DClass* d3dclass, CameraClass* cameraclass, ShaderClass* shaderclass) {
	sm_hwnd = hwnd;
	sm_Direct3D = d3dclass;
	sm_Camera = cameraclass;
	sm_ShaderClass = shaderclass;
	m_active = false;
	//sm_Timer;
}


SceneClass::SceneClass(const SceneClass& other) {
}


SceneClass::~SceneClass() {
}

//
// Inline for initializing a TexturedRect with a color shader type.
//
TexturedRect* SceneClass::InitializeRect(TexturedRect* object, H_RGBA color, H_DIMENSION width, H_DIMENSION height) {
	object = new TexturedRect();
	if (!object) {
		std::string stringg = "Could not initialize object with boi color \n" + to_string(color.x * 255) + ", " + DecatenateRGBA(color);
		MessageBoxA(sm_hwnd, stringg.c_str(), "Error", MB_OK);
	}

	if (!(object->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		color,
		width, height))) {
		std::string stringg = ", " + to_string(color.w * 255);
		MessageBoxA(sm_hwnd, stringg.c_str(), "Error", MB_OK); "Could not initialize object with fuck  color \n" + DecatenateRGBA(color);
		//MessageBoxA(sm_hwnd, lpcwstr, L"Error", MB_OK);
	}
	return object;
	//MessageBoxA(sm_hwnd, lpcwstr, L"Error", MB_OK);
}

//
// Inline for initializing a TexturedRect with a texture shader type.
//
TexturedRect* SceneClass::InitializeRect(TexturedRect* object, char* filename, H_DIMENSION width, H_DIMENSION height) {
	object = new TexturedRect();
	if (!object) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename);
		//MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}

	if (!(object->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		filename,
		width, height))) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename);
		MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}
	return object;
	//MessageBoxA(sm_hwnd, lpcwstr, L"Error", MB_OK);
}

//
// Inline for initializing a TexturedRect with a colored texture shader type.
//
TexturedRect* SceneClass::InitializeRect(TexturedRect* object, char* filename, H_RGBA color, H_DIMENSION width, H_DIMENSION height) {
	object = new TexturedRect();
	if (!object) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename) + std::string("\n and color \n") + DecatenateRGBA(color);
		MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}

	if (!(object->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		filename, color,
		width, height))) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename) + std::string("\n and color \n") + DecatenateRGBA(color);;
		MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}
	return object;
}



//
// Inline for initializing a TexturedRect with a texture shader type.
//
TexturedSpritesheet* SceneClass::InitializeSpritesheet(TexturedSpritesheet* object, char* filename, H_RGBA color, H_DIMENSION width, H_DIMENSION height, int sprites) {
	object = new TexturedSpritesheet();
	if (!object) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename) + std::string("\n and color \n") + DecatenateRGBA(color);;
		MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}

	if (!(object->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		filename, color,
		width, height, sprites))) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename) + std::string("\n and color \n") + DecatenateRGBA(color);;
		MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}
	std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename) + std::string("\n and color \n") + DecatenateRGBA(color);;
	MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	return object;
}
//
// Inline for initializing a TexturedRect with a colored texture shader type.
//
TexturedSpritesheet* SceneClass::InitializeSpritesheet(TexturedSpritesheet* object, char* filename, H_DIMENSION width, H_DIMENSION height, int sprites) {
	object = new TexturedSpritesheet();
	if (!object) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename);
		MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}

	if (!(object->Initialize(sm_Direct3D->GetDevice(), sm_Direct3D->GetDeviceContext(),
		filename,
		width, height, sprites))) {
		std::string thing = std::string("Could not initialize object with texture file \n") + std::string(filename);
		MessageBoxA(sm_hwnd, thing.c_str(), "Error", MB_OK);
	}
	return object;
}