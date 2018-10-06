cbuffer MatrixBuffer {
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType {
	float4 color : COLOR0;
	float2 tex : TEXCOORD0;
	float3 instancePosition : TEXCOORD1;
	float4 instanceColor : COLOR1;
};

struct PixelInputType {
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR0;
	float4 instanceColor : COLOR1;
};

PixelInputType TextureVertexShader(VertexInputType input) {
	PixelInputType output;
	// Change the position vector to be 4 units for proper matrix calculations.
	input.instancePosition.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.instancePosition, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	output.color = input.color;
	output.instanceColor = input.instanceColor;

	return output;
}