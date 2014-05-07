#include <TestGame/Include/Entity/PlayerEntity.h>
#include <Windows.h>

PlayerEntity::PlayerEntity()
: m_speed(50.0f)
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
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_position.x = m_position.x + m_speed * deltaTime;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_position.x = m_position.x - m_speed * deltaTime;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_position.y = m_position.y + m_speed * deltaTime;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_position.y = m_position.y - m_speed * deltaTime;
	}
}