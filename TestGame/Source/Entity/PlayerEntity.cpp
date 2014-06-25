#include <TestGame/Include/Entity/PlayerEntity.h>
#include <Windows.h>
#include <math.h>

static const float maxSpeed = 0.10f;

PlayerEntity::PlayerEntity()
{

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

void PlayerEntity::Update(double p_deltaTime)
{	
	RenderEntity::Update(p_deltaTime);
}