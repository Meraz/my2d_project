#pragma once

#include <Jamgine/Include/JResourceManager.h>
#include <External\Include\ziplib\ZipFile.h>
#include <hash_map>
#include <string>
#include <map>
#include <vector>
namespace Jamgine
{

	struct Resource
	{
		void* memoryLocation;
		unsigned refCount;
	};


	class JWinResourceManager : public JResourceManager
	{
	public:
		JWinResourceManager();
		virtual ~JWinResourceManager();
		void Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory) override;
		void* LoadResource(std::string p_zipFile, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type) override;
		void* GetResource(std::string p_guid) override;
		void FreeResources(LifeTime p_lifeTime, Marker p_marker) override;
	private:

		void* LoadRaw(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);
		void* LoadTexture(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);
		void* LoadScript(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);
		void* LoadShader(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);



		std::map<size_t, Resource> m_resources;
		MemoryAllocator* m_memAllocator;
		StackAllocator* m_gameStack;
		StackAllocator* m_levelStack;
		StackAllocator* m_eventStack;

		Marker m_gameStackMarker;
		Marker m_levelStackMarker;
		Marker m_eventStackMarker;

		std::hash<std::string> m_asher;
	};
}