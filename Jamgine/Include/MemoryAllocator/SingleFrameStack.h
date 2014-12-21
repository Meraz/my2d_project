#pragma once

//#include "Jamgine/Include/MemoryAllocator/StackAllocator.h"

#include <stdint.h>
#include <atomic>
#include <iostream>

class SingleFrameStack
{
private:
	size_t* m_start;
	size_t m_size;
	size_t* m_current;
	unsigned m_nonCustomMemFinder;
	unsigned int m_count;
	
public:	
	SingleFrameStack(unsigned int p_stacksize);

	virtual ~SingleFrameStack();

	void Wipe();

	template <class T>
	T* Push(unsigned p_alignment)
	{
		// First is always four, all others are 0
		if (m_count == 0)
			p_alignment = 4;
		else
			p_alignment = 0;

		if (p_alignment == 0)
		{
			T* returnblock = (T*)((size_t)m_current);
			int i = sizeof(T);
			i = i + (size_t)m_current;
			m_current = (size_t*)(i);
			m_count++;
			return returnblock;
		}
		else{
			size_t mask = p_alignment - 1;
			size_t misalignment = ((size_t)m_current & mask);
			size_t adjustment = p_alignment - misalignment;

			if (((size_t)m_current + (size_t)adjustment + sizeof(T)) >= ((size_t)m_start + (size_t)m_size))
			{
				return nullptr;
			}

			T* returnblock = (T*)((size_t)m_current + adjustment);

			int i = sizeof(T);
			char* metadata = (char*)((size_t)returnblock - 1);
			*metadata = static_cast<char>(adjustment);
			//Check end of stack

			i = i + (size_t)m_current;
			m_current = (size_t*)(i + adjustment);
			m_count++;
			return returnblock;
		}
	}
};
