#include <Jamgine/Include/JWinResourceManager.h>
#include <fstream>

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
		m_levelStack = MemoryAllocator::GetMe().CreateStack(p_levelMemory - 56, true); // the fuck is -56 doing?
		m_nextLevelStack = MemoryAllocator::GetMe().CreateStack(p_levelMemory - 56, true);

		m_eventStack = MemoryAllocator::GetMe().CreateStack(p_eventMemory, true);

		m_singleFrameStack = MemoryAllocator::GetMe().CreateSingleFrameStack(56, true);
	}
	void JWinResourceManager::LoadResource(std::string p_zipFile, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type)
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
			stack = m_nextLevelStack;
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
			std::cout << "ERROR ERROR ERROR package not found!" << std::endl;
			return;
		}
		switch (p_type)
		{
		case(RAW) :
			tempRes.memoryAdress = LoadRaw(entry, stack);
			break;
		case(TEXTURE) :
			tempRes.memoryAdress = LoadTexture(entry, stack);
			break;
		case(SCRIPT) :
			tempRes.memoryAdress = LoadScript(entry, stack);
			break;
		case(SHADER) :
			tempRes.memoryAdress = LoadShader(entry, stack);
			break;
		}
		if (tempRes.memoryAdress == nullptr)
		{
			//No more memory, write to logg
			DumpMemoryToFile();
			return;
		}
		size_t hash = m_asher(p_fileName);
		tempRes.filePath = p_fileName;
		tempRes.packagePath = p_zipFile;
		m_resources.insert(std::pair<size_t, Resource>(hash, tempRes));

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
		char* singleFrameMemory = m_singleFrameStack->Push<char>(dataSize, 1);
		void* memoryPointer = nullptr;
		if (singleFrameMemory != nullptr)
		{
			return nullptr;
		}
		else
		{
			data->read(singleFrameMemory, dataSize);
			memoryPointer = (char*)m_TextureConverter->Convert(singleFrameMemory, dataSize, p_stack);
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
		return m_resources[hash].memoryAdress;
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
	
	void JWinResourceManager::DumpMemoryToFile()
	{
		std::ofstream dumpFile;
		dumpFile.open("ResourceDump.txt");

		dumpFile << "No more memory available for resource loading" << std::endl;
		dumpFile << "The Following resources where loaded at the time, in order of allocation" << std::endl;
		for (auto i : m_resources)
		{
			dumpFile << "Package: " + i.second.packagePath + " FilePath: " + i.second.filePath << std::endl;
		}

		dumpFile.close();
	}

	void JWinResourceManager::Update()
	{
		m_singleFrameStack->Wipe();
	}


	void JWinResourceManager::SwapLevelBuffers()
	{
		void* temp = m_nextLevelStack;
		m_nextLevelStack = m_levelStack;
		m_levelStack = reinterpret_cast<StackAllocator*>(temp);
		
	}

}