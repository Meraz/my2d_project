#include <Jamgine/Include/JWinResourceManager.h>


namespace Jamgine
{
	JWinResourceManager::JWinResourceManager()
	{
		m_gameStack = nullptr;
		m_levelStack = nullptr;
		m_eventStack = nullptr;
	}
	JWinResourceManager::~JWinResourceManager()
	{
		delete m_gameStack;
		delete m_levelStack;
		delete m_eventStack;

	}
	void JWinResourceManager::Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory)
	{
		m_gameStack = m_memAllocator->CreateStack(p_globalMemory, true);

		m_levelStack = m_memAllocator->CreateStack(p_levelMemory, true);

		m_eventStack = m_memAllocator->CreateStack(p_eventMemory, true);
	}
	void* JWinResourceManager::LoadResource(std::string p_zipFile, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type)
	{
		//Check if already existing
		//Else check if memory is enough
		Resource tempRes;
		tempRes.memoryLocation;
		tempRes.refCount++;

		//Hash path to int
		//m_resources[p_path] = tempRes.memoryLocation;

		
		switch (p_type)
		{
		case(RAW) :
			tempRes.memoryLocation = LoadRaw(p_zipFile, p_fileName, p_lifeTime);
			break;
		case(TEXTURE) :
			tempRes.memoryLocation = LoadTexture(p_zipFile, p_fileName, p_lifeTime);
			break;
		case(SCRIPT) :
			tempRes.memoryLocation = LoadScript(p_zipFile, p_fileName, p_lifeTime);
			break;
		case(SHADER) :
			tempRes.memoryLocation = LoadShader(p_zipFile, p_fileName, p_lifeTime);
			break;
		}
		size_t hash = m_asher(p_fileName);
		m_resources.insert(std::pair<size_t, Resource>(hash, tempRes));

		return tempRes.memoryLocation;
	}

	void* JWinResourceManager::LoadRaw(std::string p_zipFile, std::string p_fileName, LifeTime p_lifeTime)
	{

	}

	void* JWinResourceManager::LoadTexture(std::string p_zipFile, std::string p_fileName, LifeTime p_lifeTime)
	{

	}

	void* JWinResourceManager::LoadScript(std::string p_zipFile, std::string p_fileName, LifeTime p_lifeTime)
	{

	}

	void* JWinResourceManager::LoadShader(std::string p_zipFile, std::string p_fileName, LifeTime p_lifeTime)
	{

	}

	void* JWinResourceManager::GetResource(std::string p_path)
	{
		size_t hash = m_asher(p_path);
		return m_resources[hash].memoryLocation;
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
	
}