Texture2D Texture;

SamplerState Sampler : register(s0);


struct VS_OUTPUT
{
	float3 position				: POSITION;
	uint   flip					: FLIP;
	float2 origin				: ORIGIN;
	float2 size					: SIZE;
	float2 subTexturePosition	: SUB_TEX_POS;	// If not entire texture is to be used. Relative position on the texture from bot left corner
	float2 subTextureSize		: SUB_TEX_SIZE;	// width and heigth on above
	float  rotation				: ROTATION;	
};

struct GS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uvCoord	: TEX_COORD;
};