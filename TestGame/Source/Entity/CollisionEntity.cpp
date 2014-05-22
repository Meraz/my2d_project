#include <TestGame/Include/Entity/CollisionEntity.h>


CollisionEntity::CollisionEntity()
	:  m_velocity(),m_acceleration(0.0f)
{
	m_entity = ENTITY::COLLISION;
}

CollisionEntity::~CollisionEntity()
{
}

void CollisionEntity::Update(double deltaTime)
{	
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
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