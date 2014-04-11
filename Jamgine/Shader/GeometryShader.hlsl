#include "Util.fx"

[maxvertexcount(6)]
void GS(point VS_OUTPUT input[1], inout TriangleStream <GS_OUTPUT> triangle_stream)
{
//	float alpha = 3.1415/2.0;
	float alpha = 0;
	float2x2 rotationmatrix =
	{
		cos(alpha), -sin(alpha),
		sin(alpha), cos(alpha)
	};

	GS_OUTPUT output;

	/*
	float2 topLeftUV	= TextureDeltaUVSize * input[0].texture_offset;
	float2 topRightUV	= topLeftUV + float2(TextureDeltaUVSize.x, 0.0f);
	float2 botLeftUV	= topLeftUV + float2(0.0f, TextureDeltaUVSize.y);
	float2 botRightUV	= botLeftUV + float2(TextureDeltaUVSize.x, 0.0f);
	*/

	float2 topLeftUV	= float2(0,0);
	float2 topRightUV	= float2(1,0);
	float2 botLeftUV	= float2(0,1);
	float2 botRightUV	= float2(1,1);

	
	float2 temp;
	if(input[0].flip == 1 || input[0].flip == 3) // Horizontal
	{
		temp = topLeftUV;
		topLeftUV = topRightUV;
		topRightUV = temp;

		temp = botLeftUV;
		botLeftUV = botRightUV;
		botRightUV = temp;
	}
	if(input[0].flip == 2 || input[0].flip == 3) // Vertícal
	{
		temp = topLeftUV;
		topLeftUV = botLeftUV;
		botLeftUV = temp;

		temp = topRightUV;
		topRightUV = botRightUV;
		botRightUV = temp;
	}
	
	
	float2 toOrigo = input[0].position.xy + input[0].origin;

	output.position		= float4(input[0].position, 1.0f) + float4(0.0f, input[0].offset.y, 0.0f, 0.0f);	// Top left mby Bot right
	output.position		= mul(output.position, ViewMatrix);						// Add camera offset 
	output.position.xy	= mul(output.position.xy - toOrigo, rotationmatrix);	// Move to origo and rotate
	output.position.xy	= output.position.xy + toOrigo;							// Move back
	output.uvCoord		= topLeftUV;
	triangle_stream.Append(output);
	
	output.position		= float4(input[0].position, 1.0f) + float4(input[0].offset.x, input[0].offset.y, 0.0f, 0.0f);	// Top right
	output.position		= mul(output.position, ViewMatrix);													// Add camera offset
	output.position.xy	= mul(output.position.xy - toOrigo, rotationmatrix);								// Move to origo and rotate
	output.position.xy	= output.position.xy + toOrigo;														// Move back
	output.uvCoord		= topRightUV;
	triangle_stream.Append(output);
	
	output.position		= float4(-1,-1,0, 1.0f);				
	output.position		= float4(input[0].position, 1.0f);	// Bot left
		output.position		= mul(output.position, ViewMatrix);													// Add camera offset
		output.position.xy	= mul(output.position.xy - toOrigo, rotationmatrix);								// Move to origo and rotate
		output.position.xy	= output.position.xy + toOrigo;														// Move back
	output.uvCoord		= botLeftUV;
	triangle_stream.Append(output);
	triangle_stream.RestartStrip();
	
	
	// Second triangle
	output.position		= float4(input[0].position, 1.0f) + float4(input[0].offset.x, input[0].offset.y, 0.0f, 0.0f);	// Top right
		output.position		= mul(output.position, ViewMatrix);													// Add camera offset
		output.position.xy	= mul(output.position.xy - toOrigo, rotationmatrix);								// Move to origo and rotate
		output.position.xy	= output.position.xy + toOrigo;														// Move back
	output.uvCoord		= topRightUV;
	triangle_stream.Append(output);
	
	output.position		= float4(input[0].position, 1.0f) + float4(input[0].offset.x, 0.0f, 0.0f, 0.0f);	// Bot right
		output.position		= mul(output.position, ViewMatrix);											// Add camera offset
		output.position.xy	= mul(output.position.xy - toOrigo, rotationmatrix);						// Move to origo and rotate
		output.position.xy	= output.position.xy + toOrigo;												// Move back
	output.uvCoord		= botRightUV;
	triangle_stream.Append(output);
	
	output.position		= float4(input[0].position, 1.0f);							// Bot left
		output.position		= mul(output.position, ViewMatrix);													// Add camera offset
		output.position.xy	= mul(output.position.xy - toOrigo, rotationmatrix);								// Move to origo and rotate
		output.position.xy	= output.position.xy + toOrigo;														// Move back
	output.uvCoord		= botLeftUV;
	triangle_stream.Append(output);
	

	triangle_stream.RestartStrip();
}