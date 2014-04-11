#pragma once
#include <Jamgine/Include/Shared.h>
#include <Jamgine/Include/Texture/Texture2DInterface.h>

namespace Jamgine
{
	namespace JDirectX
	{
		struct SpriteData
		{
			Position position;
			Position origin;
			Position textureOffset;
			Texture2D* texture;
			SpriteEffect spriteEffect;
			float width;
			float height;
			float depth;
			float rotation;

			SpriteData(
				Position p_position,
				Position p_origin,
				Position p_textureOffset,
				Texture2D* p_texture,
				SpriteEffect p_spriteEffect,
				float p_width,
				float p_height,
				float p_depth,
				float p_rotation
				)
			{
				position = p_position;
				origin	= p_origin;
				textureOffset = p_textureOffset;
				texture = p_texture;
				spriteEffect = p_spriteEffect;
				width = p_width;
				height = p_height;
				depth = p_depth;
				rotation = p_rotation;
			}
			
			// Without flip
			SpriteData
				(
				Position p_position,
				Position p_origin,
				Position p_textureOffset,
				Texture2D* p_texture,
				float p_width,
				float p_height,
				float p_depth,
				float p_rotation)
			{
				position = p_position;
				origin	= p_origin;
				textureOffset = p_textureOffset;
				texture = p_texture;
				spriteEffect =	SpriteEffect::FLIP_NONE;
				width = p_width;
				height = p_height;
				depth = p_depth;
				rotation = p_rotation;
			}

			// without flip and origin
			SpriteData(
				Position p_position,
				Position p_textureOffset,
				Texture2D* p_texture,
				float p_width,
				float p_height,
				float p_depth
				)
			{
				position = p_position;
				origin	= Position(0,0);
				textureOffset = p_textureOffset;
				texture = p_texture;
				spriteEffect =	SpriteEffect::FLIP_NONE;
				width = p_width;
				height = p_height;
				depth = p_depth;
				rotation = 0;
			}

			// Without origin and rotation
			SpriteData(
				Position p_position,
				Position p_textureOffset,
				Texture2D* p_texture,
				SpriteEffect p_spriteEffect,
				float p_width,
				float p_height,
				float p_depth
				)
			{
				position = p_position;
				origin	= Position(0,0);
				textureOffset = p_textureOffset;
				texture = p_texture;
				spriteEffect =	p_spriteEffect;
				width = p_width;
				height = p_height;
				depth = p_depth;
				rotation = 0;
			}
		};
	}	
}