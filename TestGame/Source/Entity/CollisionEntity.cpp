#include <TestGame/Include/Entity/CollisionEntity.h>


CollisionEntity::CollisionEntity()
{
	m_entity = ENTITY::COLLISION;
}

CollisionEntity::~CollisionEntity()
{
}

Position CollisionEntity::GetPosition()
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
