#ifndef RENDERENTITY_H
#define RENDERENTITY_H

// Engineclass include
#include <Jamgine/Include/Jamgine.h>
#include <Jamgine/Include/JFloat2.h>
#include <Jamgine/Include/Rectangle.h>
#include <Jamgine/Render/Include/Texture2D.h>
#include <Jamgine/Render/Include/SpriteEffect.h>
#include <Jamgine/Render/Include/Spritedata.h>

// c++ Includes
#include <string>
#include <sstream>

// Class forward declarations
using namespace Jamgine;
using namespace Jamgine::Render;

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
	virtual void Initialize(Rectangle p_rectangle,  char* p_texture);
	virtual void Initialize(JFloat2 p_position, float p_width, float p_height);
	virtual void Initialize(JFloat2 p_position, float p_width, float p_height, bool p_hasTransparent);
	virtual void Initialize(Rectangle p_rectangle, Texture2D* p_texture, JamgineEngine* p_engine);

	void SetTexture(Texture2D* p_texture);
	virtual void Update(double p_deltaTime);
	virtual	void Render();
	
	// Load and save class
	virtual std::stringstream ToFile();
	virtual void LoadClassFromData(char* p_data); // Return how many variables you read
	
	ENTITY m_entity;
	char m_texturePath[50];
	Texture2D*	m_texture;
	SpriteEffect			m_spriteEffect;
	JFloat2					m_position;
	JFloat2					m_origin;
	JFloat2					m_currentSubImage; // 0-n
	float m_width;
	float m_height;
	float m_depth;
	float m_rotation;
	bool			  m_hasTransparent;
	JFloat2 m_amountOfSubImages;	//1-n
	JamgineEngine* m_engine;		//1-n
	Rectangle m_rectangle;

};

#endif