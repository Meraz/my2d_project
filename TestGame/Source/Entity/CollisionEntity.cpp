#include <TestGame/Include/Entity/CollisionEntity.h>


CollisionEntity::CollisionEntity()
	:  m_velocity(),m_acceleration(0.0f)
{
	m_entity = ENTITY::COLLISION;

}

CollisionEntity::~CollisionEntity()
{
}

void CollisionEntity::Update(double p_deltaTime)
{	
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
	RenderEntity::Update(p_deltaTime);
}

Point CollisionEntity::GetPosition()
{
	return m_position;
}

float CollisionEntity::GetWidth()
{
	return m_width;
}

float CollisionEntity::GetHeight()
{
	return m_height;
}

void CollisionEntity::SetVelocity(Point p_velocity)
{
	m_velocity = p_velocity;
}

bool CollisionEntity::OutsideBounds(float p_left, float p_right, float p_bot, float p_top)
{
	Jamgine::Rectangle a = Jamgine::Rectangle(p_left, p_bot, abs(p_left-p_right), abs(p_top-p_bot));

	if(m_rectangle.Intersect(a) == false)
		return true;
	return false;
}
