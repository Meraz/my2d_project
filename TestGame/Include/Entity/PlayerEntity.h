#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include <TestGame/Include/Entity/AnimationEntity.h>
class PlayerEntity : public AnimationEntity
{
public:
	PlayerEntity();
	~PlayerEntity();

	void moveLeft();
	void moveRight();
	void jump();
	void Update();
private:
	Position			m_moveDir;
	Texture2DInterface* m_texture;
	SpriteEffect		m_spriteEffect;
	Position			m_position;
	Position			m_origin;
	Position			m_textureOffset;
	float	m_width;
	float	m_height;
	float	m_depth;
	float	m_rotation;
	bool	hasJumped;
	bool	onGround;
};

#endif