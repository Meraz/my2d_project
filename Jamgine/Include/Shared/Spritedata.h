#pragma once

#include <Jamgine/Include/Shared/Rectangle.h>
#include <Jamgine/Include/Shared/SpriteEffect.h>
#include <Jamgine/Include/Texture/Texture2DInterface.h>

namespace Jamgine
{
	#define STANDARD_SPRITE_DEPTH 0.5f
	struct SpriteData
	{
		Rectangle rectangle;
		Point origin;
		Point textureOffset;
		Texture2DInterface* texture;
		SpriteEffect spriteEffect;
		float depth;
		float rotation;
		bool hasTransparent;
		Point textureDelta;

		// All variables, but no rectangle
		SpriteData(
			Point p_position,
			float p_width,
			float p_height,
			Point p_origin,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_depth,
			float p_rotation,
			bool p_hasTransparent,
			Point p_textureDelta
			)
		{
			rectangle = Rectangle(p_position, p_width, p_height);
			origin = p_origin;
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = p_spriteEffect;
			depth = p_depth;
			rotation = p_rotation;
			hasTransparent = p_hasTransparent;
			textureDelta = p_textureDelta;
		}

		// All variables, with rectangle
		SpriteData(
			Rectangle p_rectangle,
			Point p_origin,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_depth,
			float p_rotation,
			bool p_hasTransparent,
			Point p_textureDelta
			)
		{
			rectangle = p_rectangle;
			origin = p_origin;
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = p_spriteEffect;
			depth = p_depth;
			rotation = p_rotation;
			hasTransparent = p_hasTransparent;
			textureDelta = p_textureDelta;
		}

		// Without flip, without rectangle
		SpriteData
			(
			Point p_position,
			float p_width,
			float p_height,
			Point p_origin,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			float p_depth,
			float p_rotation)
		{
			rectangle = Rectangle(p_position, p_width, p_height);
			origin = p_origin;
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = p_depth;
			rotation = p_rotation;
			hasTransparent = false;
			textureDelta = Point(1, 1);
		}

		// Without flip, with rectangle
		SpriteData
			(
			Rectangle p_rectangle, 
			Point p_origin,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			float p_depth,
			float p_rotation)
		{
			rectangle = p_rectangle;
			origin = p_origin;
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = p_depth;
			rotation = p_rotation;
			hasTransparent = false;
			textureDelta = Point(1, 1);
		}

		// without flip and origin, without rectangle
		SpriteData(
			Point p_position,
			float p_width,
			float p_height,
			Point p_textureOffset,
			Texture2DInterface* p_texture,

			float p_depth
			)
		{
			rectangle = Rectangle(p_position, p_width, p_height);
			origin = Point(0, 0);
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = p_depth;
			rotation = 0;
			hasTransparent = false;
			textureDelta = Point(1, 1);
		}

		// without flip and origin, with rectangle
		SpriteData(
			Rectangle p_rectangle,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			float p_depth
			)
		{
			rectangle = p_rectangle;
			origin = Point(0, 0);
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = p_depth;
			rotation = 0;
			hasTransparent = false;
			textureDelta = Point(1, 1);
		}
		
		// Without origin and rotation, without rectangle
		SpriteData(
			Point p_position,
			float p_width,
			float p_height,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_depth
			)
		{
			rectangle = Rectangle(p_position, p_width, p_height);
			origin = Point(0, 0);
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = p_spriteEffect;
			depth = p_depth;
			rotation = 0;
			hasTransparent = false;
			textureDelta = Point(1, 1);
		}

		// Without origin and rotation, with rectangle
		SpriteData(
			Rectangle p_rectangle,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_depth
			)
		{
			rectangle = p_rectangle;
			origin = Point(0, 0);
			textureOffset = p_textureOffset;
			texture = p_texture;
			spriteEffect = p_spriteEffect;
			depth = p_depth;
			rotation = 0;
			hasTransparent = false;
			textureDelta = Point(1, 1);
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
			textureOffset = Point(0, 0);
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = STANDARD_SPRITE_DEPTH;
			rotation = 0;
			hasTransparent = false;
			textureDelta = Point(1, 1);
		}

	// As small as possible, but no rectangle
		SpriteData(
			Rectangle p_rectangle,
			Texture2DInterface* p_texture
			)
		{
			rectangle = p_rectangle;
			origin = Point(0, 0);
			textureOffset = Point(0, 0);
			texture = p_texture;
			spriteEffect = SpriteEffect::FLIP_NONE;
			depth = STANDARD_SPRITE_DEPTH;
			rotation = 0;
			hasTransparent = false;
			textureDelta = Point(1, 1);
		}
	};
}