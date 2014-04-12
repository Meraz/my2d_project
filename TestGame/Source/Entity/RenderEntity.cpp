#include <TestGame/Include/Entity/RenderEntity.h>
#include <stdio.h>

RenderEntity::RenderEntity()
{
	m_entity = ENTITY::RENDER;
	
}

RenderEntity::~RenderEntity()
{
}

void RenderEntity::Initialize(Position p_position, Position p_origin, Position p_currentSubImage, char* p_texturePath, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation, bool p_hasTransparent, Position p_amountOfSubImages)
{
	GetEngine(); // Cheat lol

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
}

void RenderEntity::Initialize(Position p_position, Position p_textureOffset, char* p_texture, float p_width, float p_height, bool p_hasTransparent, Position p_amountOfSubImages)
{
	Initialize(
		p_position, 
		Position(0, 0),
		p_textureOffset, 
		p_texture, 
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height, 
		STANDARD_SPRITE_DEPTH, 
		0,
		false,
		Position(1, 1)
		);
}
void RenderEntity::Initialize(Position p_position, char* p_texture, float p_width, float p_height)
{
	Initialize(
		p_position,
		Position(0, 0),
		Position(0, 0),
		p_texture,
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height,
		STANDARD_SPRITE_DEPTH,
		0,
		false,
		Position(1, 1)
		);
}

void RenderEntity::Initialize(Position p_position, float p_width, float p_height)
{
	Initialize(
		p_position,
		Position(0, 0),
		Position(1, 1),
		nullptr,
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height,
		STANDARD_SPRITE_DEPTH,
		0, 
		false,
		Position(1, 1)
		);
}

void RenderEntity::Initialize( Position p_position, float p_width, float p_height, bool p_hasTransparent)
{
	Initialize(
		p_position,
		Position(0, 0),
		Position(1, 1),
		nullptr,
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height,
		STANDARD_SPRITE_DEPTH,
		0,
		p_hasTransparent,
		Position(1, 1)
		);
}

void RenderEntity::SetTexture(Texture2DInterface* p_texture)
{
	m_texture = p_texture;
}

void RenderEntity::Render(Jamgine::JamgineEngine* p_engine)
{

	p_engine->Render(m_position, m_origin, m_currentSubImage, m_texture, m_spriteEffect, m_width, m_height, m_depth, m_rotation, false, Jamgine::Position(1, 1));
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
		m_rotation;												// float
	return l_returnValue;
}

void RenderEntity::LoadClassFromData(char* p_data)
{
	int i = 0;
	sscanf_s(p_data, "%i %f %f %f %f %i %i %s %i %f %f %f %f", 
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
		&m_rotation
		);

	GetEngine();
	m_engine->LoadTexture(&m_texture, m_texturePath);
}

void RenderEntity::GetEngine()
{
	Jamgine::JamgineEngine::CreateEngine(&m_engine, Jamgine::GraphicalSystem::DIRECTX);
}