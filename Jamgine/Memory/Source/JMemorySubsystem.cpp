#include <Jamgine/Memory/Include/JMemorySubsystem.h>
#include <Jamgine/Memory/Include/Implementation/JMemoryImplementation.h>

Jamgine::Memory::JMemorySubsystem* CreateMemorySubsystem(void)
{
	return new Jamgine::Memory::JMemoryImplementation;
}