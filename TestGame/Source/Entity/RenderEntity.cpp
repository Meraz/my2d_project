#include <TestGame/Include/Entity/RenderEntity.h>
#include <stdio.h>

RenderEntity::RenderEntity()	
{
	m_entity = ENTITY::RENDER;
}

RenderEntity::~RenderEntity()
{
}

void RenderEntity::Initialize(Point p_position, Point p_origin, Point p_currentSubImage, char* p_texturePath, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation, bool p_hasTransparent, Point p_amountOfSubImages)
{
	strcpy(m_texturePath, p_texturePath);

	m_position = p_position;
	m_origin = p_origin; 
	m_currentSubImage = p_currentSubImage;
	m_engine->LoadTexture(&m_texture, p_texturePath);
	m_spriteEffect = p_spriteEffect;
	m_width = p_width;
	m_height = p_height;
	m_depth = p_depth;
	m_rotation = p_rotation;
	m_hasTransparent = p_hasTransparent;
	m_amountOfSubImages = p_amountOfSubImages;
	m_rectangle = Rectangle(m_position, m_width, m_height);
}

void RenderEntity::Initialize(Point p_position, Point p_textureOffset, char* p_texture, float p_width, float p_height, bool p_hasTransparent, Point p_amountOfSubImages)
{
	Initialize(
		p_position, 
		Point(0, 0),
		p_textureOffset, 
		p_texture, 
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height, 
		STANDARD_SPRITE_DEPTH, 
		0,
		false,
		Point(1, 1)
		);
}
void RenderEntity::Initialize(Point p_position, char* p_texture, float p_width, float p_height)
{
	Initialize(
		p_position,
		Point(0, 0),
		Point(0, 0),
		p_texture,
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height,
		STANDARD_SPRITE_DEPTH,
		0,
		false,
		Point(1, 1)
		);
}

void RenderEntity::Initialize(Point p_position, float p_width, float p_height)
{
	Initialize(
		p_position,
		Point(0, 0),
		Point(1, 1),
		nullptr,
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height,
		STANDARD_SPRITE_DEPTH,
		0, 
		false,
		Point(1, 1)
		);
}

void RenderEntity::Initialize(Jamgine::Rectangle p_rectangle, char* p_texture)
{
	Initialize(
		p_rectangle.position,
		Point(0, 0),
		Point(0, 0),
		p_texture,
		SpriteEffect::FLIP_NONE,
		p_rectangle.width,
		p_rectangle.height,
		STANDARD_SPRITE_DEPTH,
		0,
		false,
		Point(1, 1)
		);
}

void RenderEntity::Initialize(Point p_position, float p_width, float p_height, bool p_hasTransparent)
{
	Initialize(
		p_position,
		Point(0, 0),
		Point(1, 1),
		nullptr,
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height,
		STANDARD_SPRITE_DEPTH,
		0,
		p_hasTransparent,
		Point(1, 1)
		);
}

void RenderEntity::Initialize(Jamgine::Rectangle p_rectangle, Texture2DInterface* p_texture, Jamgine::JamgineEngine* p_engine)
{
	m_rectangle = p_rectangle;
	m_texture = p_texture;
	m_engine = p_engine;
}

void RenderEntity::SetTexture(Texture2DInterface* p_texture)
{
	m_texture = p_texture;
}

void RenderEntity::Update(double p_deltaTime)
{
	m_rectangle.position.x	= m_position.x;
	m_rectangle.position.y	= m_position.y;
	m_rectangle.width		= m_width;
	m_rectangle.height		= m_height;
}


void RenderEntity::Render()
{
	//m_engine->Render(m_rectangle, m_texture);
	//float m_rectangle.position.x;
	//if ((int)m_rectangle.position.x % 2 == 0)
		m_engine->Render(Jamgine::SpriteData(m_rectangle, Point(), Jamgine::Rectangle(0.0f, 0.0f, 1.0f, 1.0f), m_texture, Jamgine::SpriteEffect::FLIP_NONE, 0.5, 0, true));
	//else
	//	m_engine->Render(Jamgine::SpriteData(m_rectangle, Point(), Jamgine::Rectangle(0.0f, 0.0f, 1.0f, 1.0f), m_texture, Jamgine::SpriteEffect::FLIP_NONE, 0.6, 0, false));
}

std::stringstream RenderEntity::ToFile()
{
	using namespace std;
	stringstream l_returnValue;
	l_returnValue <<						
		static_cast<unsigned int>(m_entity)			<< ' ' <<	// signed int
		m_position.x								<< ' ' <<	// float
		m_position.y								<< ' ' <<	// float
		m_origin.x									<< ' ' <<	// float
		m_origin.y									<< ' ' <<	// float
		m_currentSubImage.x							<< ' ' <<	// signed int
		m_currentSubImage.y							<< ' ' <<	// signed int
		m_texturePath								<< ' ' <<	// string, array of chars
		static_cast<unsigned int>(m_spriteEffect)	<< ' ' <<	// signed int
		m_width										<< ' ' <<	// float
		m_height									<< ' ' <<	// float
		m_depth										<< ' ' <<	// float
		m_rotation									<< ' ' <<	// float
		m_hasTransparent							<< ' ' <<
		m_amountOfSubImages.x						<< ' ' <<
		m_amountOfSubImages.y;										
	return l_returnValue;
}

void RenderEntity::LoadClassFromData(char* p_data)
{
	int i = 0;
	sscanf_s(p_data, "%i %f %f %f %f %i %i %s %i %f %f %f %f %i %f %f", 
		&m_entity,
		&m_position.x, 
		&m_position.y,
		&m_origin.x,
		&m_origin.y,
		&m_currentSubImage.x,
		&m_currentSubImage.y,
		&m_texturePath, sizeof(m_texturePath),
		&m_spriteEffect,
		&m_width,
		&m_height,
		&m_depth,
		&m_rotation,
		&m_hasTransparent,
		&m_amountOfSubImages.x,
		&m_amountOfSubImages.y
		);
	m_engine->LoadTexture(&m_texture, m_texturePath);
	m_rectangle = Rectangle(m_position, m_width, m_height);
}