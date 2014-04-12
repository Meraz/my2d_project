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
	virtual ~RenderEntity();

	virtual void Initialize(Position p_position, Position p_origin, Position p_currentSubImage, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation, bool p_hasTransparent, Position p_amountOfSubImages);
	virtual void Initialize(Position p_position, Position p_currentSubImage, Texture2DInterface* p_texture, float p_width, float p_height, bool p_hasTransparent, Position p_amountOfSubImages);
	virtual void Initialize(Position p_position, Texture2DInterface* p_texture, float p_width, float p_height);
	virtual void Initialize(Position p_position, float p_width, float p_height);
	virtual void RenderEntity::Initialize(Position p_position, float p_width, float p_height, bool p_hasTransparent);


	void SetTexture(Texture2DInterface* p_texture);
	virtual	void Render(Jamgine::JamgineEngine* p_engine);
	
	// Load and save class
	std::stringstream ToFile();
//	void LoadClassFromString();
	
private:
	Jamgine::Texture2DInterface* m_texture;
	Jamgine::SpriteEffect		m_spriteEffect;
	Jamgine::Position			m_position;
	Jamgine::Position			m_origin;
	Jamgine::Position			m_currentSubImage; // 0-n
	float m_width;
	float m_height;
	float m_depth;
	float m_rotation;
	bool			  m_hasTransparent;
	Jamgine::Position m_amountOfSubImages;	//1-n

};

#endif