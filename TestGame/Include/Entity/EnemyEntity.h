#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <TestGame/Include/Entity/AnimationEntity.h>

class EnemyEntity : public AnimationEntity
{
public:
	EnemyEntity();
	EnemyEntity(Point* playerPos);
	virtual ~EnemyEntity();

	void Update();
	bool cornerCollision();
	bool verticalCollision();
	bool horizontalCollision();
	int getPlayerPos();
private:
	Point			m_moveDir;
	Point*			m_playerPos;
	float	m_gravity;
	bool	onGround;
};

#endif