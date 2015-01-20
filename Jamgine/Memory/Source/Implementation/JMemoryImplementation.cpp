#pragma once
#include <Jamgine/Memory/Include/Implementation/JMemoryImplementation.h>

namespace Jamgine {
	namespace Memory{

		JMemoryImplementation::JMemoryImplementation()
		{

		}
	
		JMemoryImplementation::~JMemoryImplementation()
		{

		}

		SingleFrameStack* JMemoryImplementation::CreateSingleFrameStack(unsigned int p_stacksize, bool p_shared)
		{
			return new SingleFrameStack(p_stacksize, p_shared);
		}

		StackAllocator* JMemoryImplementation::CreateStack(unsigned int p_stacksize, bool p_shared)
		{
			return new StackAllocator(p_stacksize, p_shared);
		}
	}
}