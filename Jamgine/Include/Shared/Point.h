#pragma once

#include <math.h>

namespace Jamgine
{
	struct Point
	{
		float x;
		float y;

		Point() : x(0), y(0) {}
		Point(float _x, float _y) : x(_x), y(_y) {}
		Point(const Point& _vector) : x(_vector.x), y(_vector.y) {};

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

		float Length()
		{
			return sqrt(x*x + y*y);
		}

		void Normalize()
		{
			if(x == 0.0f && y == 0.0f)
				return;
			float l_length;
			l_length = Length();
			x = x / l_length;
			y = y / l_length;
		}
		void Invert()
		{
			x = -x;
			y = -y;
		}
	};
}