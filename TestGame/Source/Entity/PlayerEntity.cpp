#include <TestGame/Include/Entity/PlayerEntity.h>
#include <Windows.h>
#include <math.h>

static const float maxSpeed = 0.10f;

// should implement a
Point Rotate(Point p_point, float p_angle);
PlayerEntity::PlayerEntity()
	: m_direction()
{
	m_entity = ENTITY::PLAYER;
	m_once = true;
	m_direction = Point(0.0f, 1.0f);	
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

Point Rotate(Point p_point, float p_angle)
{
	float cosAngle = cos(p_angle);
	float sinAngle = sin(p_angle);


	Point l_point;
	l_point.x = p_point.x * cosAngle - p_point.y * sinAngle;
	l_point.y = p_point.x * sinAngle + p_point.y * cosAngle;
	return l_point;
}

float CalcAcceleration(float p_speed)
{
	return 1/(p_speed*p_speed+8.0f);
}

void PlayerEntity::AddRotation(float p_angle)
{
	m_rotation += p_angle;
	if(p_angle > 360)
	{
		m_rotation = (int)m_rotation % 360;
	}

	if(p_angle == 360.0f)
	{
		p_angle = 360.0f;
	}
}

static const float pi = 3.1415;
static const float rotationSpeed = pi;

void PlayerEntity::Update(double p_deltaTime)
{	
	RenderEntity::Update(p_deltaTime);
	if(m_once)
	{
		m_spawn = m_position;
		m_once = false;
	}

	m_acceleration = 0;
	Point l_pos = m_position;
	// Update speed_direction
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		AddRotation(rotationSpeed*p_deltaTime);
		m_direction = Rotate(m_direction, -rotationSpeed*p_deltaTime);
		m_direction.Normalize();
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		AddRotation(-rotationSpeed*p_deltaTime);
		m_direction = Rotate(m_direction, rotationSpeed*p_deltaTime);
		m_direction.Normalize();
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// Add acceleration
		m_acceleration = CalcAcceleration(m_velocity.Length());
		//m_acceleration = acceleration;
		m_velocity.x += m_direction.x*m_acceleration*p_deltaTime;
		m_velocity.y += m_direction.y*m_acceleration*p_deltaTime;
	}

	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		// Add acceleration
		m_acceleration = -CalcAcceleration(m_velocity.Length());
		m_velocity.x += m_direction.x*m_acceleration*p_deltaTime;
		m_velocity.y += m_direction.y*m_acceleration*p_deltaTime;
	}

	Point l_position;
	l_position.x = m_position.x + m_velocity.x;
	l_position.y = m_position.y + m_velocity.y;
	

	// Right and left border
	if((m_position.x + m_width) > 800.0f || (m_position.x) < 0.0f)
	{
		m_velocity.x *= -1.0f;
	}

	// Right and left border
	if((m_position.y + m_height) > 800.0f || (m_position.y) < 0.0f)
	{
		m_velocity.y *= -1.0f;
	}
	
	// Limit speed to maxSpeed
	float l_length = m_velocity.Length();
	if(l_length > maxSpeed)
	{
		m_velocity.x = m_velocity.x / l_length * maxSpeed;
		m_velocity.y = m_velocity.y / l_length * maxSpeed;
	}
	

	// Stop if very slow and not accelerating, might remove this later
	if(l_length > 0 && l_length < 0.01 && m_acceleration == 0)
	{
		m_velocity.x = 0.0f;
		m_velocity.y = 0.0f;
	}
	
	m_position.x = m_position.x + m_velocity.x;
	m_position.y = m_position.y + m_velocity.y;
}

CollisionEntity* PlayerEntity::CreateProjectile()
{
	CollisionEntity* l_entity;
	l_entity = new CollisionEntity();
	l_entity->Initialize(Point(m_position.x+m_origin.x, m_position.y+m_origin.y), Point(1.5f, 1.5f), Point(0.0f, 0.0f), "SpaceShip.dds", SpriteEffect::FLIP_NONE, 3.0f, 3.0f, 0.1f, 0.0f, false, Point(1.0f, 1.0f));
	
	l_entity->SetVelocity(Point(m_direction.x*5,m_direction.y*5));

	return l_entity;
}

void PlayerEntity::RestToSpawn()
{
	m_position = m_spawn;
}