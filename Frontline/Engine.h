#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

/////////////////
// Constants
//////////////////

//------------------------------------------------------------------------------
//  Default screen resolution
//  Ideally updated per game
//
#define H_SCREENWIDTH 800
#define H_SCREENHEIGHT 600

/////////////////
// Typedefs
//////////////////

typedef float H_SCALE;
typedef float H_ROT;
typedef int H_POS;
typedef int H_DIMENSION;
typedef DirectX::XMFLOAT4 H_COLORRGBA;

typedef DirectX::XMMATRIX H_WORLDMATRIX;
typedef DirectX::XMMATRIX H_VIEWMATRIX;
typedef DirectX::XMMATRIX H_PROJECTIONMATRIX;
typedef DirectX::XMMATRIX H_ORTHOMATRIX;

typedef struct {
	float last;
	float curr;
} H_TIME;

/////////////////
// Enums
//////////////////

//------------------------------------------------------------------------------
//  Shader types
//  2D/3D: Dimension
//  Shader Resource Type
//  SHADERTYPE/SHADERMOD: Shader Type / Shader Modifier
//
enum H_2DSHADERTYPE {
	H_2D_COLOR_SHADERTYPE = 1,
	H_2D_TEXTURE_SHADERTYPE = 2,
	H_2D_COLOR_TEXTURE_SHADERTYPE = 4,
	H_2D_TRANSPARENCY_SHADERMOD = 8,
	H_2D_INSTANCE_SHADERMOD = 16
};

enum H_3DSHADERTYPE {
	H_3D_LIGHT_SHADERTYPE = 1
};

/////////////////
// Structs
//////////////////

//------------------------------------------------------------------------------
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

/////////////////
// Functions
/////////////////

inline float seconds(float m) { return m * 1000; }
