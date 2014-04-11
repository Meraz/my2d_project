#include "Util.fx"

float4 PS(GS_OUTPUT input) : SV_Target
{
	float4 color;
	color = Texture.Sample(Sampler, input.uvCoord) + float4(0.1,0,0,0);; 
//	color = float4(1,0,0,0);//Texture.Sample(Sampler, input.uvCoord);

	return color;
}