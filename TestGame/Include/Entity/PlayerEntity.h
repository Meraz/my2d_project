#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include <TestGame/Include/Entity/AnimationEntity.h>

class PlayerEntity : public AnimationEntity
{
public:
	PlayerEntity();
	virtual ~PlayerEntity();

	virtual std::stringstream ToFile();
	virtual void LoadClassFromData(char* p_data);

	virtual void Update(double p_deltaTime);

	CollisionEntity* CreateProjectile();

private:
	Point m_direction;
//	Point m_velocity;
//	float m_acceleration;	

	void AddRotation(float p_angle);

	

};

#endif