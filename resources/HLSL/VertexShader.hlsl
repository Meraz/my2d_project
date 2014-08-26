#include "Util.fx"


cbuffer PerWindowChange :  register(b0)
{
	float ClientWidth;
	float ClientHeight;
	float2 padding2;
};

cbuffer CameraMatrix : register(b1)
{
	float4x4 Camera;
};

VS_OUTPUT VS(VS_OUTPUT input)
{
	VS_OUTPUT output;

	output.position.x	= input.position.x / (ClientWidth/2.0f) -1;
	output.position.y	= input.position.y / (ClientHeight/2.0f) -1;
	output.position.z	= input.position.z;
		
	output.position = mul(input.position, Camera);

	output.origin.x	= input.origin.x / (ClientWidth/2.0f);
	output.origin.y	= input.origin.y / (ClientHeight/2.0f);

	output.size.x = input.size.x / (ClientWidth / 2.0f);
	output.size.y = input.size.y / (ClientHeight / 2.0f);
		
	output.subTexturePosition = input.subTexturePosition;
	output.subTextureSize = input.subTextureSize;

	output.rotation = input.rotation * padding2.x;
	output.flip = input.flip * padding2.y;

	return output;
};