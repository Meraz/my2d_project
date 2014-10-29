#pragma once
#include "DDSTextureLoader\DDSTextureLoader.h"
#include "Jamgine\Include\JTextureConverter.h"
#include <d3d11_1.h>
#include <atomic>
namespace Jamgine
{
	class JDXTextureConverter : public JTextureConverter
	{
	public:
		JDXTextureConverter(ID3D11Device* p_device);
		~JDXTextureConverter();

		void* Convert(void* p_data, unsigned int p_size, StackAllocator* p_stack) override;
	private:
		ID3D11Device* m_device;
		std::atomic_flag m_lock;
	};
}