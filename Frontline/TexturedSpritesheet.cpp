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
	H_DIMENSION spriteWidth, H_DIMENSION imageHeight, int spriteAmount) {
	bool result;

	// Store the size in pixels that this bitmap should be rendered at.
	m_imageWidth = spriteWidth * spriteAmount;
	m_imageHeight = imageHeight;
	m_spriteWidth = spriteWidth;
	
	m_shaderType = H_2D_TEXTURE_SHADERTYPE;

	m_Color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);

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
bool TexturedSpritesheet::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename, H_COLORRGBA color,
	H_DIMENSION spriteWidth, H_DIMENSION imageHeight, int spriteAmount) {
	bool result;

	// Store the size in pixels that this bitmap should be rendered at.
	m_imageWidth = spriteWidth * spriteAmount;
	m_imageHeight = imageHeight;
	m_spriteWidth = spriteWidth;

	m_shaderType = H_2D_COLOR_TEXTURE_SHADERTYPE;

	m_Color = color;

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

void TexturedSpritesheet::SetSprite(ID3D11DeviceContext* deviceContext, int l) {
	//(m_previousSprite == m_currentSprite)
	m_currentSprite = l;
}

void TexturedSpritesheet::SetColor(ID3D11DeviceContext* deviceContext, H_COLORRGBA color) {
	float left, right, top, bottom;
	H_2D_COLOR_TEXTURE_RESOURCETYPE* coloredtype = 0;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	H_2D_COLOR_TEXTURE_RESOURCETYPE* coloredPtr;
	HRESULT result;


	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if ((color.x == m_Color.x) && (color.y == m_Color.y) && (color.z == m_Color.z) && (color.w == m_Color.w)) {
		return;
	}
	// Calculate the screen coordinates of the left side of the bitmap.
	left = -m_spriteWidth / 2;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + (float)m_spriteWidth;

	// Calculate the screen coordinates of the top of the bitmap.
	top = m_imageHeight / 2;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - (float)m_imageHeight;
	switch (m_shaderType) {
	case H_2D_COLOR_TEXTURE_SHADERTYPE:
		// Create the vertex array.
		coloredtype = new H_2D_COLOR_TEXTURE_RESOURCETYPE[m_vertexCount];
		if (!coloredtype) {
			return;
		}
		// Load the vertex array with data.
		coloredtype[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		coloredtype[0].color = color;
		coloredtype[0].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 0.0f);

		coloredtype[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		coloredtype[1].color = color;
		coloredtype[1].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 1.0f);

		coloredtype[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		coloredtype[2].color = color;
		coloredtype[2].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 1.0f);

		coloredtype[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		coloredtype[3].color = color;
		coloredtype[3].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 0.0f);

		// Lock the vertex buffer so it can be written to.
		result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return;
		}
		// Get a pointer to the data in the vertex buffer.
		coloredPtr = (H_2D_COLOR_TEXTURE_RESOURCETYPE*)mappedResource.pData;

		// Copy the data into the vertex buffer.
		memcpy(coloredPtr, (void*)coloredtype, (sizeof(H_2D_COLOR_TEXTURE_RESOURCETYPE) * m_vertexCount));

	}
	m_previousSprite = m_currentSprite;

	m_Color = color;

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);
	// Release the vertex array as it is no longer needed.
	delete[] coloredtype;
	coloredtype = 0;

	return;
}
