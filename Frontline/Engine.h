#include <d3d11.h>
#include <DirectXMath.h>
#ifndef __HYPERION_ENGINE_H__
#define __HYPERION_ENGINE_H__

//////////////////
// Typedefs
//////////////////

// To help avoid confusion in SceneClass::RenderX between different parameters.
typedef float H_SCALE;

typedef float H_ROT;

typedef int H_POS;

typedef DirectX::XMFLOAT4 H_COLORRGBA;

//////////////////
// Enums
//////////////////

//
//  Shader types
//  2D/3D: Dimension
//  Shader Resource Type
//  SHADERTYPE/SHADERMOD: Shader Type / Shader Modifier
//
enum H_SHADERTYPE {
	H_2D_COLOR_SHADERTYPE = 1,
	H_2D_TEXTURE_SHADERTYPE = 2,
	H_2D_COLOR_TEXTURE_SHADERTYPE = 4,
	H_2D_TRANSPARENCY_SHADERMOD = 8,
	H_2D_INSTANCE_SHADERMOD = 16,
	H_3D_LIGHT_SHADERTYPE = 32
};

//
//  Default screen resolution
//  Ideally updated per game
//
enum H_SCREENDIMENSIONS {
	H_SCREENWIDTH = 800,
	H_SCREENHEIGHT = 600
};

//////////////////
// Structs
//////////////////

//
//  Resource types
//  2D/3D: Dimension
//  Shader name
//  RESOURCETYPE/RESOURCEMOD: Resource Type / Resource Modifier
//
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