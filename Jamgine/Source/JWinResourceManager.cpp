#include <Jamgine/Include/JWinResourceManager.h>
#include <fstream>
#include <Jamgine/Include/JTejpPackageHandler.h>
#include <Jamgine/Include/JZipPackageHandler.h>

#define KimsSillyStackSize 1012800

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

		m_singleFrameStack = MemoryAllocator::GetMe().CreateSingleFrameStack(KimsSillyStackSize, true);

		m_tejpHandler = new JTejpPackageHandler();
		m_zipHandler = new JZipPackageHandler();
	}


	void JWinResourceManager::LoadResource(std::string p_package, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type)
	{
		JPackageHandler* packageHandler;
		std::size_t findTheDot = p_package.find(".");
		std::string rightOfDot = &p_package[findTheDot];
		if (strcmp(rightOfDot.c_str(), ".zip") == 0)
			packageHandler = m_zipHandler;
		else if (strcmp(rightOfDot.c_str(), ".tejp") == 0)
			packageHandler = m_tejpHandler;
		//Check if already existing
		//Else check if memory is enough
		Resource tempRes;

		//Hash path to int
		//m_resources[p_path] = tempRes.memoryLocation;

		StackAllocator* stack;

		switch (p_lifeTime)
		{
		case Jamgine::LifeTime::GLOBAL:
			stack = m_gameStack;
			break;
		case Jamgine::LifeTime::LEVEL:
			stack = m_nextLevelStack;
			break;
		case Jamgine::LifeTime::EVENT:
			stack = m_eventStack;
			break;
		default:
			break;
		}

		//TODO move to JZipPackageHandler
		/*ZipArchive::Ptr archive = ZipFile::Open(p_zipFile);
		ZipArchiveEntry::Ptr entry = archive->GetEntry(p_fileName);
		if (entry == NULL)
		{
			std::cout << "ERROR ERROR ERROR package not found!" << std::endl;
			return;
		}*/
		switch (p_type)
		{
		case(ResourceType::RAW) :
			tempRes.memoryAdress = LoadRaw(p_package, p_fileName, stack, packageHandler);
			break;
		case(ResourceType::TEXTURE) :
			tempRes.memoryAdress = LoadTexture(p_package, p_fileName, stack, packageHandler);
			break;
		case(ResourceType::SCRIPT) :
			tempRes.memoryAdress = LoadScript(p_package, p_fileName, stack, packageHandler);
			break;
		case(ResourceType::SHADER) :
			tempRes.memoryAdress = LoadShader(p_package, p_fileName, stack, packageHandler);
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
		tempRes.packagePath = p_package;
		if (!m_resources.insert(std::pair<size_t, Resource>(hash, tempRes)).second)
		{
			m_resources[hash] = tempRes;
		}

	}

	void* JWinResourceManager::LoadRaw(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler)
	{
		size_t dataSize = 0;
		std::istream* data = p_handler->ReadFile(p_package, p_fileName, dataSize);
		/*data->seekg(0, data->end);
		size_t dataSize = data->tellg();
		data->seekg(0, data->beg);*/
		char* singleFrameMemory = m_singleFrameStack->Push<char>(dataSize, 1);
		char* memoryPointer = nullptr;
		if (memoryPointer == nullptr)
		{
			return nullptr;
		}
		else
		{
			data->read(memoryPointer, dataSize);
		}
		//delete data;
		
		return memoryPointer;
	}

	void* JWinResourceManager::LoadTexture(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler)
	{
		size_t size = 0;
		std::istream* data = p_handler->ReadFile(p_package, p_fileName, size);
		
		/*data->seekg(0, data->end);
		size_t dataSize = data->tellg(); //Something wrong here, very large dataSize
		data->seekg(0, data->beg);*/
		size_t dataSize = size;
		char* singleFrameMemory = m_singleFrameStack->Push<char>(dataSize, 1);
		void* memoryPointer = nullptr;
		if (singleFrameMemory == nullptr)
		{
			return nullptr;
		}
		else
		{
			data->read(singleFrameMemory, dataSize);
			memoryPointer = (char*)m_TextureConverter->Convert(singleFrameMemory, dataSize, p_stack);
		}
		//delete data;
		return memoryPointer;
	}

	void* JWinResourceManager::LoadScript(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler)
	{
		return 0;
	}

	void* JWinResourceManager::LoadShader(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler)
	{
		return LoadRaw(p_package, p_fileName, p_stack, p_handler); //D3DCompile uses a raw data pointer for compiling the HLSL code
	}

	void* JWinResourceManager::GetResource(std::string p_path)
	{
		size_t hash = m_asher(p_path);
		return m_resources[hash].memoryAdress;
		// Safety here mayhaps. maybe need dual maps
	}

	void JWinResourceManager::FreeResources(LifeTime p_lifeTime, Marker p_marker)
	{
		switch (p_lifeTime)
		{
		case(LifeTime::GLOBAL) :
			m_gameStack->Free(p_marker);
			break;
		case(LifeTime::LEVEL) :
			m_levelStack->Free(p_marker);
			break;
		case(LifeTime::EVENT) :
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
		m_nextLevelStack->Wipe();
		m_levelStack = static_cast<StackAllocator*>(temp);		
	}
}