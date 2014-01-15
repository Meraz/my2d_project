#include <Jamgine\Include\Rectangle.h>


namespace Jamgine
{
	Rectangle::Rectangle()
	{
		
	}

	Rectangle::Rectangle(Position l_position, float l_width, float l_height)
	{
		m_position = l_position;
		m_width = l_width;
		m_height = l_height;
	}
		
	Rectangle::~Rectangle()
	{
		
	}
}