#include <Jamgine\Include\JDXTextureConverter.h>

namespace Jamgine
{

	JDXTextureConverter::JDXTextureConverter(ID3D11Device* p_device)
	{
		m_device = p_device;
	}

	JDXTextureConverter::~JDXTextureConverter()
	{

	}


	void* JDXTextureConverter::Convert(void* p_data, unsigned int p_size)
	{
		ID3D11ShaderResourceView* SRV;
		DirectX::CreateDDSTextureFromMemory(m_device, (uint8_t*)p_data, p_size, nullptr /* We don't need this, hopefully....*/, &SRV);

		return SRV;
	}
}