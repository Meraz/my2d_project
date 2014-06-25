#include <TestGame/Include/Entity/EnemyEntity.h>


EnemyEntity::EnemyEntity( )
{
	m_entity = ENTITY::ENENMY;
}

EnemyEntity::~EnemyEntity()
{

}

void EnemyEntity::Update(double p_deltaTime)
{

	RenderEntity::Update(p_deltaTime);
}

bool EnemyEntity::OutsideBounds(float p_left, float p_right, float p_bot, float p_top)
{
	Jamgine::Rectangle a = Jamgine::Rectangle(p_left, p_bot, abs(p_left-p_right), abs(p_top-p_bot));

	if(m_rectangle.Intersect(a) == false)
		return true;
	return false;
}
