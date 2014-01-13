#pragma once

#if defined(_WINDLL)
	#define ROOTENGINE_DLL_EXPORT __declspec(dllexport)
#else
	#define ROOTENGINE_DLL_EXPORT __declspec(dllimport)
#endif

namespace Engine2D
{
	class EngineMain
	{
	public:
		EngineMain();
		~EngineMain();
		
		void Initialize();	
	};
}