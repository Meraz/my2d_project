#pragma once

#include <Jamgine/Include/Shared/Rectangle.h>
#include <Jamgine/Include/Shared/SpriteEffect.h>
#include <Jamgine/Include/Texture2DInterface.h>

namespace Jamgine
{
	#define STANDARD_SPRITE_DEPTH 0.5f
	struct SpriteData
	{
		Rectangle rectangle;
		Point origin;
		Rectangle subTexture;
		Texture2DInterface* texture;
		SpriteEffect spriteEffect;
		float depth;
		float rotation;
		bool hasTransparent;

		// All variables, but no rectangle
		SpriteData(
			Point p_position,
			float p_width,
			float p_height,
			Point p_origin,
			Rectangle p_subTexture,
			Texture2DInterface* p_texture,
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
			Point p_origin,
			Rectangle p_subTexture,
			Texture2DInterface* p_texture,
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
			Point p_position,
			float p_width,
			float p_height,
			Point p_origin,
			Rectangle p_subTexture,
			Texture2DInterface* p_texture,
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
			Point p_origin,
			Rectangle p_subTexture,
			Texture2DInterface* p_texture,
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
			Point p_position,
			float p_width,
			float p_height,
			Rectangle p_subTexture,
			Texture2DInterface* p_texture,
			float p_depth
			)
		{
			rectangle = Rectangle(p_position, p_width, p_height);
			origin = Point(0, 0);
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
			Texture2DInterface* p_texture,
			float p_depth
			)
		{
			rectangle = p_rectangle;
			origin = Point(0, 0);
			subTexture = p_subTexture;
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = p_depth;
			rotation = 0;
			hasTransparent = false;
		}
		
		// Without origin and rotation, without rectangle
		SpriteData(
			Point p_position,
			float p_width,
			float p_height,
			Rectangle p_subTexture,
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_depth
			)
		{
			rectangle = Rectangle(p_position, p_width, p_height);
			origin = Point(0, 0);
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
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_depth
			)
		{
			rectangle = p_rectangle;
			origin = Point(0, 0);
			subTexture = p_subTexture;
			texture = p_texture;
			spriteEffect = p_spriteEffect;
			depth = p_depth;
			rotation = 0;
			hasTransparent = false;
		}

		// As small as possible, but no rectangle
		SpriteData(
			Point p_position,
			float p_width,
			float p_height,
			Texture2DInterface* p_texture
			)
		{
			rectangle = Rectangle(p_position, p_width, p_height);
			origin = Point(0, 0);
			subTexture = Rectangle(rectangle);
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = STANDARD_SPRITE_DEPTH;
			rotation = 0;
			hasTransparent = false;
		}

	// As small as possible, but no rectangle
		SpriteData(
			Rectangle p_rectangle,
			Texture2DInterface* p_texture
			)
		{
			rectangle = p_rectangle;
			origin = Point(0, 0);
			subTexture = Rectangle(rectangle);
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = STANDARD_SPRITE_DEPTH;
			rotation = 0;
			hasTransparent = false;
		}
		

			// As small as possible with depth, but no rectangle
			SpriteData(
				Point p_position,
				float p_width,
				float p_height,
				Texture2DInterface* p_texture,
				float p_depth
				)
			{
				rectangle = Rectangle(p_position, p_width, p_height);
				origin = Point(0, 0);
				subTexture = Rectangle(rectangle);
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}

			// As small as possible with depth, but no rectangle
			SpriteData(
				Rectangle p_rectangle,
				Texture2DInterface* p_texture,
				float p_depth
				)
			{
				rectangle = p_rectangle;
				origin = Point(0, 0);
				subTexture = Rectangle(rectangle);
				texture = p_texture;
				spriteEffect = SpriteEffect::FLIP_NONE;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
			}
	};
}