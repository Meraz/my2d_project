#include "Jamgine.h"
#include <Jamgine\Include\DirectXEngine.h>

//#include <stdexception>

namespace Jamgine
{
	JamgineEngine* JamgineEngine::m_jamgineEngine = nullptr;

	ErrorMessage::ErrorMessage JamgineEngine::CreateEngine(JamgineEngine** p_jamgineEngine, GraphicalSystem::GraphicalSystem p_graphicalSystem)
	{
		ErrorMessage::ErrorMessage l_errorMessage = ErrorMessage::OK;
		
		if(m_jamgineEngine == nullptr)
		{		
			if(p_graphicalSystem == GraphicalSystem::DIRECTX)
			{
				try{
					m_jamgineEngine = new DirectX::DirectXEngine();
				}
				catch(std::exception e)
				{
					l_errorMessage = ErrorMessage::FAILED;
				}
			}
			else if(p_graphicalSystem == GraphicalSystem::OPENGL)
			try{
					//m_jamgineEngine = new OpenGLEngine();
				}
				catch(std::exception e)
				{
					l_errorMessage = ErrorMessage::FAILED;
				}
		}
		*p_jamgineEngine = m_jamgineEngine;
		return l_errorMessage;
	}

	ErrorMessage::ErrorMessage JamgineEngine::ReleaseEngine()
	{
		ErrorMessage::ErrorMessage l_errorMessage = ErrorMessage::OK;
		if(m_jamgineEngine == nullptr)
			l_errorMessage = ErrorMessage::FAILED; 
		//else
		//{
		//	try
		//	{
		//	//	m_jamgineEngine->Safe_Delete(m_jamgineEngine);
		//	}
		//	catch(std::exception e)
		//	{
		//		l_errorMessage = ErrorMessage::FAILED; 
		//	}
		//}
		return l_errorMessage;
	}	
}