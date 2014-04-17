#include <Jamgine/Include/Texture/Texture2D.h>

namespace Jamgine
{
	Texture2D::Texture2D()
	{
		
	}

	ErrorMessage Texture2D::LoadTexture(ID3D11Device* p_device, std::string p_filePath)
	{
		HRESULT hr;
		std::wstring l_wstring = std::wstring(p_filePath.begin(), p_filePath.end()); // FAUL
		hr = DirectX::CreateDDSTextureFromFile(p_device, l_wstring.c_str(), (ID3D11Resource**)&m_texture2DBuffer, &m_texture2D_SRV);
			
		if(hr != S_OK)
		{
			return J_FAIL;
		}

		return J_OK;
	}

	Texture2D::~Texture2D()
	{

	}	

	void* Texture2D::GetRawData()
	{
		return nullptr; // Not implemented atm
	}

	ID3D11ShaderResourceView* Texture2D::GetShaderResourceView()
	{
		return m_texture2D_SRV;
	}
}