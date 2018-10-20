#include <d3d11.h>
#include <DirectXMath.h>
#ifndef __HYPERION_ENGINE_H__
#define __HYPERION_ENGINE_H__
//  Shader types
//  2D/3D: Dimension
//  Shader Resource Type
//  SHADERTYPE/SHADERMOD: Shader Type / Shader Modifier
enum H_SHADERTYPE {
	H_2D_COLOR_SHADERTYPE = 1,
	H_2D_TEXTURE_SHADERTYPE = 2,
	H_2D_COLOR_TEXTURE_SHADERTYPE = 4,
	H_2D_TRANSPARENCY_SHADERMOD = 8,
	H_2D_INSTANCE_SHADERMOD = 16,
	H_3D_LIGHT_SHADERTYPE = 32
};

//  Resource types
//  2D/3D: Dimension
//  Shader name
//  RTYPE/RMOD: Resource Type / Resource Modifier

struct H_2D_COLOR_RESOURCETYPE {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

struct H_2D_TEXTURE_RESOURCETYPE {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texture;

};

struct H_2D_COLOR_TEXTURE_RESOURCETYPE {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texture;
	DirectX::XMFLOAT4 color;
};

struct H_3D_LIGHT_RESOURCETYPE {

};
#endif