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
	void SetVelocity(Point p_velocity);
		bool OutsideBounds(float p_left, float p_right, float p_bot, float p_top);

protected:
	Point m_velocity;
	float m_acceleration;

};

