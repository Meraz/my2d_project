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
	PLAYER,
	PROJECTILE
};

class RenderEntity
{
public:
	RenderEntity();
	virtual ~RenderEntity();

	virtual void Initialize(JFloat2 p_position, JFloat2 p_origin, JFloat2 p_currentSubImage, char* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation, bool p_hasTransparent, JFloat2 p_amountOfSubImages);
	virtual void Initialize(JFloat2 p_position, JFloat2 p_currentSubImage, char* p_texture, float p_width, float p_height, bool p_hasTransparent, JFloat2 p_amountOfSubImages);
	virtual void Initialize(JFloat2 p_position, char* p_texture, float p_width, float p_height);
	virtual void Initialize(Jamgine::Rectangle p_rectangle,  char* p_texture);
	virtual void Initialize(JFloat2 p_position, float p_width, float p_height);
	virtual void Initialize(JFloat2 p_position, float p_width, float p_height, bool p_hasTransparent);
	virtual void Initialize(Jamgine::Rectangle p_rectangle, Texture2D* p_texture, Jamgine::JamgineEngine* p_engine);

	void SetTexture(Texture2D* p_texture);
	virtual void Update(double p_deltaTime);
	virtual	void Render();
	
	// Load and save class
	virtual std::stringstream ToFile();
	virtual void LoadClassFromData(char* p_data); // Return how many variables you read
	
	ENTITY m_entity;
	char m_texturePath[50];
	Jamgine::Texture2D*	m_texture;
	Jamgine::SpriteEffect			m_spriteEffect;
	Jamgine::JFloat2					m_position;
	Jamgine::JFloat2					m_origin;
	Jamgine::JFloat2					m_currentSubImage; // 0-n
	float m_width;
	float m_height;
	float m_depth;
	float m_rotation;
	bool			  m_hasTransparent;
	Jamgine::JFloat2 m_amountOfSubImages;	//1-n
	Jamgine::JamgineEngine* m_engine;		//1-n
	Jamgine::Rectangle m_rectangle;

};

#endif