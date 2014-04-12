#include <TestGame/Include/Entity/PlayerEntity.h>


PlayerEntity::PlayerEntity()
{
}


PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::moveLeft()
{
	if (!collisionWall)
		m_moveDir.x = -1;
	else
		m_moveDir.x = 0;
}

void PlayerEntity::moveRight()
{
	if (!collisionWall)
		m_moveDir.x = 1;
	else
		m_moveDir.x = 0;
}

void PlayerEntity::jump()
{
	hasJumped = true;
	m_moveDir.y = 20;
}

void PlayerEntity::Update()
{
	if (hasJumped && !onGround)
	{
		m_moveDir.y--;

		if (m_position.y - 1 == groundheight)
		{
			m_moveDir.y = 0;
			onGround = true;
		}
	}

	m_position += m_moveDir;
}