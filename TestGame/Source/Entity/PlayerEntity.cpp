#include <TestGame/Include/Entity/PlayerEntity.h>


PlayerEntity::PlayerEntity()
{
	m_entity = ENTITY::PLAYER;
}

PlayerEntity::~PlayerEntity()
{
}

std::stringstream PlayerEntity::ToFile()
{
	using namespace std;
	stringstream l_returnValue = RenderEntity::ToFile();	

	return l_returnValue;
}

void PlayerEntity::LoadClassFromData(char* p_data)
{
	RenderEntity::LoadClassFromData(p_data);
}


void PlayerEntity::Update(double deltaTime)
{


}