#pragma once

namespace Jamgine
{
	struct Rectangle
	{
		Vector2 position; // Bot left
		float width;
		float height;

		Rectangle()
			: position(), width(0.0f), height(0.0f)
		{
		
		};

		Rectangle(Vector2 _position, float _width, float _height)
			: position(_position), width(_width), height(_height)
		{
		
		};

		Rectangle(float _x, float _y, float _width, float _height): position(_x, _y), width(_width), height(_height)
		{
		
		};

		Rectangle(const Rectangle& _rectangle)
			: position(_rectangle.position), width(_rectangle.width), height(_rectangle.height)
		{
		
		};

		bool Intersect(Rectangle r2)
		{
			Rectangle r1 = *this;

			if((r1.position.x				< r2.position.x + r2.width  ||  // Intersect on leftside of 1
				r1.position.x + r1.width	> r2.position.x)				// Intersect on rightside of 1
				&&	
			   (r1.position.y				< r2.position.y + r2.height ||	// Intersect on botside of 1
				r1.position.y + r1.height	> r2.position.y))				// Intersect on topside of 1
			{
				return true;
			}
			return false;
		}
		
	};
}