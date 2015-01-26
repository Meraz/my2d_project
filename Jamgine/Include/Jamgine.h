#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{
	struct Data_Send;

	class JamgineEngine
	{
		
	public:
		// This engine is a singleton, only one instance can be created.
		static ErrorMessage CreateEngine(JamgineEngine** p_jamgineEngine, Subsystem p_subsystems, GraphicalSystem p_graphicalSystem);
		static ErrorMessage ReleaseEngine(); 
				
		// If Jamgine/Include/'API'Shared has been included, a definition of the struct exists.
		virtual ErrorMessage Initialize(Data_Send p_data) = 0;

	private:
		static JamgineEngine* m_jamgineEngine;		
	
	protected:
	};
}