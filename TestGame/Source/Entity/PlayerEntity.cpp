#include <TestGame/Include/Entity/PlayerEntity.h>


PlayerEntity::PlayerEntity(int num)
{
	m_entity = ENTITY::PLAYER;
	m_playerOneController = new XBOXController(num);

	m_hasGoatBoost = false;
	m_hasWhaleJumped = false;
	m_goatDurationTimer = 0;
	m_goatJumpColdownTimer = 0;
	m_animationWhaleJumpTimer = 0;
	m_onGround = false;
	m_isWhaleAnimating = false;
	m_velocity = Point(0,0);
	m_isAlive = true;
	m_noControl = false;
	IsReversedYaxis = false;
	noControlTimer = NO_CONTROL_PENALTY;
	playerNum = num;

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
		m_onGround = false;
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
		if (((m_playerOneController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0))
		{
			GoatJump();
		}
		if (((m_playerOneController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0))
		{
			/*if (IsReversedYaxis)
			{
				IsReversedYaxis = false;
			}
			else
			{
				IsReversedYaxis = true;
			}*/
		}
		dir += m_playerOneController->CheckMovmentStickLeft();

	}

	/*if (m_playerTwoController->IsConnected())
	{
		
		else
		{
			m_hasGoatBoost = false;
		}

		dir += m_playerTwoController->CheckMovmentStickLeft();

	}*/
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
	//if (hasJumped && !onGround)
	//check inputs

	if (m_isAlive)
	{
		if (!m_noControl)
		{
			CheckMovementInputs();
		}
		else
		{
			noControlTimer += deltaTime;
			if (noControlTimer >= NO_CONTROL_PENALTY)
			{
				m_noControl = false;
				noControlTimer = NO_CONTROL_PENALTY;
			}
		}
		
		
		

		//move + save position
		lastPos = m_position;

		float rocketHover = 0;

		if (m_hasGoatBoost)
		{
			rocketHover = GOAT_JUMP_VELOCITY;
		}

		/*if (!m_onGround)
		{*/
			m_velocity.y += deltaTime*(double)(GRAVITY + rocketHover);
			m_position += Point(m_velocity.x*deltaTime, m_velocity.y*deltaTime);
		//}
		
		

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
			if (m_animationWhaleJumpTimer > WHALE_JUMP_ANIMATION_TIME)
			{

				m_animationWhaleJumpTimer = 0;
				if (Animate())
				{
					m_isWhaleAnimating = false;
				
				}
			}
		}
	}
}

void PlayerEntity::CollideStatic()
{
	if (m_position.y <= lastPos.y)
	{
		m_onGround = true;
		
	}
}

void PlayerEntity::AddAnimationTexture(float p_width, float p_height, char * p_textureName, Jamgine::Point p_numOfSubTextures)
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

bool PlayerEntity::IsOnGround()
{
	return m_onGround;
}

void PlayerEntity::SetVelocityX(float amount)
{
	m_velocity.x = amount;
}
void PlayerEntity::SetVelocityY(float amount)
{
	m_velocity.y = amount;
}
void PlayerEntity::BackPosition()
{
	m_position = lastPos;
}
void PlayerEntity::SetOnGround()
{
	m_onGround =true;
}

void PlayerEntity::InverseCollide()
{
	/*if (m_velocity.y < 0.01)
	{
		m_velocity.y = 10;
	}
	else
	{
		m_velocity.x = m_velocity.x * -1;
	}*/
	
	m_velocity.x = ( m_velocity.x) * (-0.5);
	if (IsReversedYaxis)
	{
		m_velocity.y = -100;
	}
	else
	{
		m_velocity.y = 100;
	}

	m_position = lastPos;
	m_hasWhaleJumped = false;
	if (noControlTimer == NO_CONTROL_PENALTY)
	{
		noControlTimer = 0;
		m_noControl = true;
	}
}

void PlayerEntity::JawsCollide(int topLeft, int topRight, int botLeft, int botRight, float objTop, float objBot)
{
	//other stuff maybe
	if (botLeft + botRight == 2) //bot collide
	{
		m_position.y = objTop ;
		m_velocity.y = 0;
		m_hasWhaleJumped = false;
	}
	if (botRight + topRight == 2|| botLeft + topLeft == 2)
	{
		m_position.x = objTop;
		m_velocity.x = 0;
	}
	
}
