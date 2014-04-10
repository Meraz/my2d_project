#pragma once

#include <Jamgine/Include/ErrorMessage.h>

namespace Jamgine
{
	#define STANDARD_SPRITE_DEPTH 0.5f
	
	enum class GraphicalSystem
	{
		DIRECTX,
		OPENGL
	};

	enum class SpriteEffect
	{
		FLIP_HORIZONTALLY,	// Rotate 180 degrees about the Y axis before rendering.
		FLIP_VERTICALLY,		// Rotate 180 degrees about the X axis before rendering.
		NONE				// No rotations specified.
	};

	struct Position
	{
		float x;
		float y;

		Position& operator+(Position p_position)
		{
			x += p_position.x;
			y += p_position.y;
			return *this;
		}
	};

}