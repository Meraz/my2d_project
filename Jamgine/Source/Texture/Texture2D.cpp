#include <Jamgine/Include/Texture/Texture2D.h>

namespace Jamgine
{
	Texture2D::Texture2D(ID3D11Device* p_device, std::string p_filePath) // SHOULD RETURN HRESULT OR SOMETHING
	{
		DirectX::CreateDDSTextureFromFile(p_device, L"Box_Texture.dds", (ID3D11Resource**)&m_texture2DBuffer , &m_texture2D_SRV); 
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