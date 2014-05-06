#include "Util.fx"


VS_OUTPUT VS(VS_OUTPUT input)
{
	VS_OUTPUT output;

	output.position.x	= input.position.x / (ClientWidth/2.0f)  -1;
	output.position.y	= input.position.y / (ClientHeight/2.0f) -1;
	output.position.z	= input.position.z;

	output.origin.x	= input.origin.x / (ClientWidth / 2.0f);
	output.origin.y	= input.origin.y / (ClientHeight / 2.0f);

	output.offset.x	= input.offset.x / (ClientWidth / 2.0f);
	output.offset.y	= input.offset.y / (ClientHeight / 2.0f);
		
	output.texture_offset = input.texture_offset;
	output.rotation = input.rotation;

	output.flip = input.flip;
	output.textureDeltaUVSize = input.textureDeltaUVSize;

	return output;
};