#include "graphicsclass.h"
GraphicsClass::GraphicsClass(Input* input) {
	m_Direct3D = 0;
	m_Camera = 0;
	m_splash = 0;
	m_menu = 0;
	m_shaders = 0;
	m_game = 0;
	m_Input = input;
	m_RenderTexture = 0;
	m_RenderedTexture = 0;
	// 0 = fullscreen, 1 = windowed with titlebar(default), 2 = windowed without titlebar
}


GraphicsClass::GraphicsClass(const GraphicsClass& other) {
}


GraphicsClass::~GraphicsClass() {
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd) {

	bool result;

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D) {
		return false;
	}

	bool state = false;
	// Initialize the Direct3D object.
	//if (Options::WINDOW_STATE == 0) {
	//	state = true;
	//}
	float SCREEN_DEPTH = 1000.0f;
	float SCREEN_NEAR = 0.1f;
	result = m_Direct3D->Initialize(screenWidth, screenHeight, true, hwnd, state, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBoxW(hwnd, L"Could not initialize DirectX.", L"Error", MB_OK);
		return false;
	}

	m_shaders = new ShaderClass(m_Direct3D);
	if (!m_shaders) {
		MessageBoxW(hwnd, L"Could not initialize shaders.", L"Error", MB_OK);
		return false;
	}
	m_shaders->Initialize(hwnd);

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera) {
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	m_splash = new SceneSplash(hwnd, m_Direct3D, m_Camera, m_shaders);
	m_splash->Initialize();

	m_menu = new SceneMainMenu(hwnd, m_Direct3D, m_Camera, m_shaders);
	m_menu->Initialize();

	m_game = new SceneGame(hwnd, m_Direct3D, m_Camera, m_shaders, m_Input);
	m_game->Initialize();

	// Create the render to texture object.
	/*m_RenderTexture = new RenderTexture;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}


	m_RenderedTexture = new RenderedTexture;
	if (!m_RenderedTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderedTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}*/
	return true;
}


void GraphicsClass::Shutdown() {
	if (m_splash) {
		m_splash->Shutdown();
		delete m_splash;
		m_splash = 0;
	}
	if (m_menu) {
		m_menu->Shutdown();
		delete m_menu;
		m_menu = 0;
	}
	if (m_game) {
		m_game->Shutdown();
		delete m_game;
		m_game = 0;
	}
	// Release the camera object.
	if (m_Camera) {
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D) {
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
	return;
}


bool GraphicsClass::Frame() {
	bool result;
	// Render the graphics scene.
	result = Render();
	if (!result) {
		return false;
	}
	return true;
}


bool GraphicsClass::Render() {
	bool result;	
	// Render the entire scene to the texture first.
	/*result = RenderToTexture();
	if (!result) {
		return false;
	}*/

	result = RenderScene();
	if (!result) {
		return false;
	}
	/*
	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_RenderTexture->GetOrthoMatrix(orthoMatrix);

	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_RenderedTexture->Render(m_Direct3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}


	// Render the debug window using the texture shader.
	result = m_shaders->m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_RenderedTexture->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_RenderTexture->GetShaderResourceView());
	if (!result)
	{
		return false;
	}
	// Turn the Z buffer back on now that all 2D rendering has completed.
	*/
	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}
bool GraphicsClass::RenderToTexture() {
	bool result;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext(), m_Direct3D->GetDepthStencilView());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), m_Direct3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);
	
	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = RenderScene();
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	return true;

}
bool GraphicsClass::RenderScene() {
	DirectX::XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	bool result;
	static float rotation = 0.0f;


	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	switch (Options::Scene) {
	case 0:
		result = m_splash->Render(viewMatrix, projectionMatrix, orthoMatrix);
		if (!result) {
			return false;
		}
		break;
	case 1:
		result = m_menu->Render(viewMatrix, projectionMatrix, orthoMatrix);
		if (!result) {
			return false;
		}
		break;
	case 2:
		result = m_game->Render(viewMatrix, projectionMatrix, orthoMatrix);
		if (!result) {
			return false;
		}
		break;
	}
	m_Direct3D->TurnZBufferOn();
	return true;
}