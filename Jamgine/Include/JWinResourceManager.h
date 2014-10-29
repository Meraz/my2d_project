#pragma once

#include <Jamgine/Include/JResourceManager.h>
#include <Jamgine/Include/JPackageHandler.h>
#include <hash_map>
#include <string>
#include <map>
#include <vector>
#include <future>
namespace Jamgine
{

	struct ThreadParams
	{
		std::string filePath;
		std::string packagePath;
		StackAllocator* Stack;
		JPackageHandler* Handler;
		LifeTime lifeType;
		ThreadParams()
		{
			filePath = "";
			packagePath = "";
			Stack = nullptr;
			Handler = nullptr;
			lifeType = LifeTime::UNDEFINED;
		};
	};

	struct Resource
	{
		void* memoryAddress;
		std::string filePath;
		std::string packagePath;
		std::size_t size;
		int refCount;
		LifeTime lifeType;

		Resource()
		{
			memoryAddress = nullptr;
			filePath = "";
			packagePath = "";
			size = 0;
			refCount = 0;
			lifeType = LifeTime::UNDEFINED;
		};
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
		void AttachTextureConverter(JTextureConverter* p_converter) override;

		void Update();
	private:


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

		std::vector<std::future<Resource>> m_threadPool;
	};
}