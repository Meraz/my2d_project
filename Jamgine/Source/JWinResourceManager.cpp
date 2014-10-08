#include <Jamgine/Include/JWinResourceManager.h>


namespace Jamgine
{
	JWinResourceManager::JWinResourceManager()
	{

	}
	JWinResourceManager::~JWinResourceManager()
	{

	}
	void JWinResourceManager::Init(unsigned p_memory)
	{
		Block tempBlock;
		tempBlock.start = malloc(p_memory);
		tempBlock.end = start + p_memory;
		tempBlock.size = p_memory;
		m_freeBlocks.push_back(tempBlock);
	}
	void* JWinResourceManager::GetResource(std::string p_path, unsigned p_lifeTime)
	{
		//Check if already existing
		//Else check if memory is enough
		Resource tempRes;
		tempRes.memoryLocation = m_freeBlocks.back().start;
		tempRes.refCount++;
		tempRes.lifeTime = p_lifeTime;
		tempRes.size;//Get size from zipLoaderThingymajig
		m_freeBlocks.front().start += tempRes.size;
		m_freeBlocks.front().size -= tempRes.size;
		m_resources[p_path] = tempRes.memoryLocation;

		return tempRes.memoryLocation;
	}
	void JWinResourceManager::FreeResources(unsigned p_lifeTime)
	{
		for(auto &i : m_resources)
		{
			if(i.second.lifeTime == p_lifeTime)
			{
				i.second.refCount--;
				if(i.second.refCount < 0)
				{
					Block tempBlock;
					tempBlock.start = i.second.memoryLocation;
					tempBlock.end = tempBlock.start + i.second.size;
					tempBlock.size = i.second.size;
					m_freeBlocks.push_back(tempBlock);
				}
			}
		}
		MergeMemoryBlocks();
	}
	void JWinResourceManager::MergeMemoryBlocks()
	{

	}
	void JWinResourceManager::DefragmentMemory()
	{

	}
}