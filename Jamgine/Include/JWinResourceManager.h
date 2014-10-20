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
		void* memoryAdress;
		std::string filePath;
		std::string packagePath;
	};
	


	class JWinResourceManager : public JResourceManager
	{
	public:
		JWinResourceManager();
		virtual ~JWinResourceManager();
		void Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory) override;
		void LoadResource(std::string p_zipFile, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type) override;
		void* GetResource(std::string p_guid) override;
		void FreeResources(LifeTime p_lifeTime, Marker p_marker) override;

		void AttatchTextureConverter(JTextureConverter* p_converter) override;

		void Update();
	private:

		void* LoadRaw(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);
		void* LoadTexture(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);
		void* LoadScript(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);
		void* LoadShader(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack);

		void DumpMemoryToFile();

		std::map<size_t, Resource> m_resources;
		StackAllocator* m_gameStack;
		StackAllocator* m_levelStack;
		StackAllocator* m_nextLevelStack;
		StackAllocator* m_eventStack;

		SingleFrameStack* m_singleFrameStack;

		std::hash<std::string> m_asher;
		JTextureConverter* m_TextureConverter;
	};
}