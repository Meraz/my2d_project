#pragma once
#include <Jamgine/Include/Shared.h>
#include <Jamgine/Include/Texture/Texture2DInterface.h>

namespace Jamgine
{
	struct Data_Send;

	class JamgineEngine
	{
		
	public:
		// This engine is a singleton, only one instance can be created. If you wish to change 3D API, you'll have to Release the current engine and Create it with new flags.
		static ErrorMessage CreateEngine(JamgineEngine** p_jamgineEngine, GraphicalSystem p_graphicalSystem);
		static ErrorMessage ReleaseEngine(); 
		
		// As long as the data is packed correctly it can be sent as a void*. This has the benefit of skipping one include file.
		virtual ErrorMessage Initialize(void* p_data) = 0;
		
		// If Jamgine/Include/'API'Shared has been included, a definition of the struct exists.
		virtual ErrorMessage Initialize(Jamgine::Data_Send p_data) = 0;

		// Because of a map, a texture will actually only be loaded once and the same pointer will be returned.
		virtual ErrorMessage LoadTexture(Texture2DInterface** p_texture2DInterface, char* p_filePath) = 0;

		//virtual void PreRender() = 0;
		virtual void Render(Position p_position, Texture2DInterface* p_textureInterface, SpriteEffect p_spriteEffect) = 0;
		virtual void PostRender() = 0;

	private:
		static JamgineEngine* m_jamgineEngine;		
	
	protected:
	};
}