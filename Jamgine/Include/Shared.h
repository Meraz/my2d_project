#pragma once

namespace GraphicalSystem
{
	enum GraphicalSystem
	{
		DIRECTX,
		OPENGL
	};
}

namespace ErrorMessage
{
	enum ErrorMessage
	{
		OK,
		FAILED
	};
}

namespace SpriteEffect
{
	enum SpriteEffect
	{
		FLIPHORIZONTALLY,	// Rotate 180 degrees about the Y axis before rendering.
		FLIPVERTICALLY,		// Rotate 180 degrees about the X axis before rendering.
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