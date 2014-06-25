#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <TestGame/Include/Entity/AnimationEntity.h>

// Forward declaration

class EnemyEntity : public AnimationEntity
{
public:
	EnemyEntity();
	virtual ~EnemyEntity();

	void Update(double p_deltaTime);
	bool OutsideBounds(float p_left, float p_right, float p_bot, float p_top);
};

#endif