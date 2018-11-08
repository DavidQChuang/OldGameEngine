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

bool TexturedSpritesheet::InitializeBuffers(ID3D11Device* device) {
	int left, right, top, bottom;
	H_2D_COLOR_RESOURCETYPE* colortype = 0;
	H_2D_COLOR_TEXTURE_RESOURCETYPE* coloredtype = 0;
	H_2D_TEXTURE_RESOURCETYPE* texturetype = 0;

	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	// Calculate the screen coordinates of the left side of the bitmap.
	left = -m_spriteWidth / 2;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + (float)m_spriteWidth;

	// Calculate the screen coordinates of the top of the bitmap.
	top = m_imageHeight / 2;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - (float)m_imageHeight;

	switch (m_shaderType) {
	case H_2D_COLOR_SHADERTYPE:
		// Create the vertex array.
		colortype = new H_2D_COLOR_RESOURCETYPE[m_vertexCount];
		if (!colortype) {
			return false;
		}

		// Load the vertex array with data.
		colortype[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		colortype[0].color = m_Color;

		colortype[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		colortype[1].color = m_Color;

		colortype[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		colortype[2].color = m_Color;

		colortype[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		colortype[3].color = m_Color;


		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(H_2D_COLOR_RESOURCETYPE) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = colortype;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		break;
	case H_2D_TEXTURE_SHADERTYPE:

		// Create the vertex array.
		texturetype = new H_2D_TEXTURE_RESOURCETYPE[m_vertexCount];
		if (!texturetype) {
			return false;
		}
		// Load the vertex array with data.
		texturetype[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		texturetype[0].texture = TextureCoords(0);

		texturetype[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		texturetype[1].texture = TextureCoords(1);

		texturetype[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		texturetype[2].texture = TextureCoords(2);

		texturetype[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		texturetype[3].texture = TextureCoords(3);

		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(H_2D_TEXTURE_RESOURCETYPE) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = texturetype;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		break;
	case H_2D_COLOR_TEXTURE_SHADERTYPE:
		// Create the vertex array.
		coloredtype = new H_2D_COLOR_TEXTURE_RESOURCETYPE[m_vertexCount];
		if (!coloredtype) {
			return false;
		}
		// Load the vertex array with data.
		coloredtype[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		coloredtype[0].color = m_Color;
		coloredtype[0].texture = TextureCoords(0);

		coloredtype[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		coloredtype[1].color = m_Color;
		coloredtype[1].texture = TextureCoords(1);

		coloredtype[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		coloredtype[2].color = m_Color;
		coloredtype[2].texture = TextureCoords(2);

		coloredtype[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		coloredtype[3].color = m_Color;
		coloredtype[3].texture = TextureCoords(3);


		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(H_2D_COLOR_TEXTURE_RESOURCETYPE) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = coloredtype;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		break;
	}

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result)) {
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices) {
		return false;
	}


	// Load the index array with data.
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 1;

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result)) {
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] colortype;
	colortype = 0;
	delete[] coloredtype;
	coloredtype = 0;
	delete[] texturetype;
	texturetype = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void TexturedSpritesheet::SetSprite(ID3D11DeviceContext* deviceContext, int s) {
	float left, right, top, bottom;
	H_2D_COLOR_TEXTURE_RESOURCETYPE* coloredtype = 0;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	H_2D_COLOR_TEXTURE_RESOURCETYPE* coloredPtr;
	HRESULT result;


	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if (s == m_currentSprite) {
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
		coloredtype[0].color = m_Color;
		coloredtype[0].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 0.0f);

		coloredtype[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		coloredtype[1].color = m_Color;
		coloredtype[1].texture = DirectX::XMFLOAT2(m_spriteSize * (m_currentSprite + 1), 1.0f);

		coloredtype[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		coloredtype[2].color = m_Color;
		coloredtype[2].texture = DirectX::XMFLOAT2(m_spriteSize * m_currentSprite, 1.0f);

		coloredtype[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		coloredtype[3].color = m_Color;
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

	m_currentSprite = s;

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);
	// Release the vertex array as it is no longer needed.
	delete[] coloredtype;
	coloredtype = 0;

	return;
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

	m_Color = color;

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);
	// Release the vertex array as it is no longer needed.
	delete[] coloredtype;
	coloredtype = 0;
}
