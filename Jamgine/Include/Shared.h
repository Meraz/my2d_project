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
		FLIP_NONE,
		FLIP_HORIZONTALLY,	
		FLIP_VERTICALLY,
		FLIP_BOTH		
	};

	struct Point
	{
		float x;
		float y;

		Point() : x(0), y(0){}
		Point(float _x, float _y) : x(_x), y(_y){}

		Point& operator+(Point p_position)
		{
			x += p_position.x;
			y += p_position.y;
			return *this;
		}

		Point& operator-(Point p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			return *this;
		}

		Point& operator-=(Point p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			return *this;
		}

		Point& operator+=(Point p_position)
		{
			x += p_position.x;
			y += p_position.y;
			return *this;
		}

		Point& operator=(const Point& p_position)
		{
			x = p_position.x;
			y = p_position.y;
			return *this;
		}
	};

}