Texture2D Texture;

cbuffer PerFrame : register(b0)
{
	float4x4 ViewMatrix;
};

cbuffer PerTexture : register(b1)
{
	float2 TextureDeltaUVSize;
	float2 padding;
};

SamplerState Sampler : register(s0);


struct VS_OUTPUT
{
	float3 position			: POSITION;
	float2 origin			: ORIGIN;
	float2 offset			: OFFSET;
	float2 texture_offset	: TEXTURE_OFFSET;	// 1 / number of subpictures
	float  rotation			: ROTATION;
};

struct GS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uvCoord	: TEX_COORD;
};