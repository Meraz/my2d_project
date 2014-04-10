#pragma once
#include <Jamgine/Include/Shared.h>
#include <Jamgine/Include/Texture/Texture2DInterface.h>

namespace Jamgine
{
	namespace DirectX
	{
		struct SpriteData
		{
			Position position;
			float depth;
			Texture2DInterface* texture;
			SpriteEffect spriteEffect;
			// rotation
			// origin pos
			
			SpriteData(Position p_position, float p_depth, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect)
			{
				position		= p_position;
				depth			= p_depth;
				texture			= p_texture;
				spriteEffect	= p_spriteEffect;
			}

			SpriteData(Position p_position, Texture2DInterface* p_texture, SpriteEffect p_spriteEffect)
			{
				position		= p_position;
				depth			= STANDARD_SPRITE_DEPTH;
				texture			= p_texture;
				spriteEffect	= p_spriteEffect;
			}

			SpriteData(Position p_position, float p_depth, Texture2DInterface* p_texture)
			{
				position		= p_position;
				depth			= p_depth;
				texture			= p_texture;
				spriteEffect	= SpriteEffect::NONE;
			}

			SpriteData(Position p_position, Texture2DInterface* p_texture)
			{
				position		= p_position;
				depth			= STANDARD_SPRITE_DEPTH;
				texture			= p_texture;
				spriteEffect	= SpriteEffect::NONE;
			}
		};
	}	
}