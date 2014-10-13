#include <Jamgine/Include/JWinResourceManager.h>


namespace Jamgine
{
	JWinResourceManager::JWinResourceManager()
	{

	}
	JWinResourceManager::~JWinResourceManager()
	{

	}
	void JWinResourceManager::Init(unsigned p_memory)
	{
	}
	void* JWinResourceManager::LoadResource(std::string p_zipFile, unsigned p_lifeTime, std::string p_fileName, ResourceType p_type)
	{
		//Check if already existing
		//Else check if memory is enough
		Resource tempRes;
		tempRes.memoryLocation;
		tempRes.refCount++;
		tempRes.lifeTime = p_lifeTime;
		tempRes.size;//Get size from zipLoaderThingymajig

		//Hash path to int
		//m_resources[p_path] = tempRes.memoryLocation;

		return tempRes.memoryLocation;
	}

	void* JWinResourceManager::LoadRaw(std::string p_zipFile, std::string p_fileName)
	{

	}

	void* JWinResourceManager::LoadTexture(std::string p_zipFile, std::string p_fileName)
	{

	}

	void* JWinResourceManager::LoadScript(std::string p_zipFile, std::string p_fileName)
	{

	}

	void* JWinResourceManager::LoadShader(std::string p_zipFile, std::string p_fileName)
	{

	}

	void* JWinResourceManager::GetResource(std::string p_path)
	{
		return nullptr; //Getting rid om them angry must return errors
	}
	void JWinResourceManager::FreeResources(unsigned p_lifeTime)
	{
		
	}
	
}