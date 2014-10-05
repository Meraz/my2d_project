#include "Util.fx"

VS_OUTPUT VS(VS_OUTPUT input)
{
	VS_OUTPUT output;
		
	output.position = input.position;//, view);
	//output.position = mul(output.position, proj);
	
	output.flip = input.flip;
	output.origin = input.origin;
	output.size = input.size;
	output.subTexturePosition = input.subTexturePosition;
	output.subTextureSize = input.subTextureSize;
	output.subTextureSize = input.subTextureSize;
	output.rotation = input.rotation;

	return output;
};