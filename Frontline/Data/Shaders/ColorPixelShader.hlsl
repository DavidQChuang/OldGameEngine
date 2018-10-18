Texture2D shaderTexture;
SamplerState SampleType;

struct PixelInputType {
	float4 position : SV_POSITION;
	nointerpolation float4 color : COLOR;
};

float4 ColorPixelShader(PixelInputType input) : SV_TARGET {
	return input.color;
}