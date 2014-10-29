#include <Jamgine/Include/JWinResourceManager.h>
#include <fstream>
#include <Jamgine/Include/JTejpPackageHandler.h>
#include <Jamgine/Include/JZipPackageHandler.h>

#define SingleFrameStackSize 1012800

namespace Jamgine
{
	JWinResourceManager::JWinResourceManager()
	{
		m_gameMemory.Stack = nullptr;
		m_levelMemory.Stack = nullptr;
		m_nextLevelMemory.Stack = nullptr;
		m_eventMemory.Stack = nullptr;
	}

	JWinResourceManager::~JWinResourceManager()
	{
		delete m_gameMemory.Stack;
		delete m_levelMemory.Stack;
		delete m_nextLevelMemory.Stack;
		delete m_eventMemory.Stack;
	}

	void JWinResourceManager::Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory)
	{
		m_gameMemory.Stack = MemoryAllocator::GetMe().CreateStack(p_globalMemory, true);

		//Design problem, should they share p_levelMemory or duplicate it?
		m_levelMemory.Stack = MemoryAllocator::GetMe().CreateStack(p_levelMemory, true);
		m_nextLevelMemory.Stack = MemoryAllocator::GetMe().CreateStack(p_levelMemory, true);

		m_eventMemory.Stack = MemoryAllocator::GetMe().CreateStack(p_eventMemory, true);

		m_singleFrameStack = MemoryAllocator::GetMe().CreateSingleFrameStack(SingleFrameStackSize, true);

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

		MemoryHandle* memory;

		switch (p_lifeTime)
		{
		case Jamgine::LifeTime::GLOBAL:
			memory = &m_gameMemory;
			break;
		case Jamgine::LifeTime::LEVEL:
			memory = &m_nextLevelMemory;
			break;
		case Jamgine::LifeTime::EVENT:
			memory = &m_eventMemory;
			break;
		default:
			break;
		}

		size_t hash = m_asher(p_fileName);
		if (memory->Resource.count(hash) == 1)
		{
			return;
		}
		if (p_lifeTime == Jamgine::LifeTime::LEVEL)
		{
			if (m_levelMemory.Resource.count(hash) == 1)
			{
				m_levelMemory.Resource[hash].refCount++;
				return;
			}
		}
		
		switch (p_type)
		{
		case(ResourceType::RAW) :
			tempRes.memoryAdress = LoadRaw(p_package, p_fileName, memory->Stack, packageHandler, tempRes.size);
			break;
		case(ResourceType::TEXTURE) :
			tempRes.memoryAdress = LoadTexture(p_package, p_fileName, memory->Stack, packageHandler, tempRes.size);
			break;
		case(ResourceType::SCRIPT) :
			tempRes.memoryAdress = LoadScript(p_package, p_fileName, memory->Stack, packageHandler, tempRes.size);
			break;
		case(ResourceType::SHADER) :
			tempRes.memoryAdress = LoadShader(p_package, p_fileName, memory->Stack, packageHandler, tempRes.size);
			break;
		}
		if (tempRes.memoryAdress == nullptr)
		{
			//No more memory, write to logg
			DumpMemoryToFile();
			return;
		}
		
		tempRes.filePath = p_fileName;
		tempRes.packagePath = p_package;
		tempRes.refCount = 1;

		memory->Resource[hash] = tempRes;
		
	}

	void* JWinResourceManager::LoadRaw(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size)
	{
		size_t dataSize = 0;
		std::istream* data = p_handler->ReadFile(p_package, p_fileName, dataSize);
		p_size = dataSize;
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
		delete data;
		
		return memoryPointer;
	}

	void* JWinResourceManager::LoadTexture(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size)
	{
		size_t dataSize = 0;
		std::istream* data = p_handler->ReadFile(p_package, p_fileName, dataSize);
		p_size = dataSize;

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
		//delete data; //might be leaking in .tejp
		return memoryPointer;
	}

	void* JWinResourceManager::LoadScript(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size)
	{
		return 0;
	}

	void* JWinResourceManager::LoadShader(std::string p_package, std::string p_fileName, StackAllocator* p_stack, JPackageHandler* p_handler, size_t &p_size)
	{
		return LoadRaw(p_package, p_fileName, p_stack, p_handler, p_size); //D3DCompile uses a raw data pointer for compiling the HLSL code
	}

	void* JWinResourceManager::GetResource(std::string p_path, LifeTime p_lifeTime)
	{
		size_t hash = m_asher(p_path);
		MemoryHandle* handle;
		switch (p_lifeTime)
		{
		case Jamgine::LifeTime::GLOBAL:
			handle = &m_gameMemory;
			break;
		case Jamgine::LifeTime::LEVEL:
			handle = &m_levelMemory;
			break;
		case Jamgine::LifeTime::EVENT:
			handle = &m_eventMemory;
			break;
		default:
			break;
		}
		return handle->Resource[hash].memoryAdress;
	}

	void JWinResourceManager::FreeResources(LifeTime p_lifeTime, Marker p_marker)
	{
		switch (p_lifeTime)
		{
		case(LifeTime::GLOBAL) :
			m_gameMemory.Stack->Free(p_marker);
			break;
		case(LifeTime::LEVEL) :
			m_levelMemory.Stack->Free(p_marker);
			break;
		case(LifeTime::EVENT) :
			m_eventMemory.Stack->Free(p_marker);
			break;
		}
	}

	void JWinResourceManager::WipeResourceStack(LifeTime p_lifeTime)
	{
		switch (p_lifeTime)
		{
		case(LifeTime::GLOBAL) :
			m_gameMemory.Stack->Wipe();
			break;
		case(LifeTime::LEVEL) :
			m_levelMemory.Stack->Wipe();
			break;
		case(LifeTime::EVENT) :
			m_eventMemory.Stack->Wipe();
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
		for (auto i : m_gameMemory.Resource)
		{
			dumpFile << "Package: " + i.second.packagePath + " FilePath: " + i.second.filePath << std::endl;
		}
		for (auto i : m_levelMemory.Resource)
		{
			dumpFile << "Package: " + i.second.packagePath + " FilePath: " + i.second.filePath << std::endl;
		}
		for (auto i : m_nextLevelMemory.Resource)
		{
			dumpFile << "Package: " + i.second.packagePath + " FilePath: " + i.second.filePath << std::endl;
		}
		for (auto i : m_eventMemory.Resource)
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
		Resource tempRes;
		for (auto i : m_levelMemory.Resource)
		{
			i.second.refCount--;
			if (i.second.refCount > 0)
			{
				tempRes = i.second;
				tempRes.memoryAdress = m_nextLevelMemory.Stack->Push<void>(i.second.size, 4);
				memcpy(tempRes.memoryAdress, i.second.memoryAdress, i.second.size);
				m_nextLevelMemory.Resource[i.first] = tempRes;
			}
			
		}
		m_levelMemory.Resource.erase(m_levelMemory.Resource.begin(), m_levelMemory.Resource.end());
		m_levelMemory.Resource.clear();
		m_levelMemory.Resource.swap(m_nextLevelMemory.Resource);
		void* temp = m_nextLevelMemory.Stack;
		m_nextLevelMemory.Stack = m_levelMemory.Stack;
		m_nextLevelMemory.Stack->Wipe();
		m_levelMemory.Stack = static_cast<StackAllocator*>(temp);		
	}
}