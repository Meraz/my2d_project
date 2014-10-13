#pragma once

#include <Jamgine/Include/JResourceManager.h>
#include "Jamgine\Include\MemoryAllocator\MemoryAllocator.h"

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


	class JWinResourceManager : public JResourceManager
	{
	public:
		JWinResourceManager();
		virtual ~JWinResourceManager();
		void Init(unsigned p_memory) override;
		void* LoadResource(std::string p_zipFile, unsigned p_lifeTime, std::string p_fileName, ResourceType p_type) override;
		void* GetResource(std::string p_guid) override;
		void FreeResources(unsigned p_lifeTime) override;
	private:

		void* LoadRaw(std::string p_zipFile, std::string p_fileName);
		void* LoadTexture(std::string p_zipFile, std::string p_fileName);
		void* LoadScript(std::string p_zipFile, std::string p_fileName);
		void* LoadShader(std::string p_zipFile, std::string p_fileName);



		std::map<int, Resource> m_resources;
		MemoryAllocator* m_memAllocator;
		StackAllocator* m_gameStack;
		StackAllocator* m_levelStack;
		StackAllocator* m_eventStack;
	};
}