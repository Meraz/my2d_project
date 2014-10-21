#include <Jamgine\Include\MemoryAllocator\MemoryAllocator.h>

MemoryAllocator::~MemoryAllocator()
{

}


SingleFrameStack* MemoryAllocator::CreateSingleFrameStack(unsigned int p_stacksize, bool p_shared)
{
	return new SingleFrameStack(p_stacksize, p_shared);
}

StackAllocator* MemoryAllocator::CreateStack(unsigned int p_stacksize, bool p_shared)
{
	return new StackAllocator(p_stacksize, p_shared);
}

