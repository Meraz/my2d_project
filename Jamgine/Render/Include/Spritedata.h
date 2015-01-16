#pragma once

/*
*	Jamgine general includes
*/
#include <Jamgine/Include/Rectangle.h>

/*
*	Render subsystem 
*/
#include <Jamgine/Render/Include/SpriteEffect.h>
#include <Jamgine/Render/Include/Texture2D.h>

namespace Jamgine
{
	namespace Render
	{
		#define STANDARD_SPRITE_DEPTH 0.5f
		struct SpriteData
		{
			Rectangle rectangle;
			JFloat2 origin;
			Rectangle subTexture;
			Texture2D* texture;
			SpriteEffect spriteEffect;
			float depth;
			float rotation;
			bool hasTransparent;

			// All variables, but no rectangle
			SpriteData(
				JFloat2 p_position,
				float p_width,
				float p_height,
				JFloat2 p_origin,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				SpriteEffect p_spriteEffect,
				float p_depth,
				float p_rotation,
				bool p_hasTransparent
				)
			{
				rectangle = Rectangle(p_position, p_width, p_height);
				origin = p_origin;
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = p_spriteEffect;
				depth = p_depth;
				rotation = p_rotation;
				hasTransparent = p_hasTransparent;
			}

			// All variables, with rectangle
			SpriteData(
				Rectangle p_rectangle,
				JFloat2 p_origin,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				SpriteEffect p_spriteEffect,
				float p_depth,
				float p_rotation,
				bool p_hasTransparent
				)
			{
				rectangle = p_rectangle;
				origin = p_origin;
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = p_spriteEffect;
				depth = p_depth;
				rotation = p_rotation;
				hasTransparent = p_hasTransparent;
			}

			// Without flip or transparant, without rectangle
			SpriteData
				(
				JFloat2 p_position,
				float p_width,
				float p_height,
				JFloat2 p_origin,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				float p_depth,
				float p_rotation)
			{
				rectangle = Rectangle(p_position, p_width, p_height);
				origin = p_origin;
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = p_rotation;
				hasTransparent = false;
			}

			// Without flip or transparant, with rectangle
			SpriteData
				(
				Rectangle p_rectangle, 
				JFloat2 p_origin,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				float p_depth,
				float p_rotation)
			{
				rectangle = p_rectangle;
				origin = p_origin;
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = p_rotation;
				hasTransparent = false;
			}

			// without flip and origin, without rectangle
			SpriteData(
				JFloat2 p_position,
				float p_width,
				float p_height,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				float p_depth
				)
			{
				rectangle = Rectangle(p_position, p_width, p_height);
				origin = JFloat2(0.0f, 0.0f);
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}

			// without flip and origin, with rectangle
			SpriteData(
				Rectangle p_rectangle,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				float p_depth
				)
			{
				rectangle = p_rectangle;
				origin = JFloat2(0.0f, 0.0f);
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}
			
			// Without origin and rotation, without rectangle
			SpriteData(
				JFloat2 p_position,
				float p_width,
				float p_height,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				SpriteEffect p_spriteEffect,
				float p_depth
				)
			{
				rectangle = Rectangle(p_position, p_width, p_height);
				origin = JFloat2(0, 0);
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = p_spriteEffect;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}

			// Without origin and rotation, with rectangle
			SpriteData(
				Rectangle p_rectangle,
				Rectangle p_subTexture,
				Texture2D* p_texture,
				SpriteEffect p_spriteEffect,
				float p_depth
				)
			{
				rectangle = p_rectangle;
				origin = JFloat2();
				subTexture = p_subTexture;
				texture = p_texture;
				spriteEffect = p_spriteEffect;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}

			// As small as possible, but no rectangle
			SpriteData(
				JFloat2 p_position,
				float p_width,
				float p_height,
				Texture2D* p_texture
				)
			{
				rectangle = Rectangle(p_position, p_width, p_height);
				origin = JFloat2();
				subTexture = Rectangle(0.0f, 0.0f, 1.0f, 1.0f);
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = STANDARD_SPRITE_DEPTH;
				rotation = 0;
				hasTransparent = false;
			}

			// As small as possible, but no rectangle
			SpriteData(
				Rectangle p_rectangle,
				Texture2D* p_texture
				)
			{
				rectangle = p_rectangle;
				origin = JFloat2();
				subTexture = Rectangle(0.0f, 0.0f, 1.0f, 1.0f);
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = STANDARD_SPRITE_DEPTH;
				rotation = 0;
				hasTransparent = false;
			}
			
			// As small as possible with depth, but no rectangle
			SpriteData(
				JFloat2 p_position,
				float p_width,
				float p_height,
				Texture2D* p_texture,
				float p_depth
				)
			{
				rectangle = Rectangle(p_position, p_width, p_height);
				origin = JFloat2();
				subTexture = Rectangle(0.0f, 0.0f, 1.0f, 1.0f);
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}

			// As small as possible with depth, but no rectangle
			SpriteData(
				Rectangle p_rectangle,
				Texture2D* p_texture,
				float p_depth
				)
			{
				rectangle = p_rectangle;
				origin = JFloat2();
				subTexture = Rectangle(0.0f, 0.0f, 1.0f, 1.0f);	// Entire texture
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}
		};
	}
}