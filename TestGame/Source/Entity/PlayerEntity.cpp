#include <TestGame/Include/Entity/PlayerEntity.h>


PlayerEntity::PlayerEntity()
{
	m_entity = ENTITY::PLAYER;
	m_playerOneController = new XBOXController(0);
	m_playerTwoController = new XBOXController(1);
	m_hasGoatBoost = false;
	m_hasWhaleJumped = false;
	m_goatDurationTimer = 0;
	m_goatJumpColdownTimer = 0;
	m_onGround = true;
	m_velocity = Position(0,0);
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

void PlayerEntity::MoveSideways(float amount)
{
	
	amount /= INPUT_X_DEVIDER;
	if (amount*m_velocity.x >= 0)
	{
		m_velocity.x += amount;
		if (abs(m_velocity.x) > MAX_X_VELOCITY)
		{
			if (m_velocity.x > 0)
			{
				m_velocity.x = MAX_X_VELOCITY;
			}
			else
			{
				m_velocity.x = -MAX_X_VELOCITY;
			}
		}
	}
	else
	{
		m_velocity.x = amount;
	}
}


void PlayerEntity::WhaleJump()	//TODO: start animation?
{
	if (!m_hasWhaleJumped)
	{
		m_velocity.y += WHALE_JUMP_VELOCITY;
		if (m_velocity.y > MAX_Y_VELOCITY)
		{
			m_velocity.y = MAX_Y_VELOCITY;
		}
		m_hasWhaleJumped = true;
	}
}

void PlayerEntity::GoatJump()	//TODO: start animation?
{
	if (m_goatJumpColdownTimer == 0)
	{
		if (m_goatDurationTimer == GOAT_HOVER_MAX_TIME)
		{
			m_goatDurationTimer = 0;
		}
		m_hasGoatBoost = true;
	}
}

void PlayerEntity::CheckMovementInputs()
{
	if (m_playerOneController->IsConnected())
	{
		if (((m_playerOneController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0))
		{
			WhaleJump();
		}
		XboxStickDirection dir = m_playerOneController->CheckMovmentStickLeft();
		MoveSideways(dir.x);
		//move camera y?
	}

	if (m_playerTwoController->IsConnected())
	{
		if (((m_playerTwoController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0))
		{
			GoatJump();
		}
		else
		{
			m_hasGoatBoost = false;
		}

		XboxStickDirection dir = m_playerTwoController->CheckMovmentStickLeft();
		MoveSideways(dir.x);
		//move camera y?
	}
}

void PlayerEntity::Update(double deltaTime)
{
	if (hasJumped && !onGround)
	//check inputs
	CheckMovementInputs();

	//move + save position
	Position lastPos = m_position;

	float rocketHover = 0;


	if (m_hasGoatBoost)
	{
		rocketHover = GOAT_JUMP_VELOCITY;
	}

	m_velocity.y += deltaTime*(double)(GRAVITY + rocketHover);
	m_position += Position(m_velocity.x*deltaTime, m_velocity.y*deltaTime);

	if (m_position.y <= 0)
	{
		m_position.y = 0;
		m_velocity.y = 0;
		m_hasWhaleJumped = false;
	}

	if (m_velocity.x > 0)
	{
		m_velocity.x -= FRICTION_X_LINEAR_SUBTRACTER*deltaTime;
		if (m_velocity.x < 0)
		{
			m_velocity.x = 0;
		}
	}
	else if (m_velocity.x < 0)
	{
		m_velocity.x += FRICTION_X_LINEAR_SUBTRACTER*deltaTime;
		if (m_velocity.x > 0)
		{
			m_velocity.x = 0;
		}
	}

	if (m_goatDurationTimer != GOAT_HOVER_MAX_TIME)
	{
		m_goatDurationTimer += deltaTime;
		if (m_goatDurationTimer >= GOAT_HOVER_MAX_TIME)
		{
			m_hasGoatBoost = false;
			m_goatDurationTimer = GOAT_HOVER_MAX_TIME;
			m_goatJumpColdownTimer = GOAT_HOVER_COLDOWN_TIME;
		}
	}
	else if (m_goatJumpColdownTimer != 0)
	{
		m_goatJumpColdownTimer -= deltaTime;
		if (m_goatJumpColdownTimer <= 0)
		{
			m_goatJumpColdownTimer = 0;
		}
	}
}

	//check collision for Y and X seperate nullify velocity if hit wall etc,
	//if (m_hasGoatJumped)
	//{
	//	m_goatHoverTimer+=deltaSec;
	//	if (m_goatHoverTimer > GOAT_HOVER_MAX_TIME)
	//	{
	//		m_hasGoatJumped = false; //add cooldown
	//	}
	//}
	//JEEEEENS FIX DIS!
	/*if (hasJumped && !onGround)
	{
		m_moveDir.y--;

		if (m_position.y - 1 == groundheight)
		{
			m_moveDir.y = 0;
			onGround = true;
		}*/
