#pragma once

#include <Jamgine/Include/Texture/Texture2D.h>

#include <Jamgine/Include/ErrorMessage.h>
#include <map>

namespace Jamgine
{
	class Texture2DManager
	{
	public:
		ErrorMessage LoadTexture(Texture2DInterface** p_texture2D, char* p_filePath);

	private:
		Texture2DManager();
//		virtual ~Texture2DManager();
		ID3D11Device* m_device;
		static ErrorMessage CreateTexture2DManager(Texture2DManager** p_textureManager);
		static void ReleaseTexture2DManager();
		static Texture2DManager* m_texture2DManager;

		std::map<char*,Texture2D*> m_texture;
		
		/*
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

			Hashmap som håller p_filePath som nyckel
			När man kör metoden LoadTexture så kollar den om texturen redan är inladdad.
			I så fall returneras en pekare till dne redan inladdade texturen
			annars så laddas texturen in och en pekare returneras till den nyinladdade texturen.
		*/


	};
}