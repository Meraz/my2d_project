#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <TestGame/Include/Entity/AnimationEntity.h>

// forward declaration
class LuaManager;

class EnemyEntity : public AnimationEntity
{
public:
//	EnemyEntity();
	EnemyEntity(LuaManager* p_luaManager, Point m_spawnPosition);
	virtual ~EnemyEntity();

	void Update(double p_deltaTime);
	bool OutsideBounds(float p_left, float p_right, float p_bot, float p_top);

private:
	LuaManager* m_luaManager;
	float m_totalMovement;
	Point  m_spawnPosition;
};

#endif