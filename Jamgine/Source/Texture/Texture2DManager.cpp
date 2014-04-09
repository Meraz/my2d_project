#include <Jamgine/Include/Texture/Texture2DManager.h>
#include <Jamgine/Include/Texture/Texture2D.h>

namespace Jamgine
{
	Texture2DManager* Texture2DManager::m_texture2DManager = nullptr;

		ErrorMessage Texture2DManager::CreateTexture2DManager(Texture2DManager** p_textureManager)
		{
			ErrorMessage l_errorMessage = J_FAIL;

			if(m_texture2DManager == nullptr)
			{
				try{
					m_texture2DManager = new Texture2DManager();
				}
				catch(std::exception e)
				{
					return l_errorMessage = J_FAIL;
				}
				*p_textureManager = m_texture2DManager;
			}

			*p_textureManager = m_texture2DManager;

			return l_errorMessage;
		}

		void Texture2DManager::ReleaseTexture2DManager()
		{
			//  Release map here
		}

		ErrorMessage Texture2DManager::LoadTexture(Texture2DInterface** p_texture2D, char* p_filePath)
		{
			ErrorMessage l_errorMessage = J_FAIL;

			if(m_texture[p_filePath] == nullptr)
				m_texture[p_filePath] = new Texture2D(m_device, p_filePath); // I AM HERE

			return J_FAIL;
		}

		Texture2DManager::Texture2DManager()
		{
			//m_texture = std::map<char*,Texture2D*>();
		}		
}