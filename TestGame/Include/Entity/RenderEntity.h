#ifndef RENDERENTITY_H
#define RENDERENTITY_H
#include <TestGame/Include/Entity/GameEntity.h>
#include <Jamgine/Include/Jamgine.h>
using namespace Jamgine;

class RenderEntity : public GameEntity
{
public:
	RenderEntity();
	~RenderEntity();
	virtual	void Render(Position p_position, Position p_origin, Position p_textureOffset, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation);
private:
	Texture2DInterface *m_texture;
	SpriteEffect m_spriteEffect;
	Position m_position;
	Position m_origin;
	Position m_textureOffset;
	Texture2DInterface* m_texture;
	float m_width;
	float m_height;
	float m_depth;
	float m_rotation;
	

};

#endif