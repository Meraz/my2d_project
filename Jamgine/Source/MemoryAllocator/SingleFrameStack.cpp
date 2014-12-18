#include "Jamgine\Include\MemoryAllocator\SingleFrameStack.h"
#include <stdlib.h>


SingleFrameStack::SingleFrameStack(unsigned p_stacksize, bool p_shared)
{
	m_size = p_stacksize;
	m_start = (size_t*)malloc(p_stacksize);
	m_current = m_start;
	m_nonCustomMemFinder = 0;
	m_lock.clear();
	m_shared = p_shared;
}


SingleFrameStack::~SingleFrameStack()
{
	//delete all
	free(m_start);
}

void SingleFrameStack::Wipe()
{
	while( m_shared && m_lock.test_and_set(std::memory_order_acquire))
	{
		//Keep on spinning in the free world
	}
	m_nonCustomMemFinder = 0;
	m_lock.clear();
	m_current = m_start;
}
