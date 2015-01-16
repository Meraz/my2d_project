#include <Jamgine/Render/Include/DirectX/JDirectXTexture2D.h>

namespace Jamgine
{
	namespace Render {
		JDirectXTexture2D::JDirectXTexture2D()
		{

		}

		JDirectXTexture2D::~JDirectXTexture2D()
		{

		}

		ErrorMessage JDirectXTexture2D::LoadTexture(ID3D11Device* p_device, std::string p_filePath)
		{
			HRESULT hr;
			std::wstring l_wstring = std::wstring(p_filePath.begin(), p_filePath.end()); // FAUL
			hr = DirectX::CreateDDSTextureFromFile(p_device, l_wstring.c_str(), (ID3D11Resource**)&m_texture2DBuffer, &m_texture2D_SRV);

			if (hr != S_OK)
			{
				return J_FAIL;
			}

			return J_OK;
		}

		ErrorMessage JDirectXTexture2D::LoadTexture(void* p_memory)
		{
			m_texture2D_SRV = static_cast<ID3D11ShaderResourceView*>(p_memory);
			return J_OK;	// TODO cannot always return J_OK
		}

		void* JDirectXTexture2D::GetRawData()
		{
			return nullptr; // Not implemented atm
		}

		ID3D11ShaderResourceView* JDirectXTexture2D::GetShaderResourceView()
		{
			return m_texture2D_SRV;
		}
	}
}