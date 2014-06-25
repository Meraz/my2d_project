#pragma once

#include <Jamgine/Include/Shared/Point.h>

namespace Jamgine
{
struct Rectangle
{
	Point position; // Bot left
	float width;
	float height;

	Rectangle()
		: position(), width(0.0f), height(0.0f)
	{
	
	};

	Rectangle(Point _position, float _width, float _height)
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

	bool static LeftIntersect(Rectangle A, Rectangle B)
	{
		if( A.position.x			< B.position.x + B.width &&
			A.position.x + A.width	> B.position.x + B.width)
			return true;
		return false;
	}

	bool static RightIntersect(Rectangle A, Rectangle B)
	{
		if( A.position.x + A.width	> B.position.x &&
			A.position.x			< B.position.x)
			return true;
		return false;
	}

	bool static TopIntersect(Rectangle A, Rectangle B)
	{
		if( A.position.y + A.height	> B.position.y &&
			A.position.y			< B.position.y)
			return true;
		return false;
	}

	bool static BotIntersect(Rectangle A, Rectangle B)
	{
		if( A.position.y			< B.position.y + B.height &&
			A.position.y + A.height	> B.position.y + B.height)
			return true;
		return false;
	}

	bool Intersect(Rectangle r2)
	{
		Rectangle r1 = *this;
		if((LeftIntersect(r1, r2) || RightIntersect(r1, r2))  && (BotIntersect(r1, r2) ||TopIntersect(r1, r2))) // Edge intersect
		{
			return true;
		}
		
		if
		(
			(r1.position.x <= r2.position.x && r1.position.x + r1.width >= r2.position.x + r2.width) // r2 is inside of r1 
			&&
			(r1.position.y <= r2.position.y && r1.position.y + r1.height >= r2.position.y + r2.height)
		)		
		{
			return true;
		}
		if
		(
			(r2.position.x <= r1.position.x && r2.position.x + r2.width >= r1.position.x + r1.width) // r1 is inside of r2
			&&
			(r2.position.y <= r1.position.y && r2.position.y + r2.height >= r1.position.y + r1.height)
		)		
		{
			return true;
		}

		return false;
	}	
};
}