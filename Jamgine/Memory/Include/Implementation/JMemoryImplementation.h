#pragma once

#include <Jamgine/Memory/Include/JMemorySubsystem.h>

namespace Jamgine
{
	namespace Memory
	{
		class JMemoryImplementation : public JMemorySubsystem
		{
		public:
			JMemoryImplementation();
			virtual ~JMemoryImplementation();
			virtual SingleFrameStack* CreateSingleFrameStack(unsigned int p_stacksize, bool p_shared) override;
			virtual StackAllocator* CreateStack(unsigned int p_stacksize, bool p_shared) override;
		};
	}
}