#pragma once
#include <Jamgine/Include/Shared.h>
#include <Jamgine/Include/Texture/Texture2DInterface.h>

namespace Jamgine
{
	namespace JDirectX
	{
		/*
		struct SpriteData
		{
			Point position;
			Point origin;
			Point textureOffset;
			Texture2DInterface* texture;
			SpriteEffect spriteEffect;
			float width;
			float height;
			float depth;
			float rotation;
			bool hasTransparent;
			Point textureDelta;
			
			SpriteData(
				Point p_position,
				Point p_origin,
				Point p_textureOffset,
				Texture2DInterface* p_texture,
				SpriteEffect p_spriteEffect,
				float p_width,
				float p_height,
				float p_depth,
				float p_rotation,
				bool p_hasTransparent,
				Point p_textureDelta
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
				hasTransparent = p_hasTransparent;
				textureDelta = p_textureDelta;
			}
			
			// Without flip
			SpriteData
				(
				Point p_position,
				Point p_origin,
				Point p_textureOffset,
				Texture2DInterface* p_texture,
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
				hasTransparent = false;
				textureDelta = Point(1,1);
			}

			// without flip and origin
			SpriteData(
				Point p_position,
				Point p_textureOffset,
				Texture2DInterface* p_texture,
				float p_width,
				float p_height,
				float p_depth
				)
			{
				position = p_position;
				origin	= Point(0,0);
				textureOffset = p_textureOffset;
				texture = p_texture;
				spriteEffect =	SpriteEffect::FLIP_NONE;
				width = p_width;
				height = p_height;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
				textureDelta = Point(1,1);
			}

			// Without origin and rotation
			SpriteData(
				Point p_position,
				Point p_textureOffset,
				Texture2DInterface* p_texture,
				SpriteEffect p_spriteEffect,
				float p_width,
				float p_height,
				float p_depth
				)
			{
				position = p_position;
				origin	= Point(0,0);
				textureOffset = p_textureOffset;
				texture = p_texture;
				spriteEffect =	p_spriteEffect;
				width = p_width;
				height = p_height;
				depth = p_depth;
				rotation = 0;
				hasTransparent = false;
				textureDelta = Point(1,1);
			}
		};
		*/
	}	
}