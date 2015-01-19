#pragma once

#if defined(_WINDLL)
#define MEMORY_SUBSYSTEM __declspec(dllexport)
#else
#define MEMORY_SUBSYSTEM __declspec(dllimport)
#endif


namespace Jamgine
{
	namespace Memory
	{
		class JMemorySubsystem
		{		
		public:
			virtual void GetMemoryPool()

		};
	}
}


extern "C"
{
	typedef Jamgine::Memory::JMemorySubsystem* (*CREATEMEMORYSUBSYSTEM) (void);
	MEMORY_SUBSYSTEM Jamgine::Memory::JMemorySubsystem* CreateMemorySubsystem(void);
}