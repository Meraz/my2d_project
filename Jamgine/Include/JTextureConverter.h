#pragma once

#include <Jamgine\Include\MemoryAllocator\MemoryAllocator.h>

namespace Jamgine
{
	class JTextureConverter
	{
	public:
		virtual void* Convert(void* p_data, unsigned int p_size, StackAllocator* p_stack) = 0;
	};
}