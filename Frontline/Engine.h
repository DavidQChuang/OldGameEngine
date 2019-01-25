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

#define K_A 65
#define K_B 66
#define K_C 67
#define K_D 68
#define K_E 69
#define K_F 70
#define K_G 71
#define K_H 72
#define K_I 73
#define K_J 74
#define K_K 75
#define K_L 76
#define K_M 77
#define K_N 78
#define K_O 79
#define K_P 80
#define K_Q 81
#define K_R 82
#define K_S 83
#define K_T 84
#define K_U 85
#define K_V 86
#define K_W 87
#define K_X 88
#define K_Y 89
#define K_Z 90

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

typedef float milliseconds;
typedef float steps;
typedef struct {
	float start;
	float curr;
	float last;
} H_TIME;

struct H_TIMESTEP {
	H_TIMESTEP(milliseconds steps) {
		step = steps;
	};
	milliseconds step;
	milliseconds delta;
	// Amount of steps that could be taken within the input time.
	inline steps timesteps(milliseconds time) {
		return time / step;
	}; 
	// Amount of time left in milliseconds if the largest integer amount of steps was taken within the input time.
	inline milliseconds remainingTime(milliseconds time) {
		return time - (floor(timesteps(time))*step);
	};
	// Amount of time left in fraction of a steps if the largest integer amount of steps was taken within the input time.
	inline steps remainingSteps(milliseconds time) {
		return (time / step) - floor(timesteps(time));
	}
};

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

// For instances that inherit the parent's properties or vertices of a parent that never is inherited.
struct H_2D_POSITION_RESOURCETYPE {
	DirectX::XMFLOAT3 position;
};

//
struct H_2D_COLOR_RESOURCETYPE {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

//
struct H_2D_TEXTURE_RESOURCETYPE {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texture;
};

//
struct H_2D_COLOR_TEXTURE_RESOURCETYPE {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texture;
	DirectX::XMFLOAT4 color;
};

//
struct H_3D_LIGHT_RESOURCETYPE {
};

/////////////////
// Functions
/////////////////

inline float seconds(float m) { return m * 1000; }


constexpr milliseconds operator "" _ms(long double x) {
	return x;
}

constexpr milliseconds operator "" _s(long double x) {
	return x * 1000;
}

// 1/60 seconds = 1 frame
constexpr milliseconds operator "" _f(long double x) {
	return x * 1000 / 60;
}
