#include "InstancedTexturedRect.h"
#include <sstream>
InstancedTexturedRect::InstancedTexturedRect(int max) {
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
	m_Texture = 0;
	m_instanceCount = 0;
	m_Instances = new InstanceType[max];
	m_instanceCountMax = max;
	m_Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}


InstancedTexturedRect::InstancedTexturedRect(const InstancedTexturedRect& other) {
}


InstancedTexturedRect::~InstancedTexturedRect() {
}


bool InstancedTexturedRect::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	char* textureFilename,
	int screenWidth, int screenHeight, int imageWidth, int imageHeight) {
	bool result;

	m_PreviousColor = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// Store the screen size.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the size in pixels that this bitmap should be rendered at.
	m_imageWidth = imageWidth;
	m_imageHeight = imageHeight;

	m_originalImageWidth = imageWidth;
	m_originalImageHeight = imageHeight;

	/*// Initialize the previous rendering position to negative one.
	m_previousPosX = -1;
	m_previousPosY = -1;*/

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


void InstancedTexturedRect::Shutdown() {
	// Release the bitmap texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

void InstancedTexturedRect::AddInstance(int x, int y) {
	m_Instances[m_instanceCount].position = DirectX::XMFLOAT3(x, y, 0.f);
	m_Instances[m_instanceCount].color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	m_instanceCount++;
}

bool InstancedTexturedRect::Render(ID3D11DeviceContext* deviceContext) {
	bool result;
	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	result = UpdateBuffers(deviceContext);
	if (!result) return false;

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return true;
}

bool InstancedTexturedRect::Render(ID3D11DeviceContext* deviceContext, int x, int y) {
	bool result;
	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	result = UpdateBuffers(deviceContext);
	if (!result) return false;

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return true;
}

int InstancedTexturedRect::GetIndexCount() {
	return m_indexCount;
}


ID3D11ShaderResourceView* InstancedTexturedRect::GetTexture() {
	return m_Texture->GetTexture();
}


bool InstancedTexturedRect::InitializeBuffers(ID3D11Device* device) {
	VertexType* vertices;
	InstanceType* instances;
	unsigned long* indices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, instanceData;
	HRESULT result;
	int i;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 6;

	// Set the number of indices in the index array.
	m_indexCount = m_vertexCount;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices) {
		return false;
	}

	// Load the vertex array with data.
	// First triangle.
	vertices[0].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

	vertices[1].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertices[2].texture = DirectX::XMFLOAT2(0.0f, 1.0f);

	// Second triangle.
	vertices[3].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

	vertices[4].texture = DirectX::XMFLOAT2(1.0f, 0.0f);

	vertices[5].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices) {
		return false;
	}

	// Load the index array with data.
	for (i = 0; i<m_indexCount; i++) {
		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result)) {
		return false;
	}

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
	if (FAILED(result))	return false;

	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCountMax;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result)) return false;

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] instances;
	instances = 0;

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void InstancedTexturedRect::Resize() {
	m_imageWidth = m_originalImageWidth;
	m_imageHeight = m_originalImageHeight;
}

void InstancedTexturedRect::Resize(int width, int height) {
	m_imageWidth = width;
	m_imageHeight = height;
}

void InstancedTexturedRect::ShutdownBuffers() {
	// Release the instance buffer.
	if (m_instanceBuffer) {
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}
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

bool InstancedTexturedRect::UpdateBuffers(ID3D11DeviceContext* deviceContext) {
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	InstanceType* instancePtr;
	HRESULT result;
	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	/*

	if ((positionX == m_previousPosX) && (positionY == m_previousPosY)) {
	return true;
	}
	// If it has changed then update the position it is being rendered to.
	m_previousPosX = positionX;
	m_previousPosY = positionY;*/

	// Release the vertex array as it is no longer needed.

	/*if (m_Color.x == m_PreviousColor.x && m_Color.y == m_PreviousColor.y && m_Color.z == m_PreviousColor.z && m_Color.w == m_PreviousColor.w) {
		return true;
	}*/
	vertices = new VertexType[m_vertexCount];
	if (!vertices) return false;

	m_PreviousColor = m_Color;
	// Load the vertex array with data.
	// First triangle.
	vertices[0].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

	vertices[1].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertices[2].texture = DirectX::XMFLOAT2(0.0f, 1.0f);

	// Second triangle.
	vertices[3].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

	vertices[4].texture = DirectX::XMFLOAT2(1.0f, 0.0f);

	vertices[5].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) return false;

	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);

	result = deviceContext->Map(m_instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) return false;

	instancePtr = (InstanceType*)mappedResource.pData;

	memcpy(instancePtr, (void*)m_Instances, (sizeof(InstanceType) * m_instanceCountMax));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_instanceBuffer, 0);

	delete[] vertices;
	vertices = 0;

	return true;
}

void InstancedTexturedRect::RenderBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set vertex buffer stride and offset.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(InstanceType);
	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_instanceCount = 0;
	m_Instances = new InstanceType[m_instanceCountMax];
	return;
}


bool InstancedTexturedRect::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename) {
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


void InstancedTexturedRect::ReleaseTexture() {
	// Release the texture object.
	if (m_Texture) {
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	return;
}

int InstancedTexturedRect::GetInstanceCount() {
	return m_instanceCount;
}