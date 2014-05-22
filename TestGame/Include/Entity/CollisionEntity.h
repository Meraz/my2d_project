#pragma once
#include <TestGame/Include/Entity/RenderEntity.h>
class CollisionEntity :	public RenderEntity
{
public:
	CollisionEntity();
	~CollisionEntity();

	virtual void Update(double p_deltaTime);

	Point GetPosition();
	float GetWidth();
	float GetHeight();

	Jamgine::Rectangle GetRectangle() {return m_rectangle;}

protected:
	Point m_velocity;
	float m_acceleration;

};

