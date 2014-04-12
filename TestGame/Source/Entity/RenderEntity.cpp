#include <TestGame/Include/Entity/RenderEntity.h>

#include <string>
#include <sstream>

RenderEntity::RenderEntity()
{
}

RenderEntity::~RenderEntity()
{
}

void RenderEntity::Initialize(Position p_position, Position p_origin, Position p_textureOffset, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation)
{
	m_position = p_position;
	m_origin = p_origin; 
	m_textureOffset = p_textureOffset;
	m_texture = p_texture;
	m_spriteEffect = p_spriteEffect;
	m_width = p_width;
	m_height = p_height;
	m_depth = p_depth;
	m_rotation = p_rotation;
}

void RenderEntity::Initialize(Position p_position, Position p_textureOffset, Texture2DInterface* p_texture, float p_width, float p_height)
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
		0
		);
}
void RenderEntity::Initialize(Position p_position, Texture2DInterface* p_texture, float p_width, float p_height)
{
	Initialize(
		p_position,
		Position(0, 0),
		Position(1, 1),
		p_texture,
		SpriteEffect::FLIP_NONE,
		p_width,
		p_height,
		STANDARD_SPRITE_DEPTH,
		0
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
		0
		);
}

void RenderEntity::SetTexture(Texture2DInterface* p_texture)
{
	m_texture = p_texture;
}

void RenderEntity::Render(Position p_position, Position p_origin, Position p_textureOffset, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect, float p_width, float p_height, float p_depth, float p_rotation)
{

}

std::stringstream RenderEntity::ToFile()
{
	using namespace std;
	stringstream l_returnValue;
	l_returnValue << 
		m_position.x						<< ' ' << 
		m_position.y						<< ' ' <<
		m_origin.x							<< ' ' <<
		m_origin.y							<< ' ' <<
		m_textureOffset.x					<< ' ' <<
		m_textureOffset.y					<< ' ' <<
		static_cast<int>(m_spriteEffect)	<< ' ' <<
		m_width								<< ' ' <<
		m_height							<< ' ' <<
		m_depth								<< ' ' <<
		m_rotation;
	return l_returnValue;
}