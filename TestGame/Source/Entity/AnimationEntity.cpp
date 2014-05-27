#include <TestGame\Include\Entity\AnimationEntity.h>


AnimationEntity::AnimationEntity()
{
	m_entity = ENTITY::ANIMATION;
}


AnimationEntity::~AnimationEntity()
{
}

bool AnimationEntity::Animate()
{
	m_currentSubImage.x++;
	if (m_currentSubImage.x == m_amountOfSubImages.x)
	{
		m_currentSubImage.y++;
		m_currentSubImage.x = 0;
		if (m_currentSubImage.y == m_amountOfSubImages.y)
		{
			m_currentSubImage.y = 0;
			return true;
		}
	}
	return false;
}

bool AnimationEntity::Animate(int p_section)
{
	m_currentSubImage.x++;
	if (m_currentSubImage.x == m_amountOfSubImages.x)
	{
		m_currentSubImage.x = 0;
		return true;
	}
	return false;
}

void AnimationEntity::ResetAnimation()
{
	m_currentSubImage.x = 0;
	m_currentSubImage.y = 0;
}

