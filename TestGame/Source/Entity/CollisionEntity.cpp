#include <TestGame/Include/Entity/CollisionEntity.h>


CollisionEntity::CollisionEntity()
{
	m_entity = ENTITY::COLLISION;
}

CollisionEntity::~CollisionEntity()
{
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

void CollisionEntity::Render()
{
	if (isWall)
		m_engine->Render(m_position, m_width, m_height, m_origin, m_currentSubImage, m_texture, m_spriteEffect, m_depth, m_rotation, m_hasTransparent, m_amountOfSubImages);
}
