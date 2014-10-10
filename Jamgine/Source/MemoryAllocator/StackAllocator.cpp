#include "Jamgine\Include\MemoryAllocator\StackAllocator.h"
#include <stdlib.h>


StackAllocator::StackAllocator(unsigned p_stacksize, bool p_shared)
{
	m_size = p_stacksize;
	m_start = (size_t*)malloc(p_stacksize);
	m_current = m_start;
	m_nonCustomMemFinder = 0;
	m_lock.clear();
	m_shared = p_shared;
	m_currentMarker = m_current;

}


StackAllocator::~StackAllocator()
{
	//delete all
	free(m_start);
}

bool StackAllocator::Free(Marker p_marker)
{
	if (p_marker > m_current)
		return false;
	else
		m_current = p_marker;
	return true;
}

Marker StackAllocator::GetMarker()
{
	m_currentMarker = m_current;

	return m_currentMarker;
}