#pragma once
namespace Jamgine
{
	class JFloat3
	{
	public:
		// Very unusual exception for public member variables
		float x;
		float y;
		float z;

		JFloat3() : x(0.0f), y(0.0f), z(0.0f) {}
		JFloat3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}

		virtual ~JFloat3()
		{
		}
	
		JFloat3& operator+(const JFloat3 &p_position)
		{
			x += p_position.x;
			y += p_position.y;
			z += p_position.z;
			return *this;
		}

		JFloat3& operator-(const JFloat3 &p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			z -= p_position.z;
			return *this;
		}

		JFloat3& operator-=(JFloat3 &p_position)
		{
			x -= p_position.x;
			y -= p_position.y;
			z -= p_position.z;
			return *this;
		}

		JFloat3& operator+=(JFloat3 &p_position)
		{
			x += p_position.x;
			y += p_position.y;
			z += p_position.z;
			return *this;
		}

		JFloat3& operator=(const JFloat3 &p_position)
		{
			x = p_position.x;
			y = p_position.y;
			z = p_position.z;
			return *this;
		}
		
		float Length()
		{
			return sqrt(x*x + y*y + z*z);
		}

		void Normalize()
		{
			if (x == 0.0f && y == 0.0f && y == 0.0f)
				return;
			float l_length;
			l_length = Length();
			x = x / l_length;
			y = y / l_length;
			z = z / l_length;
		}
		
		void Invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}
	};
}