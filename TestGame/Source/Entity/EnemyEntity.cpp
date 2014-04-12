#include <TestGame/Include/Entity/EnemyEntity.h>


EnemyEntity::EnemyEntity()
{
}

EnemyEntity::EnemyEntity(Position* playerPos)
{
	m_playerPos = playerPos;
}
EnemyEntity::~EnemyEntity()
{
}

int EnemyEntity::getPlayerPos()
{
	return m_playerPos->x;
}
void EnemyEntity::jump()
{
	
}

void EnemyEntity::collisionWall()
{
	if ()
	{
		//implement later
	}
}
void EnemyEntity::Update()
{
	// Find out which direction to move in
	if (m_position.x > getPlayerPos())
		m_moveDir.x = -1;
	else
		m_moveDir.x = 1;

	if (collisionWall || !onGround)
	{
		if (!hasJumped)
		{
			m_moveDir.y = 25; // burst of speed in the beginning, then declining
			hasJumped = true;
		}

		if (m_position.y-1 == groundheight)
		{
			m_moveDir.y = 0;
			onGround = true;
		}
		m_moveDir.y--;
	}

	



	m_position.x += m_moveDir.x;
	m_position.y += (m_moveDir.y/4); // fix number after testing
}