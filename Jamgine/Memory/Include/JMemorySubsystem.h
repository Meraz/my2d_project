#pragma once

#if defined(_WINDLL)
#define MEMORY_SUBSYSTEM __declspec(dllexport)
#else
#define MEMORY_SUBSYSTEM __declspec(dllimport)
#endif

#include <Jamgine/Memory/Include/SingleFrameStack.h>
#include <Jamgine/Memory/Include/StackAllocator.h>
#include <Jamgine/Memory/Include/MemPool.h>

namespace Jamgine
{
	namespace Memory
	{
		class SingleFrameStack;

		class JMemorySubsystem 
		{		
		public:

			/* Note here please */
			template <class T>
			MemPool<T>* CreatePool(unsigned int p_numBlocks, unsigned int p_alignment, bool p_shared)
			{
				MemPool<T>* pool = new MemPool<T>(p_numBlocks, p_alignment, p_shared);
				return pool;
			}

			/* Note: If you allocate more than some unknown high value, think INT_MAX~ish, you're gonna have a bad bad time */
			virtual SingleFrameStack* CreateSingleFrameStack(unsigned int p_stacksize, bool p_shared) = 0;

			/* Note here please*/ // TODO
			virtual StackAllocator* CreateStack(unsigned int p_stacksize, bool p_shared) = 0;
		};
	}
}


extern "C"
{
	typedef Jamgine::Memory::JMemorySubsystem* (*CREATEMEMORYSUBSYSTEM) (void);
	MEMORY_SUBSYSTEM Jamgine::Memory::JMemorySubsystem* CreateMemorySubsystem(void);
}