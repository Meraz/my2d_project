#pragma once

#include <Jamgine/Include/JResourceManager.h>

#include <string>
#include <map>
#include <vector>

namespace Jamgine
{
	struct Resource
	{
		void* memoryLocation;
		unsigned size;
		unsigned lifeTime;
		unsigned refCount;
	};

	struct Block
	{
		unsigned start;
		unsigned end;
		unsigned size;
	};

	class JWinResourceManager : public JResourceManager
	{
	public:
		JWinResourceManager();
		virtual ~JWinResourceManager();
		void Init(unsigned p_memory) override;
		void* GetResource(std::string p_guid, unsigned p_lifeTime) override;
		void FreeResources(unsigned p_lifeTime) override;
	private:
		void MergeMemoryBlocks();
		void DefragmentMemory();


		std::map<std::string, Resource> m_resources;
		std::vector<Block> m_freeBlocks;
	};
}