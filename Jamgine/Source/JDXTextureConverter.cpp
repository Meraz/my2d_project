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
		ID3D11Resource* testRes;
		SRV = (ID3D11ShaderResourceView*)p_stack->Push<void>(p_size, 4);

		HRESULT re = DirectX::CreateDDSTextureFromMemory(m_device, static_cast<uint8_t*>(p_data), p_size, &testRes /* We don't need this, hopefully....*/, &SRV);

		return SRV;
	}

}