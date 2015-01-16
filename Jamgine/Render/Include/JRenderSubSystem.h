#pragma once

/*
*	Jamgine general includes
*/
#include <Jamgine/Include/Rectangle.h>
#include <Jamgine/Include/JFloat2.h>
#include <Jamgine/Include/ErrorMessage.h>

/*
*	Subsystem includes
*/
#include <Jamgine/Render/Include/Texture2D.h>
#include <Jamgine/Render/Include/Spritedata.h>

namespace Jamgine
{
	namespace Render
	{
		struct Data_Send;	// TODO rename

		class JRenderSubsystem
		{		
		public:
			// As long as the data is packed correctly it can be sent as a void*. This has the benefit of skipping one include file.
			virtual ErrorMessage Initialize(void* p_data) = 0;
			
			// If Jamgine/Include/'API'Shared has been included, a definition of the struct exists.
			virtual ErrorMessage Initialize(Data_Send p_data) = 0;

			// Because of a map, a texture will actually only be loaded once and the same pointer will be returned.
			virtual ErrorMessage LoadTexture(Texture2D** p_texture, char* p_filePath) = 0;

			virtual	void Render(Rectangle p_rectangle, Texture2D* p_texture) = 0;
			virtual	void Render(Rectangle p_rectangle, Texture2D* p_texture, float p_depth) = 0;
			virtual	void Render(JFloat2 p_position, float p_width, float p_height, Texture2D* p_texture) = 0;
			virtual	void Render(JFloat2 p_position, float p_width, float p_height, Texture2D* p_texture, float p_depth) = 0;

			// Render with a pre-filled SpriteData struct
			virtual void Render(SpriteData p_spriteData) = 0;

			// This function is called once per draw, this call actually renders the sprites to the backbuffer.
			virtual void PostRender() = 0;
		};
	}
}