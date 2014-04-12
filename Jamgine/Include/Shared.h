#pragma once

#include <Jamgine/Include/ErrorMessage.h>

namespace Jamgine
{
	#define STANDARD_SPRITE_DEPTH -50.5f
	
	enum class GraphicalSystem
	{
		DIRECTX,
		OPENGL
	};

	enum class SpriteEffect
	{
		FLIP_NONE,
		FLIP_HORIZONTALLY,	
		FLIP_VERTICALLY,
		FLIP_BOTH		
	};

	struct Position
	{
		float x;
		float y;

		Position() : x(0), y(0){}
		Position(float _x, float _y) : x(_x), y(_y){}

		Position& operator+(Position p_position)
		{
			x += p_position.x;
			y += p_position.y;
			return *this;
		}

		Position& operator-(Position p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			return *this;
		}

		Position& operator-=(Position p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			return *this;
		}

		Position& operator+=(Position p_position)
		{
			x += p_position.x;
			y += p_position.y;
			return *this;
		}

		Position& operator=(const Position& p_position)
		{
			x = p_position.x;
			y = p_position.y;
			return *this;
		}
	};

}