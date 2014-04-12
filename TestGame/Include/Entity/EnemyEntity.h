#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <TestGame/Include/Entity/AnimationEntity.h>

class EnemyEntity : public AnimationEntity
{
public:
	EnemyEntity();
	EnemyEntity(Position* playerPos);
	virtual ~EnemyEntity();

	void Update();
	bool cornerCollision();
	bool verticalCollision();
	bool horizontalCollision();
	int getPlayerPos();
private:
	Position			m_moveDir;
	Position*			m_playerPos;
	Texture2DInterface* m_texture;
	SpriteEffect		m_spriteEffect;
	Position			m_position;
	Position			m_origin;
	Position			m_textureOffset;
	float	m_gravity;
	float	m_width;
	float	m_height;
	float	m_depth;
	float	m_rotation;
	bool	onGround;
};

#endif