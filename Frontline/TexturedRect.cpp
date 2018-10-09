#include "TexturedRect.h"
#include <sstream>
TexturedRect::TexturedRect() {
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
}


TexturedRect::TexturedRect(const TexturedRect& other) {
}


TexturedRect::~TexturedRect() {
}

bool TexturedRect::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	DirectX::XMFLOAT4 color,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight) {
	bool result;


	// Store the screen size.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the size in pixels that this bitmap should be rendered at.
	m_imageWidth = imageWidth;
	m_imageHeight = imageHeight;

	m_originalImageWidth = imageWidth;
	m_originalImageHeight = imageHeight;

	m_shaderType = COLOR_TYPE;

	// Initialize the previous rendering position to negative one.
	m_previousPosX = -1;
	m_previousPosY = -1;

	m_Color = color;
	m_previousColor = color;

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result) {
		return false;
	}

	return true;
}

bool TexturedRect::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight) {
	bool result;


	// Store the screen size.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the size in pixels that this bitmap should be rendered at.
	m_imageWidth = imageWidth;
	m_imageHeight = imageHeight;

	m_originalImageWidth = imageWidth;
	m_originalImageHeight = imageHeight;

	m_shaderType = TEXTURE_TYPE;

	// Initialize the previous rendering position to negative one.
	m_previousPosX = -1;
	m_previousPosY = -1;

	m_Color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	m_previousColor = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result) {
		return false;
	}

	// Load the texture for this bitmap.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result) {
		return false;
	}

	return true;
}

bool TexturedRect::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename, DirectX::XMFLOAT4 color,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight) {
	bool result;


	// Store the screen size.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the size in pixels that this bitmap should be rendered at.
	m_imageWidth = imageWidth;
	m_imageHeight = imageHeight;

	m_originalImageWidth = imageWidth;
	m_originalImageHeight = imageHeight;

	m_shaderType = COLOR_TEXTURE_TYPE;
	
	m_Color = color;
	m_previousColor = color;

	// Initialize the previous rendering position to negative one.
	m_previousPosX = -1;
	m_previousPosY = -1;

	m_Color = color;
	m_Color = color;

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result) {
		return false;
	}

	// Load the texture for this bitmap.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result) {
		return false;
	}

	return true;
}


