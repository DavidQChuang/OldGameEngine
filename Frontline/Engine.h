#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
enum ShaderType {
	COLOR_TYPE = 1,
	TEXTURE_TYPE = 2,
	COLOR_TEXTURE_TYPE = 4,
	TRANSPARENCY = 8,
	INSTANCE = 16,
	LIGHT_TYPE = 32
};

