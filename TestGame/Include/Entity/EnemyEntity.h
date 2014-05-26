#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <TestGame/Include/Entity/AnimationEntity.h>

// forward declaration
class LuaManager;

class EnemyEntity : public AnimationEntity
{
public:
//	EnemyEntity();
	EnemyEntity(LuaManager* p_luaManager);
	virtual ~EnemyEntity();

	void Update(double p_deltaTime);

private:
	LuaManager* m_luaManager;
	float m_totalMovement;
};

#endif