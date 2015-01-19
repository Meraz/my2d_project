#pragma once

#if defined(_WINDLL)
#define RENDER_SUBSYSTEM __declspec(dllexport)
#else
#define RENDER_SUBSYSTEM __declspec(dllimport)
#endif

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

extern "C"
{
	typedef Jamgine::Render::JRenderSubsystem* (*CREATERENDERSUBSYSTEM) (void);
	RENDER_SUBSYSTEM Jamgine::Render::JRenderSubsystem* CreateRenderSubsystem(void);
}