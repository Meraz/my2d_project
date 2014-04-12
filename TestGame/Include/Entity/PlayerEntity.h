#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include <TestGame/Include/Entity/RenderEntity.h>

class PlayerEntity : public RenderEntity
{
public:
	PlayerEntity();
	virtual ~PlayerEntity();

	virtual std::stringstream ToFile();
	virtual void LoadClassFromData(char* p_data);

private:

};

#endif