#include "Jamgine\Include\MemoryAllocator\SingleFrameStack.h"
#include <stdlib.h>

SingleFrameStack::SingleFrameStack(unsigned p_stacksize)
{
	m_size = p_stacksize;
	m_start = (size_t*)malloc(p_stacksize);
	m_current = m_start;
	m_nonCustomMemFinder = 0;
	m_count = 0;
}


SingleFrameStack::~SingleFrameStack()
{
	//delete all
	free(m_start);
}

void SingleFrameStack::Wipe()
{
	m_nonCustomMemFinder = 0;
	m_current = m_start;
}
