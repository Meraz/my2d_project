#pragma once

#include <stdint.h>

static const unsigned int FREE_TO_LAST = 1;
template <class T>
class MemoryPool
{

private:
	// Startpointer
	uint32_t* m_start;

	uint32_t* m_firstFree;
	uint32_t* m_last;
	unsigned int m_numBlocks;
	unsigned int m_alignment;
	unsigned int m_sizeOfBlock;

public:
	MemoryPool(unsigned p_numBlocks, unsigned p_alignment)
	{
		m_numBlocks = p_numBlocks + 1;
		m_alignment = p_alignment;
		m_sizeOfBlock = sizeof(T);
	}

	void init()
	{
		uint32_t* raw = (uint32_t*)malloc(m_numBlocks * m_sizeOfBlock + m_alignment);
		uint32_t mask = m_alignment - 1;

		uint32_t misalignment = (reinterpret_cast<uint32_t>(raw) & mask);
		uint32_t adjustment = m_alignment - misalignment;

		m_start = reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(raw) + adjustment);

		char* metadata = (char*)((uint32_t)m_start-1);
		*metadata = static_cast<char>(adjustment);		
		
		m_firstFree = m_start;
		
		uint32_t* currentBlock = m_firstFree;
		for(unsigned int i = 0; i < m_numBlocks-1; i++)
		{
			uint32_t adress = (uint32_t)currentBlock; //get pointer adress as uint
			*currentBlock = (uint32_t)(adress + m_sizeOfBlock); //Save next block as uint in the currentBlock
			currentBlock = reinterpret_cast<uint32_t*>(*currentBlock); //Set currentBlock to next block		
		}
		//nyrad
		m_last = currentBlock;
		*currentBlock = NULL;
	}

	~MemoryPool()
	{		
		char* test = (char*)((uint32_t)m_start-1);
		uint32_t test2 = (uint32_t)(*test);
		void* deleteptr = (void*)((uint32_t)m_start - test2);
		free(deleteptr);		
	}
	
	T* getBlock()
	{
		if(m_firstFree == nullptr || m_last == m_firstFree)
		{
			return nullptr;
		}
				
		T* local = (T*)m_firstFree;
		if(*m_firstFree != NULL)
			m_firstFree = (uint32_t*)*m_firstFree;
		else
			m_firstFree = nullptr; //No more memory now;
		return local;		
	}

	void freeBlock(T* p_block)
	{
		if(FREE_TO_LAST)
		{
			uint32_t* block = (uint32_t*)p_block;
			*m_last = (uint32_t)block;
			m_last = block;
			*m_last = NULL;
		}
		else
		{
			uint32_t* block = (uint32_t*)p_block;
			*block = (uint32_t)m_firstFree;
			m_firstFree = block;
		}		
	}
};
