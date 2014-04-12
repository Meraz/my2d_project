#include <TestGame/Include/Entity/EntityFactory.h>
#include <TestGame/Include/Entity/EnemyEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>
#include <TestGame/Include/Entity/RenderEntity.h>

EntityFactory::EntityFactory()
{

}
EntityFactory::~EntityFactory()
{

}

RenderEntity* EntityFactory::CreateObject(int l_entity, char* l_data)
{
	RenderEntity* l_returnEntity;
//	if (l_entity == ENTITY::ANIMATION)
//	{
//		l_returnEntity = new
//	}
//	else if (l_entity == ENTITY::COLLISION)
//	{
//
//	}
	if (l_entity == (int)ENTITY::ENENMY)
	{
		l_returnEntity = new EnemyEntity();
	}
	else if (l_entity == (int)ENTITY::PLAYER)
	{
		l_returnEntity = new PlayerEntity();
	}
	else if (l_entity == (int)ENTITY::RENDER)
	{
		l_returnEntity = new RenderEntity();
	}
	l_returnEntity->LoadClassFromData(l_data);
	return l_returnEntity;
}