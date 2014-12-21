#pragma once
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

	};
}