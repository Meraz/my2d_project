#pragma once
#include <TestGame/Include/Entity/RenderEntity.h>
class CollisionEntity :	public RenderEntity
{
public:
	CollisionEntity();
	~CollisionEntity();
	Point GetPosition();
	float GetWidth();
	float GetHeight();

	Jamgine::Rectangle GetRectangle() {return m_rectangle;}
};

