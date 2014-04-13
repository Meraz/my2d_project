#include "Util.fx"

float4 PS(GS_OUTPUT input) : SV_Target
{
	float4 color;
	color = Texture.Sample(Sampler, input.uvCoord); 

	return color;
}