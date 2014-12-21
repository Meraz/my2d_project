#include "Jamgine/Include/MemoryAllocator/MemoryStack.h"
#include <stdlib.h>


MemoryStack::MemoryStack(unsigned p_stacksize)
{
	m_size = p_stacksize;
	m_start = (size_t*)malloc(p_stacksize);
	m_current = m_start;
	m_nonCustomMemFinder = 0;
	m_currentMarker = m_current;
}

MemoryStack::~MemoryStack()
{
	//delete all
	free(m_start);
}

bool MemoryStack::Free(Marker p_marker)
{
	if (p_marker > m_current)
		return false;
	else
		m_current = p_marker;
	return true;
}

Marker MemoryStack::GetMarker()
{
	m_currentMarker = m_current;

	return m_currentMarker;
}

void MemoryStack::Wipe()
{
	m_nonCustomMemFinder = 0;
	
	m_current = m_start;
}