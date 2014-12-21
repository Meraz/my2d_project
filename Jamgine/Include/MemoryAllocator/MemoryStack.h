#pragma once

#include <stdint.h>
#include <atomic>
#include <iostream>

typedef size_t* Marker;

namespace
{
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
}
class MemoryStack
{
private:
	size_t* m_start;
	size_t m_size;
	size_t* m_current;
	Marker m_currentMarker;
	unsigned m_nonCustomMemFinder;

public:	
	MemoryStack(unsigned int p_stacksize);

	~MemoryStack();

	void Wipe();

	template <class T>
	T* Push(size_t p_size,unsigned p_alignment)
	{			
		size_t mask = p_alignment - 1;
		size_t misalignment = ((size_t)m_current & mask);
		size_t adjustment = p_alignment - misalignment;

			
		if(((size_t)m_current + (size_t)adjustment + p_size) >= ((size_t)m_start + (size_t)m_size))
		{
			return nullptr;
		}

		T* returnblock = (T*)((size_t)m_current + adjustment);
		
		int i = p_size;
		int j = m_size;
		char* metadata = (char*)((size_t)returnblock-1);
		*metadata = static_cast<char>(adjustment);
		//Check end of stack
		
		i = i + (size_t)m_current;
		m_current = (size_t*)(i + adjustment);
		return returnblock; 
	}	

	bool Free(Marker p_marker);

	Marker GetMarker();

};
