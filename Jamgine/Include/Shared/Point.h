#pragma once

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
	};
}