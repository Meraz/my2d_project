#ifndef RENDERENTITY_H
#define RENDERENTITY_H

// Engineclass include
#include <Jamgine/Include/Jamgine.h>

// c++ Includes
#include <string>
#include <sstream>

// Class forward declarations
using namespace Jamgine;

enum class ENTITY
{
	RENDER,
	COLLISION,
	ANIMATION,
	ENENMY,
	PLAYER
};



class RenderEntity
{
public:
	RenderEntity();
	virtual ~RenderEntity();

	virtual void Initialize(Position p_position, Position p_origin, Position p_currentSubImage, char* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation, bool p_hasTransparent, Position p_amountOfSubImages);
	virtual void Initialize(Position p_position, Position p_currentSubImage, char* p_texture, float p_width, float p_height, bool p_hasTransparent, Position p_amountOfSubImages);
	virtual void Initialize(Position p_position, char* p_texture, float p_width, float p_height);
	virtual void Initialize(Position p_position, float p_width, float p_height);
	virtual void Initialize(Position p_position, float p_width, float p_height, bool p_hasTransparent);


	void SetTexture(Texture2DInterface* p_texture);
	virtual	void Render(Jamgine::JamgineEngine* p_engine);
	
	// Load and save class
	virtual std::stringstream ToFile();
	virtual void LoadClassFromData(char* p_data); // Return how many variables you read
	
	ENTITY m_entity;
	char m_texturePath[50];
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
	Jamgine::JamgineEngine* m_engine;		//1-n

protected:


	void GetEngine();
};

#endif