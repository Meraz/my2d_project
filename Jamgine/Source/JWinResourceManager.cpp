#include <Jamgine/Include/JWinResourceManager.h>
#include <fstream>
#include <Jamgine/Include/JTejpPackageHandler.h>
#include <Jamgine/Include/JZipPackageHandler.h>
#include <chrono>
#define SingleFrameStackSize 1012800

namespace Jamgine
{
	namespace
	{
		SingleFrameStack* frameStack;
		JTextureConverter* textureConverter;
		Resource LoadRaw(ThreadParams p_params)
		{
			Resource tempRes;
			tempRes.filePath = p_params.filePath;
			tempRes.packagePath = p_params.packagePath;
			tempRes.refCount = 1;
			tempRes.lifeType = p_params.lifeType;
			size_t dataSize = 0;
			std::istream* data = p_params.Handler->ReadFile(p_params.packagePath, p_params.filePath, dataSize);
			tempRes.size = dataSize;
			void* memoryPointer = frameStack->Push<void>(dataSize, 1);
			if (memoryPointer == nullptr)
			{	
				
				Resource temp = Resource();
				return temp;
			}
			else
			{
				data->read((char*)memoryPointer, dataSize);
				tempRes.memoryAddress = memoryPointer;
			}
			delete data;

			return tempRes;
		}

		Resource LoadTexture(ThreadParams p_params)
		{
			Resource tempRes;
			tempRes.filePath = p_params.filePath;
			tempRes.packagePath = p_params.packagePath;
			tempRes.refCount = 1;
			tempRes.lifeType = p_params.lifeType;
			size_t dataSize = 0;
			std::istream* data = p_params.Handler->ReadFile(p_params.packagePath, p_params.filePath, dataSize);
			tempRes.size = dataSize;
			void* singleFrameMemory = frameStack->Push<void>(dataSize, 1);
			void* memoryPointer = nullptr;
			if (singleFrameMemory == nullptr)
			{
				
				Resource temp = Resource();
				return temp;
			}
			else
			{
				data->read((char*)singleFrameMemory, dataSize);
				memoryPointer = textureConverter->Convert(singleFrameMemory, dataSize, p_params.Stack);
				if (memoryPointer == nullptr)
				{
					//No more memory, write to logg
					
					Resource temp = Resource();
					return temp;
				}
				else
				{
					tempRes.memoryAddress = memoryPointer;
				}
			}
			//delete data; //might be leaking in .tejp
			return tempRes;
		}

		

		Resource LoadShader(ThreadParams p_params)
		{
			return LoadRaw(p_params); //D3DCompile uses a raw data pointer for compiling the HLSL code
		}
	}

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

		frameStack = m_singleFrameStack;
		textureConverter = m_TextureConverter;
	}

	void JWinResourceManager::LoadResource(std::string p_package, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type)
	{
		JPackageHandler* packageHandler;

		//Check if it's a .zip or .tejp file and attach the proper handler
		std::size_t findTheDot = p_package.find(".");
		std::string rightOfDot = &p_package[findTheDot];
		if (strcmp(rightOfDot.c_str(), ".zip") == 0)
			packageHandler = m_zipHandler;
		else if (strcmp(rightOfDot.c_str(), ".tejp") == 0)
			packageHandler = m_tejpHandler;


		MemoryHandle* memory;

		//get handle to the right memorystack, depending on scope for loaded asset
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
		//get hash from filename
		size_t hash = m_asher(p_fileName);
		if (memory->Resource.count(hash) == 1) //Asset already loaded
		{
			return;
		}
		if (p_lifeTime == Jamgine::LifeTime::LEVEL) //If levelscope and the asset is already loaded increase refCount
		{
			if (m_levelMemory.Resource.count(hash) == 1)
			{
				m_levelMemory.Resource[hash].refCount++;
				return;
			}
		}

		//Init threadparameters
		ThreadParams params;
		params.filePath = p_fileName;
		params.packagePath = p_package;
		params.Handler = packageHandler;
		params.Stack = memory->Stack;
		params.lifeType = p_lifeTime;

		//Launch async load for the asset type
		switch (p_type)
		{
		case(ResourceType::RAW) :
			m_threadPool.push_back(std::async(LoadRaw, params));
			break;
		case(ResourceType::TEXTURE) :
			m_threadPool.push_back(std::async(LoadTexture, params));
			break;
		case(ResourceType::SHADER) :
			m_threadPool.push_back(std::async(LoadShader, params));
			break;
		}
		
	}

	

	void* JWinResourceManager::GetResource(std::string p_path, LifeTime p_lifeTime)
	{
		size_t hash = m_asher(p_path); //get asset hash

		//get handle to memorystack where the asset is stored
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
		//Return pointer to asset
		return handle->Resource[hash].memoryAddress;
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

	void JWinResourceManager::AttachTextureConverter(JTextureConverter* p_converter)
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

		MemoryHandle* handle;
		Resource tempRes;
		//Check if any active async load is finished
		for (unsigned int i = 0; i < m_threadPool.size(); i++)
		{
			std::chrono::microseconds time(1);
			//If finished store the data into the asset map, if not loaded continue
			if (m_threadPool.at(i).wait_for(time) == std::future_status::ready)
			{
				tempRes = m_threadPool.at(i).get(); //get data
				m_threadPool.erase(m_threadPool.begin() + i); //remove thread from pool 
				if (tempRes.memoryAddress == nullptr) //Out of memory, dump current memory to file
				{
					DumpMemoryToFile();
					continue;
				}
					
				switch (tempRes.lifeType)
				{
				case LifeTime::GLOBAL:
					handle = &m_gameMemory;
					break;
				case LifeTime::LEVEL:
					handle = &m_nextLevelMemory;
					break;
				case LifeTime::EVENT:
					handle = &m_eventMemory;
					break;
				default:
					break;
				}
				handle->Resource[m_asher(tempRes.filePath)] = tempRes; 
			}
		}
	}

	void JWinResourceManager::SwapLevelBuffers()
	{
		while (m_threadPool.size() > 0) //If assets are currently being loaded 
		{
			Update();
		}
		m_threadPool.clear();
		Resource tempRes;
		
		for (auto i : m_levelMemory.Resource)
		{
			//Decrease refcount for all assets in current level
			i.second.refCount--;

			//If asset is still being used in next level move to next levelstack/map
			if (i.second.refCount > 0)
			{
				tempRes = i.second;
				tempRes.memoryAddress = m_nextLevelMemory.Stack->Push<void>(i.second.size, 4);
				memcpy(tempRes.memoryAddress, i.second.memoryAddress, i.second.size);
				m_nextLevelMemory.Resource[i.first] = tempRes;
			}
			
		}
		//Clear current level
		m_levelMemory.Resource.erase(m_levelMemory.Resource.begin(), m_levelMemory.Resource.end());
		m_levelMemory.Resource.clear();
		m_tejpHandler->WipeBuffers();
		
		//Swap current and next level
		m_levelMemory.Resource.swap(m_nextLevelMemory.Resource);
		void* temp = m_nextLevelMemory.Stack;
		m_nextLevelMemory.Stack = m_levelMemory.Stack;
		m_nextLevelMemory.Stack->Wipe();
		m_levelMemory.Stack = static_cast<StackAllocator*>(temp);		
	}
}