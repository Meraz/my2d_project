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


	void* JDXTextureConverter::Convert(void* p_data, unsigned int p_size, StackAllocator* p_stack)
	{
		ID3D11ShaderResourceView* SRV;

		SRV = p_stack->Push<ID3D11ShaderResourceView>(sizeof(ID3D11ShaderResourceView), 4);

		DirectX::CreateDDSTextureFromMemory(m_device, (uint8_t*)p_data, p_size, nullptr /* We don't need this, hopefully....*/, &SRV);

		return SRV;
	}
}