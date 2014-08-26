#include <Jamgine/Include/DirectX/JDirectXTexture2DManager.h>
#include <Jamgine/Include/DirectX/JDirectXTexture2D.h>
#include <exception>

namespace Jamgine
{
	Texture2DManager* Texture2DManager::m_texture2DManager = nullptr;

		ErrorMessage Texture2DManager::CreateTexture2DManager(Texture2DManager** p_textureManager)
		{
			ErrorMessage l_errorMessage = J_OK;

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

		Texture2DManager::Texture2DManager()
		{
			//m_texture = std::map<char*,Texture2D*>();
		}	
		
		void Texture2DManager::Initialize(ID3D11Device* p_device)
		{
			m_device = p_device;
		}

		void Texture2DManager::ReleaseTexture2DManager()
		{
			//  Release map here
		}

		ErrorMessage Texture2DManager::GetTexture(Texture2DInterface** p_texture2D, std::string p_filePath)
		{
			ErrorMessage l_errorMessage = J_FAIL;
			try
			{
				if(m_texture[p_filePath] == nullptr)	// TODO, this code creates an entry in the map
				{
					m_texture[p_filePath] = new Texture2D();
					m_texture[p_filePath]->LoadTexture(m_device, p_filePath);
				}
				*p_texture2D = m_texture[p_filePath];
			}
			catch(std::exception e)
			{
				// Should remove the entry in the map
				return J_FAIL;
			}
			return J_OK;
		}	
}