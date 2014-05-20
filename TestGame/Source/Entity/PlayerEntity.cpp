#include <TestGame/Include/Entity/PlayerEntity.h>
#include <Windows.h>

static const float speedFactor = 1.2f;
static const float frictionFactor = 0.7f;

// should implement a

PlayerEntity::PlayerEntity()
: m_speed(0.0f, 0.0f)
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
	// Update speed_direction
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_speed.x += speedFactor;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_speed.x -= speedFactor;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_speed.y += speedFactor;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_speed.y -= speedFactor;
	}

	if(m_speed.x > 0)
	{
		m_speed.x -= frictionFactor;
	}
	else if(m_speed.x < 0)
	{
		m_speed.x += frictionFactor;
	}

	if(m_speed.y > 0)
	{
		m_speed.y -= frictionFactor;
	}
	else if(m_speed.y < 0)
	{
		m_speed.y += frictionFactor;
	}

	// if close to zero brake
	if(m_speed.x > 0.0f && m_speed.x < 0.1f)
		m_speed.x = 0.0f;

	if(m_speed.y > 0.0f && m_speed.y < 0.1f)
		m_speed.y = 0.0f;

	// Update position
	m_position.x = m_position.x + m_speed.x * deltaTime;
	m_position.y = m_position.y + m_speed.y * deltaTime;
}