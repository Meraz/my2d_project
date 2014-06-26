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
	float2 size					: SIZE;
	float2 subTexturePosition	: SUB_TEX_POS;	// If not entire texture is to be used. Relative position on the texture from bot left corner
	float2 subTextureSize		: SUB_TEX_SIZE;	// width and heigth on above
	float  rotation				: ROTATION;	
	uint   flip					: FLIP;
};

struct GS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uvCoord	: TEX_COORD;
};