#include "TextureClass.h"
#include <sstream>
TextureClass::TextureClass() {
	m_targaData = 0;
	m_texture = 0;
	m_textureView = 0;
}

TextureClass::TextureClass(const TextureClass& other) {
}

TextureClass::~TextureClass() {
}

bool TextureClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename) {
	bool result;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	//So first we call the TextureClass::LoadTarga function to load the targa file into the m_targaData array.This function will also pass us back the height and width of the texture.

	// Load the targa image data into memory.
	result = LoadTarga(filename, height, width);
	if (!result) {
		return false;
	}
	//Next we need to setup our description of the DirectX texture that we will load the targa data into.We use the height and width from the targa image data, and set the format to be a 32 bit RGBA texture.We set the SampleDesc to default.Then we set the Usage to D3D11_USAGE_DEFAULT which is the better performing memory, which we will also explain a bit more about down below.And finally we set the MipLevels, BindFlags, and MiscFlags to the settings required for Mipmaped textures.Once the description is complete we call CreateTexture2D to create an empty texture for us.The next step will be to copy the targa data into that empty texture.

	// Setup the description of the texture.
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// Create the empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
	if (FAILED(hResult)) {
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (width * 4) * sizeof(unsigned char);
	//Here we use UpdateSubresource to actually do the copying of the targa data array into the DirectX texture.If you will remember from the previous tutorial we used Map and Unmap to copy our matrices in the ColorRect into the matrix constant buffer, and we could have done the same here with our texture data.And in fact using Map and Unmap is generally a lot quicker than using UpdateSubresource, however both loading methods have specific purposes and you need to choose correctly which one to use for performance reasons.The recommendation is that you use Map and Unmap for data that is going to be reloaded each frame or on a very regular basis.And you should use UpdateSubresource for something that will be loaded once or that gets loaded rarely during loading sequences.The reason being is that UpdateSubresource puts the data into higher speed memory that gets cache retention preference since it knows you aren't going to remove or reload it anytime soon. We let DirectX also know by using D3D11_USAGE_DEFAULT when we are going to load using UpdateSubresource. And Map and Unmap will put the data into memory locations that will not be cached as DirectX is expecting that data to be overwritten shortly. And that is why we use D3D11_USAGE_DYNAMIC to notify DirectX that this type of data is transient.

	// Copy the targa image data into the texture.
	deviceContext->UpdateSubresource(m_texture, 0, NULL, m_targaData, rowPitch, 0);
	//After the texture is loaded we create a shader resource view which allows us to have a pointer to set the texture in shaders.In the description we also set two important Mipmap variables which will give us the full range of Mipmap levels for high quality texture rendering at any distance.Once the shader resource view is created we call GenerateMips and it creates the Mipmaps for us, however if you want you can load your own Mipmap levels in manually if you are looking for even better quality.

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;
	// Create the shader resource view for the texture.
	hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
	if (FAILED(hResult)) {
		return false;
	}

	// Generate mipmaps for this texture.
	deviceContext->GenerateMips(m_textureView);

	// Release the targa image data now that the image data has been loaded into the texture.
	delete[] m_targaData;
	m_targaData = 0;

	return true;
}

void TextureClass::Shutdown() {
	// Release the texture view resource.
	if (m_textureView) {
		m_textureView->Release();
		m_textureView = 0;
	}

	// Release the texture.
	if (m_texture) {
		m_texture->Release();
		m_texture = 0;
	}

	// Release the targa data.
	if (m_targaData) {
		delete[] m_targaData;
		m_targaData = 0;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture() {
	return m_textureView;
}

bool TextureClass::LoadTarga(char* filename, int& height, int& width) {
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TargaHeader targaFileHeader;
	SpriteHeader spriteFileHeader;
	unsigned char* targaImage;
	unsigned char* spriteInformation;


	// Open the targa file for reading in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0) {
		return false;
	}

	// Read in the file header.
	count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1) {
		return false;
	}

	//data = targaFileHeader.data1;
	// Get the important information from the header.
	height = (int)targaFileHeader.height;
	width = (int)targaFileHeader.width;
	bpp = (int)targaFileHeader.bpp;


	// Check that it is 32 bit and not 24 bit.
	if (bpp != 32) {
		return false;
	}

	// Calculate the size of the 32 bit image data.
	imageSize = width * height * 4;

	// Allocate memory for the targa image data.
	targaImage = new unsigned char[imageSize];
	if (!targaImage) {
		return false;
	}

	// Read in the targa image data.
	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize) {
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if (error != 0) {
		return false;
	}

	// Allocate memory for the targa destination data.
	m_targaData = new unsigned char[imageSize];
	if (!m_targaData) {
		return false;
	}

	// Bytes 0-3: Sprite dimensions

	// Initialize the index into the targa destination data array.
	index = 0;

	// Initialize the index into the targa image data.
	k = (width * height * 4) - (width * 4);
	//2093056
	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
	k = 0;
	for (j = 0; j < height; j++) {
		//height = 512
		for (i = 0; i < width; i++) {
			//height*width = 524288
			m_targaData[index + 0] = targaImage[k + 2];  // Red.
			m_targaData[index + 1] = targaImage[k + 1];  // Green.
			m_targaData[index + 2] = targaImage[k + 0];  // Blue
			m_targaData[index + 3] = targaImage[k + 3];  // Alpha

															// Increment the indexes into the targa data.
															//height*width = 524288 * 4 = 2097152
			k += 4;
			index += 4;
		}
	}
	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = 0;

	return true;
}
