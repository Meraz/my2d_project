#pragma once

#include <Jamgine/Include/JResourceManager.h>
#include <Jamgine/Include/JPackageHandler.h>
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
		std::size_t size;
		int refCount;
	};
	
	struct MemoryHandle
	{
		StackAllocator* Stack;
		std::map<size_t, Resource> Resource;
	};

	class JWinResourceManager : public JResourceManager
	{
	public:
		JWinResourceManager();
		virtual ~JWinResourceManager();
		void Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory) override;
		void LoadResource(std::string p_package, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type) override;
		void* GetResource(std::string p_guid, LifeTime p_lifeTime) override;
		void FreeResources(LifeTime p_lifeTime, Marker p_marker) override;
		void WipeResourceStack(LifeTime p_lifeTime) override;
		void SwapLevelBuffers();
		void AttatchTextureConverter(JTextureConverter* p_converter) override;

		void Update();
	private:

		void* LoadRaw(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size);
		void* LoadTexture(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size);
		void* LoadScript(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size);
		void* LoadShader(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size);

		void DumpMemoryToFile();

		MemoryHandle m_gameMemory;
		MemoryHandle m_levelMemory;
		MemoryHandle m_nextLevelMemory;
		MemoryHandle m_eventMemory;

		SingleFrameStack* m_singleFrameStack;

		std::hash<std::string> m_asher;
		JTextureConverter* m_TextureConverter;

		JPackageHandler* m_zipHandler;
		JPackageHandler* m_tejpHandler;
	};
}