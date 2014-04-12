#pragma once

#include <TestGame/Include/Entity/RenderEntity.h>

class EntityFactory
{
public:
	EntityFactory();
	virtual ~EntityFactory();

	RenderEntity* CreateObject(int l_entity, char* l_data);
};