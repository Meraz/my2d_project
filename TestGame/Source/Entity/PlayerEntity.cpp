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
	m_animationWhaleJumpTimer = 0;
	m_onGround = true;
	m_isWhaleAnimating = false;
	m_velocity = Position(0,0);

	AnimationSetup newSetup;
	newSetup.numOfSubTextures = m_amountOfSubImages;
	newSetup.height = m_height;
	newSetup.width = m_width;
	newSetup.texture = m_texture;
	m_animations.push_back(newSetup);
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
	/*if (!collisionWall)
		m_moveDir.x = -1;
	else
		m_moveDir.x = 0;*/
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
		m_isWhaleAnimating = true;
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
	XboxStickDirection dir = XboxStickDirection(0,0);
	if (m_playerOneController->IsConnected())
	{
		if (((m_playerOneController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0))
		{
			WhaleJump();
		}
		dir += m_playerOneController->CheckMovmentStickLeft();

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

		dir += m_playerTwoController->CheckMovmentStickLeft();

	}
	MoveSideways(dir.x);
	if (dir.x < 0)
	{
		m_spriteEffect = Jamgine::SpriteEffect::FLIP_HORIZONTALLY;
	}
	else if(dir.x != 0)
	{
		m_spriteEffect = Jamgine::SpriteEffect::FLIP_NONE;
	}
}

void PlayerEntity::Update(double deltaTime)
{
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
		m_isWhaleAnimating = false;
		ResetAnimation();
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
	if (m_isWhaleAnimating)
	{
		m_animationWhaleJumpTimer += deltaTime;
		if (m_animationWhaleJumpTimer > 0.06)
		{
			m_animationWhaleJumpTimer = 0;
			if (Animate())
			{
				m_isWhaleAnimating = false;
				
			}
		}
	}
}


void PlayerEntity::AddAnimationTexture(float p_width, float p_height, char * p_textureName, Jamgine::Position p_numOfSubTextures)
{
	AnimationSetup newSetup;
	newSetup.numOfSubTextures = p_numOfSubTextures;
	newSetup.height = p_height;
	newSetup.width = p_width;
	m_engine->LoadTexture( &newSetup.texture , p_textureName);
	m_animations.push_back(newSetup);
}

void PlayerEntity:: UseAnimationSetup(int p_setupIndex)
{
	if (p_setupIndex >= m_animations.size())
	{
		return;
	}

	AnimationSetup a = m_animations[p_setupIndex];

	m_height = a.height;
	m_width = a.width;
	m_texture = a.texture;
	m_amountOfSubImages = a.numOfSubTextures;

	ResetAnimation();
}