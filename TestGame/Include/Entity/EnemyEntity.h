#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <TestGame/Include/Entity/AnimationEntity.h>

class EnemyEntity : public AnimationEntity
{
public:
	EnemyEntity();
	EnemyEntity(Position* playerPos);
	virtual ~EnemyEntity();

	void Update();
	bool cornerCollision();
	bool verticalCollision();
	bool horizontalCollision();
	int getPlayerPos();
private:
	Position			m_moveDir;
	Position*			m_playerPos;
	float	m_gravity;
	bool	onGround;
};

#endif