#include <TestGame/Include/Entity/EnemyEntity.h>


EnemyEntity::EnemyEntity()
{

}

EnemyEntity::EnemyEntity(Position* playerPos)
{
	m_playerPos = playerPos;
	m_gravity = 0.05;
}
EnemyEntity::~EnemyEntity()
{
}

int EnemyEntity::getPlayerPos()
{
	return m_playerPos->x;
}

bool EnemyEntity::cornerCollision()
{	// might need change for rotation. object is a placeholder for other objects than this.
	bool intersection = false;
	//Position corners[4], otherCorners[4];

	//corners[0].x	= m_position.x + m_width;	// BR
	//corners[1].y	= m_position.y + m_height;	// TR
	//corners[1].x	= m_position.x + m_width;	// TR
	//corners[2].y	= m_position.y + m_height;	// TL
	//corners[3]		= m_position;				// BL

	//otherCorners[0].x	= object.x + object.width;	// BR
	//otherCorners[1].y	= object.y + object.height;	// TR
	//otherCorners[1].x	= object.x + object.width;	// TR
	//otherCorners[2].y	= object.y + object.height;	// TL
	//otherCorners[3]		= object;					// BL

	//if ((corners[0].x > otherCorners[2].x && corners[0].y > otherCorners[2].y) ||	// BR corner intersect
	//	(corners[1].x > otherCorners[3].x && corners[1].y > otherCorners[3].y) ||	// TR corner intersect
	//	(corners[2].x < otherCorners[0].x && corners[2].y > otherCorners[0].y) ||	// TL corner intersect
	//	(corners[3].x < otherCorners[1].x && corners[3].y > otherCorners[1].y))		// BL corner intersect
	//{
	//	intersection = true;
	//}
	
	return intersection;
}
bool EnemyEntity::horizontalCollision()
{
	bool intersection = false;

	//if (!onGround && m_position.y < object.y && m_position.y + m_height > object.y &&
	//	m_position.x + m_width > object.x || m_position.x < object.x + object.width)
	//{
	//	intersection = true;
	//}

	return intersection;
}
bool EnemyEntity::verticalCollision()
{
	bool intersection = false;

	//if (!onGround && m_position.x < object.x && m_position.x + m_width < object.x &&
	//	m_position.y + m_height > object.y || m_position.y < object.y + object.height)
	//{
	//	intersection = true;
	//	if (m_position.y < object.y + object.height)
	//		onGround = true;
	//}

	return intersection;
}
void EnemyEntity::Update()
{
	// Find out which direction to move in
	if (m_position.x > getPlayerPos())
		m_moveDir.x = -1;
	else
		m_moveDir.x = 1;

	if (m_moveDir.y > 0)
	{
		onGround = false;
	}

	if (cornerCollision() && onGround)
	{
		m_moveDir.y = 1;
	}


	m_position.x += m_moveDir.x;
	m_position.y += m_moveDir.y;

	m_moveDir.y -= m_gravity;
}