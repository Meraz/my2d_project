#ifndef ANIMATIONENTITY_H
#define ANIMATIONENTITY_H
#include <TestGame/Include/Entity/CollisionEntity.h>
class AnimationEntity : public CollisionEntity
{
public:
	AnimationEntity();
	~AnimationEntity();

	//returns true when animation is done
	bool Animate();

	bool Animate(int p_section);
	void ResetAnimation();



private:


};

#endif