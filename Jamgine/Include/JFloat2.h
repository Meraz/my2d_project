#pragma once

#include <math.h>

namespace Jamgine
{
	struct JFloat2
	{
		float x;
		float y;

		JFloat2() : x(0), y(0) {}
		JFloat2(float _x, float _y) : x(_x), y(_y) {}
		JFloat2(const JFloat2& _vector) : x(_vector.x), y(_vector.y) {};

		JFloat2& operator+(JFloat2 p_position)
		{
			x += p_position.x;
			y += p_position.y;
			return *this;
		}

		JFloat2& operator-(JFloat2 p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			return *this;
		}

		JFloat2& operator-=(JFloat2 p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			return *this;
		}

		JFloat2& operator+=(JFloat2 p_position)
		{
			x += p_position.x;
			y += p_position.y;
			return *this;
		}

		JFloat2& operator=(const JFloat2& p_position)
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