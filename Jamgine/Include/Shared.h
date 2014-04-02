#pragma once

#include <Jamgine/Include/ErrorMessage.h>

namespace Jamgine
{
	namespace GraphicalSystem
	{
		enum GraphicalSystem
		{
			DIRECTX,
			OPENGL
		};
	}

	namespace SpriteEffect
	{
		enum SpriteEffect
		{
			FLIP_HORIZONTALLY,	// Rotate 180 degrees about the Y axis before rendering.
			FLIP_VERTICALLY,		// Rotate 180 degrees about the X axis before rendering.
			NONE				// No rotations specified.
		};
	}

	struct Position
	{
		float X;
		float Y;

		Position& operator+(Position p_position)
		{
			X += p_position.X;
			Y += p_position.Y;
			return *this;
		}
	};

}