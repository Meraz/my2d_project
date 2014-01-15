#pragma once
#include <Jamgine\Include\Shared.h>

//#pragma comment(lib, "DirectX.lib")

namespace Jamgine
{


	class JamgineEngine
	{
	public:		
		virtual void Render() = 0;

	static ErrorMessage::ErrorMessage CreateEngine(JamgineEngine** p_jamgineEngine, GraphicalSystem::GraphicalSystem p_graphicalSystem);
	static ErrorMessage::ErrorMessage ReleaseEngine();
	static JamgineEngine* m_jamgineEngine;

	/*template<typename T> void Safe_Delete(T*& a) 
	{
		delete a;
		a = nullptr;
	}*/
	
	private:
		
	
	protected:
		//	virtual EngineMain() = 0;
	//	virtual ~EngineMain() = 0;
	};
	//static JamgineEngine* m_jamgineEngine = nullptr;

}