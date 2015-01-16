#pragma once

#include <math.h>
namespace Jamgine
{
	class JFloat4
	{
	public:
		// Very unusual exception for public member variables
		float x;
		float y;
		float z;
		float w;

		JFloat4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		JFloat4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

		virtual ~JFloat4()
		{
		}
	
		JFloat4& operator+(const JFloat4 &p_position)
		{
			x += p_position.x;
			y += p_position.y;
			z += p_position.z;
			w += p_position.w;
			return *this;
		}

		JFloat4& operator-(const JFloat4 &p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			z -= p_position.z;
			w -= p_position.w;
			return *this;
		}

		JFloat4& operator-=(JFloat4 &p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			z -= p_position.z;
			w -= p_position.w;
			return *this;
		}

		JFloat4& operator+=(JFloat4 &p_position)
		{
			x += p_position.x;
			y += p_position.y;
			z += p_position.z;
			w += p_position.w;
			return *this;
		}

		JFloat4& operator=(const JFloat4 &p_position)
		{
			x = p_position.x;
			y = p_position.y;
			z = p_position.z;
			w = p_position.w;
			return *this;
		}
		
		float Length()
		{
			return sqrt(x*x + y*y + z*z + w*w);
		}

		void Normalize()
		{
			if (x == 0.0f && y == 0.0f && y == 0.0f && w == 0.0f)
				return;
			float l_length;
			l_length = Length();
			x = x / l_length;
			y = y / l_length;
			z = z / l_length;
			w = w / l_length;
		}
		
		void Invert()
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;
		}
	};
}