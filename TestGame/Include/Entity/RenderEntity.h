#ifndef RENDERENTITY_H
#define RENDERENTITY_H

// Engineclass include
#include <Jamgine/Include/Jamgine.h>

// Inheritence include
#include <TestGame/Include/Entity/GameEntity.h>

// c++ Includes
#include <sstream>



using namespace Jamgine;


class RenderEntity : public GameEntity
{
public:
	RenderEntity();
	~RenderEntity();

	virtual void Initialize(Position p_position, Position p_origin, Position p_textureOffset, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation);
	virtual void Initialize(Position p_position, Position p_textureOffset, Texture2DInterface* p_texture, float p_width, float p_height);
	virtual void Initialize(Position p_position, Texture2DInterface* p_texture, float p_width, float p_height);
	virtual void Initialize(Position p_position, float p_width, float p_height);

	void SetTexture(Texture2DInterface* p_texture);
	virtual	void Render(Position p_position, Position p_origin, Position p_textureOffset, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation);
	
	void SetTexture();

	// Load and save class
	std::stringstream ToFile();
	void LoadClassFromString();
	
private:
	Jamgine::Texture2DInterface* m_texture;
	Jamgine::SpriteEffect		m_spriteEffect;
	Jamgine::Position			m_position;
	Jamgine::Position			m_origin;
	Jamgine::Position			m_textureOffset;
	float m_width;
	float m_height;
	float m_depth;
	float m_rotation;
	

};

#endif