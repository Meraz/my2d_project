#include <Jamgine/Include/JWinResourceManager.h>


namespace Jamgine
{
	JWinResourceManager::JWinResourceManager()
	{
		m_gameStack = nullptr;
		m_levelStack = nullptr;
		m_nextLevelStack = nullptr;
		m_eventStack = nullptr;
	}
	JWinResourceManager::~JWinResourceManager()
	{
		delete m_gameStack;
		delete m_levelStack;
		delete m_nextLevelStack;
		delete m_eventStack;

	}
	void JWinResourceManager::Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory)
	{
		m_gameStack = MemoryAllocator::GetMe().CreateStack(p_globalMemory, true);

		//Design problem, should they share p_levelMemory or duplicate it?
		m_levelStack = MemoryAllocator::GetMe().CreateStack(p_levelMemory, true);
		m_nextLevelStack = MemoryAllocator::GetMe().CreateStack(p_levelMemory, true);

		m_eventStack = MemoryAllocator::GetMe().CreateStack(p_eventMemory, true);
	}
	void* JWinResourceManager::LoadResource(std::string p_zipFile, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type)
	{
		//Check if already existing
		//Else check if memory is enough
		Resource tempRes;
		tempRes;

		//Hash path to int
		//m_resources[p_path] = tempRes.memoryLocation;

		StackAllocator* stack;

		switch (p_lifeTime)
		{
		case Jamgine::GLOBAL:
			stack = m_gameStack;
			break;
		case Jamgine::LEVEL:
			stack = m_levelStack;
			break;
		case Jamgine::EVENT:
			stack = m_eventStack;
			break;
		default:
			break;
		}

		ZipArchive::Ptr archive = ZipFile::Open(p_zipFile);
		ZipArchiveEntry::Ptr entry = archive->GetEntry(p_fileName);
		if (entry == NULL)
		{
			return nullptr;
		}
		switch (p_type)
		{
		case(RAW) :
			tempRes = LoadRaw(entry, stack);
			break;
		case(TEXTURE) :
			tempRes = LoadTexture(entry, stack);
			break;
		case(SCRIPT) :
			tempRes = LoadScript(entry, stack);
			break;
		case(SHADER) :
			tempRes = LoadShader(entry, stack);
			break;
		}
		if (tempRes == nullptr)
		{
			//No more memory, write to logg
		}
		size_t hash = m_asher(p_fileName);
		m_resources.insert(std::pair<size_t, Resource>(hash, tempRes));

		return tempRes;
	}

	void* JWinResourceManager::LoadRaw(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack)
	{
		std::istream* data = p_entry->GetDecompressionStream();
		size_t dataSize = p_entry->GetSize();
		char* memoryPointer = p_stack->Push<char>(dataSize, 1);
		if (memoryPointer != nullptr)
		{
			return nullptr;
		}
		else
		{
			data->read(memoryPointer, dataSize);
		}

		
		return memoryPointer;
	}

	void* JWinResourceManager::LoadTexture(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack)
	{
		std::istream* data = p_entry->GetDecompressionStream();
		size_t dataSize = p_entry->GetSize();
		char* memoryPointer = p_stack->Push<char>(dataSize, 1);
		if (memoryPointer != nullptr)
		{
			return nullptr;
		}
		else
		{
			data->read(memoryPointer, dataSize);
			memoryPointer = m_TextureConverter->Convert(memoryPointer, dataSize);
		}

		return memoryPointer;
	}

	void* JWinResourceManager::LoadScript(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack)
	{
		return 0;
	}

	void* JWinResourceManager::LoadShader(ZipArchiveEntry::Ptr p_entry, StackAllocator* p_stack)
	{
		return LoadRaw(p_entry, p_stack); //D3DCompile uses a raw data pointer for compiling the HLSL code
	}

	void* JWinResourceManager::GetResource(std::string p_path)
	{
		size_t hash = m_asher(p_path);
		return m_resources[hash];
	}
	void JWinResourceManager::FreeResources(LifeTime p_lifeTime, Marker p_marker)
	{
		switch (p_lifeTime)
		{
		case(GLOBAL) :
			m_gameStack->Free(p_marker);
			break;
		case(LEVEL) :
			m_levelStack->Free(p_marker);
			break;
		case(EVENT) :
			m_eventStack->Free(p_marker);
			break;
		}
	}

	void JWinResourceManager::AttatchTextureConverter(JTextureConverter* p_converter)
	{
		m_TextureConverter = p_converter;
	}
	
}