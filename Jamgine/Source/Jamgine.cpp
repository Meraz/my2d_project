#include <Jamgine/Include/Jamgine.h>
#include <Jamgine/Include/DirectX/DirectXEngine.h>
#include <exception>

namespace Jamgine
{
	JamgineEngine* JamgineEngine::m_jamgineEngine = nullptr;

	ErrorMessage JamgineEngine::CreateEngine(JamgineEngine** p_jamgineEngine, GraphicalSystem::GraphicalSystem p_graphicalSystem)
	{
		ErrorMessage l_errorMessage = J_OK;
		
		if(m_jamgineEngine == nullptr)
		{		
			if(p_graphicalSystem == GraphicalSystem::DIRECTX)
			{
				try{
					m_jamgineEngine = new DirectX::DirectXEngine();
				}
				catch(std::exception e)
				{
					l_errorMessage = J_FAIL;
				}
			}
			else if(p_graphicalSystem == GraphicalSystem::OPENGL)
			try{
					//m_jamgineEngine = new OpenGLEngine();
				}
				catch(std::exception e)
				{
					l_errorMessage = J_FAIL;
				}
		}
		*p_jamgineEngine = m_jamgineEngine;
		return l_errorMessage;
	}

	ErrorMessage JamgineEngine::ReleaseEngine()
	{
		ErrorMessage l_errorMessage = J_OK;
		if(m_jamgineEngine == nullptr)
			l_errorMessage = J_FAIL; 
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