void TexturedRect::Shutdown() {
	// Release the bitmap texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


bool TexturedRect::Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY) {
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


bool TexturedRect::Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY, DirectX::XMFLOAT4 color) {
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

int TexturedRect::GetIndexCount() {
	return m_indexCount;
}


ID3D11ShaderResourceView* TexturedRect::GetTexture() {
	return m_Texture->GetTexture();
}


bool TexturedRect::InitializeBuffers(ID3D11Device* device) {
	ColorVertexType* colortype = 0;
	ColoredVertexType* coloredtype = 0;
	VertexType* texturetype = 0;

	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	switch (m_shaderType) {
	case COLOR_TYPE:
		// Create the vertex array.
		colortype = new ColorVertexType[m_vertexCount];
		if (!colortype) {
			return false;
		}
		// Initialize vertex array to zeros at first.
		memset(colortype, 0, (sizeof(ColorVertexType) * m_vertexCount));


		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(ColorVertexType) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = colortype;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		break;
	case TEXTURE_TYPE:
		// Create the vertex array.
		texturetype = new VertexType[m_vertexCount];
		if (!texturetype) {
			return false;
		}
		// Initialize vertex array to zeros at first.
		memset(texturetype, 0, (sizeof(VertexType) * m_vertexCount));


		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = texturetype;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		break;
	case COLOR_TEXTURE_TYPE:
		// Create the vertex array.
		coloredtype = new ColoredVertexType[m_vertexCount];
		if (!coloredtype) {
			return false;
		}
		// Initialize vertex array to zeros at first.
		memset(coloredtype, 0, (sizeof(ColoredVertexType) * m_vertexCount));


		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(ColoredVertexType) * m_vertexCount;
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

void TexturedRect::Resize() {
	m_imageWidth = m_originalImageWidth;
	m_imageHeight = m_originalImageHeight;
}

void TexturedRect::Resize(int width, int height) {
	m_imageWidth = width;
	m_imageHeight = height;
}

void TexturedRect::ShutdownBuffers() {
	// Release the index buffer.
	if (m_indexBuffer) {
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer) {
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}

bool TexturedRect::UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY, DirectX::XMFLOAT4 color) {
	float left, right, top, bottom;
	ColorVertexType* colortype = 0;
	ColoredVertexType* coloredtype = 0;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ColorVertexType* colorPtr;
	ColoredVertexType* coloredPtr;
	HRESULT result;


	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if ((positionX == m_previousPosX) && (positionY == m_previousPosY) && (color.x == m_previousColor.x) && (color.y == m_previousColor.y) && (color.z == m_previousColor.z) && (color.w == m_previousColor.w)) {
		return true;
	}

	// Calculate the screen coordinates of the left side of the bitmap.
	left = (float)(m_screenWidth / 2 * -1) + (float)positionX;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + (float)m_imageWidth;

	// Calculate the screen coordinates of the top of the bitmap.
	top = (float)(m_screenHeight / 2) - (float)positionY;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - (float)m_imageHeight;

	switch (m_shaderType) {
	case COLOR_TYPE:
		// Create the vertex array.
		colortype = new ColorVertexType[m_vertexCount];
		if (!colortype) {
			return false;
		}
		// Load the vertex array with data.
		colortype[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		colortype[0].color = color;

		colortype[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		colortype[1].color = color;

		colortype[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		colortype[2].color = color;

		colortype[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		colortype[3].color = color;

		// Lock the vertex buffer so it can be written to.
		result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return false;
		}

		// Get a pointer to the data in the vertex buffer.
		colorPtr = (ColorVertexType*)mappedResource.pData;

		// Copy the data into the vertex buffer.
		memcpy(colorPtr, (void*)colortype, (sizeof(ColorVertexType) * m_vertexCount));

		// Unlock the vertex buffer.
		deviceContext->Unmap(m_vertexBuffer, 0);
		break;
	case TEXTURE_TYPE:
		UpdateBuffers(deviceContext, positionX, positionY);
		break;
	case COLOR_TEXTURE_TYPE:
		// Create the vertex array.
		coloredtype = new ColoredVertexType[m_vertexCount];
		if (!coloredtype) {
			return false;
		}
		// Load the vertex array with data.
		coloredtype[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		coloredtype[0].color = color;
		coloredtype[0].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

		coloredtype[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		coloredtype[1].color = color;
		coloredtype[1].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

		coloredtype[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		coloredtype[2].color = color;
		coloredtype[2].texture = DirectX::XMFLOAT2(0.0f, 1.0f);

		coloredtype[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		coloredtype[3].color = color;
		coloredtype[3].texture = DirectX::XMFLOAT2(1.0f, 0.0f);


		// Lock the vertex buffer so it can be written to.
		result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return false;
		}

		// Get a pointer to the data in the vertex buffer.
		coloredPtr = (ColoredVertexType*)mappedResource.pData;

		// Copy the data into the vertex buffer.
		memcpy(coloredPtr, (void*)coloredtype, (sizeof(ColoredVertexType) * m_vertexCount));

		// Unlock the vertex buffer.
		deviceContext->Unmap(m_vertexBuffer, 0);
		break;
	}
	// If it has changed then update the position it is being rendered to.
	m_previousPosX = positionX;
	m_previousPosY = positionY;

	m_previousColor = color;

	// Release the vertex array as it is no longer needed.
	delete[] coloredtype;
	coloredtype = 0;
	delete[] colortype;
	colortype = 0;

	return true;
}

bool TexturedRect::UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY) {
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
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
	vertices = new VertexType[m_vertexCount];
	if (!vertices) {
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
	vertices[0].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertices[2].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
	vertices[2].texture = DirectX::XMFLOAT2(0.0f, 1.0f);

	vertices[3].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
	vertices[3].texture = DirectX::XMFLOAT2(1.0f, 0.0f);

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	return true;
}


void TexturedRect::RenderBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	switch (m_shaderType) {
	case COLOR_TYPE:
		stride = sizeof(ColorVertexType);
		break;
	case TEXTURE_TYPE:
		stride = sizeof(VertexType);
		break;
	case COLOR_TEXTURE_TYPE:
		stride = sizeof(ColoredVertexType);
		break;
	}
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool TexturedRect::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename) {
	bool result;

	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture) {
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result) {
		return false;
	}
	return true;
}


void TexturedRect::ReleaseTexture() {
	// Release the texture object.
	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	return;
}