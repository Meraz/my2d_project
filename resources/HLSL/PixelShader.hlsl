#include "Util.fx"

float4 PS(GS_OUTPUT input) : SV_Target
{
	float4 color;
	color = Texture.Sample(Sampler, input.uvCoord);
	if(color.w == 0.0f)
		return float4(0,0,0,0);

	return color;
}