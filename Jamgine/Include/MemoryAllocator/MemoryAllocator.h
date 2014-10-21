#pragma once

#include "MemPool.h"
#include "SingleFrameStack.h"
#include "StackAllocator.h"

class MemoryAllocator
{
public:
	~MemoryAllocator();

	template <class T>
	MemPool<T>* CreatePool(unsigned int p_numBlocks, unsigned int p_alignment, bool p_shared) 
	{
		MemPool<T>* pool = new MemPool<T>(p_numBlocks, p_alignment, p_shared);
		return pool;
	}

	//Note: If you allocate more than some unknown high value, think INT_MAX~ish, you're gonna have a bad bad time
	SingleFrameStack* CreateSingleFrameStack(unsigned int p_stacksize, bool p_shared);

	StackAllocator* CreateStack(unsigned int p_stacksize, bool p_shared);

	static MemoryAllocator& GetMe() { static MemoryAllocator M; return M; }
private:
	MemoryAllocator(){};
	MemoryAllocator(MemoryAllocator const&);
	void operator=(MemoryAllocator const&);
};