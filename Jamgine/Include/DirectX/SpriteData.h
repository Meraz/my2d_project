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
			float depth;
			Texture2D* texture;
			SpriteEffect spriteEffect;
			// rotation
			// origin pos


			SpriteData(Position p_position, float p_depth, Texture2D* p_texture, SpriteEffect p_spriteEffect)
			{
				position		= p_position;
				depth			= p_depth;
				texture			= p_texture;
				spriteEffect	= p_spriteEffect;
			}

			SpriteData(Position p_position, Texture2D* p_texture, SpriteEffect p_spriteEffect)
			{
				position		= p_position;
				depth			= STANDARD_SPRITE_DEPTH;
				texture			= p_texture;
				spriteEffect	= p_spriteEffect;
			}

			SpriteData(Position p_position, float p_depth, Texture2D* p_texture)
			{
				position		= p_position;
				depth			= p_depth;
				texture			= p_texture;
				spriteEffect	= SpriteEffect::FLIP_NONE;
			}

			SpriteData(Position p_position, Texture2D* p_texture)
			{
				position		= p_position;
				depth			= STANDARD_SPRITE_DEPTH;
				texture			= p_texture;
				spriteEffect	= SpriteEffect::FLIP_NONE;
			}
		};
	}	
}