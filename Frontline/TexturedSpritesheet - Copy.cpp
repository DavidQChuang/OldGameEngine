#include "TexturedSpritesheet.h"
#include <sstream>
TexturedSpritesheet::TexturedSpritesheet() {
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_currentSprite = 0;
}

TexturedSpritesheet::TexturedSpritesheet(const TexturedSpritesheet& other) {
}


TexturedSpritesheet::~TexturedSpritesheet() {
}
bool TexturedSpritesheet::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int screenWidth, int screenHeight, int spriteWidth, int imageHeight, int spriteAmount) {
	bool result;


	// Store the screen size.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the size in pixels that this bitmap should be rendered at.
	m_imageWidth = spriteWidth * spriteAmount;
	m_imageHeight = imageHeight;

	m_originalImageWidth = m_imageWidth;
	m_originalImageHeight = imageHeight;

	m_spriteWidth = spriteWidth;
	m_originalSpriteWidth = spriteWidth;

	// Initialize the previous rendering position to negative one.
	m_previousPosX = -1;
	m_previousPosY = -1;

	m_previousSprite = 0;

	m_spriteAmount = spriteAmount;
	m_spriteSize = 1.0f / spriteAmount;

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result) return false;

	// Load the texture for this bitmap.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result) return false;

	return true;
}

void TexturedSpritesheet::SetSprite(int l) {
	m_currentSprite = l;
}

void TexturedSpritesheet::Resize() {
	m_imageWidth = m_originalImageWidth;
	m_spriteWidth = m_originalSpriteWidth;
	m_imageHeight = m_originalImageHeight;
}

void TexturedSpritesheet::Resize(int width, int height) {
	m_imageWidth = width * m_spriteAmount;
	m_spriteWidth = width;
	m_imageHeight = height;
}

bool TexturedSpritesheet::Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY) {
	bool result;
	m_posX = positionX;
	m_posY = positionY;
	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	result = UpdateBuffers(deviceContext, positionX, positionY);
	if (!result) return false;

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return true;
}


bool TexturedSpritesheet::Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY, DirectX::XMFLOAT4 color) {
	bool result;
	m_posX = positionX;
	m_posY = positionY;
	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	result = UpdateBuffers(deviceContext, positionX, positionY, color);
	if (!result) return false;

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return true;
}
bool TexturedSpritesheet::UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY) {
	float left, right, top, bottom;
	ColorVertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ColorVertexType* verticesPtr;
	HRESULT result;
	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if ((positionX == m_previousPosX) && (positionY == m_previousPosY) && (m_previousSprite == m_currentSprite)) {
		return true;
	}

	// If it has changed then update the position it is being rendered to.
	m_previousPosX = positionX;
	m_previousPosY = positionY;
	m_previousSprite = m_currentSprite;

	m_spriteWidth = m_imageWidth / m_spriteAmount;
	// Calculate the screen coordinates of the left side of the bitmap.
	left = (float)(m_screenWidth / 2 * -1) + (float)positionX;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + (float)m_spriteWidth;

	// Calculate the screen coordinates of the top of the bitmap.
	top = (float)(m_screenHeight / 2) - (float)positionY;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - (float)m_imageHeight;

	// Create the vertex array.
	vertices = new ColorVertexType[m_vertexCount];
	if (!vertices) {
		return false;
	}
	// Load the vertex array with data.
	// First triangle.
	vertices[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
	vertices[0].color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	vertices[0].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 0.0f);

	vertices[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	vertices[1].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 1.0f);

	vertices[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left
	vertices[2].color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	vertices[2].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 1.0f);

	// Second triangle.
	vertices[3].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
	vertices[3].color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	vertices[3].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 0.0f);

	vertices[4].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
	vertices[4].color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	vertices[4].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 0.0f);

	vertices[5].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
	vertices[5].color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	vertices[5].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 1.0f);
	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (ColorVertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(ColorVertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	return true;
}

bool TexturedSpritesheet::UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY, DirectX::XMFLOAT4 color) {
	float left, right, top, bottom;
	ColorVertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ColorVertexType* verticesPtr;
	HRESULT result;


	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if ((positionX == m_previousPosX) && (positionY == m_previousPosY)) {
		return true;
	}

	// If it has changed then update the position it is being rendered to.
	m_previousPosX = positionX;
	m_previousPosY = positionY;

	// Calculate the screen coordinates of the left side of the bitmap.
	left = (float)(m_screenWidth / 2 * -1) + (float)positionX;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + (float)m_imageWidth;

	// Calculate the screen coordinates of the top of the bitmap.
	top = (float)(m_screenHeight / 2) - (float)positionY;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - (float)m_imageHeight;
	// Create the vertex array.
	vertices = new ColorVertexType[m_vertexCount];
	if (!vertices) {
		return false;
	}

	// Load the vertex array with data.
	// First triangle.
	vertices[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
	//vertices[0].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 0.0f);
	vertices[0].color = color;

	vertices[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 1.0f);
	vertices[1].color = color;

	vertices[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
	vertices[2].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 1.0f);
	vertices[2].color = color;

	// Second triangle.
	vertices[3].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
	vertices[3].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 0.0f);
	vertices[3].color = color;

	vertices[4].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
	vertices[4].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 0.0f);
	vertices[4].color = color;

	vertices[5].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
	vertices[5].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 1.0f);
	vertices[5].color = color;

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (ColorVertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(ColorVertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	return true;
}
