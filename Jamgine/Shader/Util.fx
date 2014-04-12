Texture2D Texture;


cbuffer PerFrame : register(b0)
{
	float4x4 ViewMatrix;
};


cbuffer PerWindowChange :  register(b2)
{
	float ClientWidth;
	float ClientHeight;
	float2 padding2;
};

SamplerState Sampler : register(s0);


struct VS_OUTPUT
{
	float3 position				: POSITION;
	float2 origin				: ORIGIN;
	float2 offset				: OFFSET;
	float2 texture_offset		: TEXTURE_OFFSET;	// Index on subimage
	float  rotation				: ROTATION;
	float2 textureDeltaUVSize	: TEXTUREDELTA;	// 1 / number of subpictures
	uint   flip					: FLIP;
};

struct GS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uvCoord	: TEX_COORD;
};