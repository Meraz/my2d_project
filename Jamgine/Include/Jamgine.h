#pragma once
#include <Jamgine\Include\Shared.h>


/*

HINSTANCE	m_instance;
HWND		m_handle;
LRESULT CALLBACK m_messageProcces(HWND, UINT, WPARAM, LPARAM);


*/

namespace Jamgine
{
	struct Data_Send;

	class JamgineEngine
	{
		
	public:		
		static ErrorMessage CreateEngine(JamgineEngine** p_jamgineEngine, GraphicalSystem::GraphicalSystem p_graphicalSystem);
		static ErrorMessage ReleaseEngine(); 
		
		virtual ErrorMessage Initialize(void* p_data) = 0;
		virtual ErrorMessage Initialize(Jamgine::Data_Send p_data) = 0;


		virtual void Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect) = 0;
		virtual void PostRender() = 0;


	/*template<typename T> void Safe_Delete(T*& a) 
	{
		delete a;
		a = nullptr;
	}*/
	
	private:
		static JamgineEngine* m_jamgineEngine;		
	
	protected:
	};
}