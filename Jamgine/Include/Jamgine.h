#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{
	struct Data_Send;
	class JCamera;
	class JResourceManager;

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

	private:
		static JamgineEngine* m_jamgineEngine;		
	
	protected:
	};
}