#include "engine\Include\SingleFrameStack.h"
#include <stdlib.h>


SingleFrameStack::SingleFrameStack(unsigned p_stacksize, bool p_shared, bool p_custom)
{
	m_size = p_stacksize;
	if(p_custom)
		m_start = (size_t*)malloc(p_stacksize);
	m_current = m_start;
	m_nonCustomMemFinder = 0;
	m_lock.clear();
	m_shared = p_shared;
	m_custom = p_custom;
	m_currentMarker = m_current;
}


SingleFrameStack::~SingleFrameStack()
{
	//delete all
	if(m_custom)
		free(m_start);
}

