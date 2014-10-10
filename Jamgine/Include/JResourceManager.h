#pragma once

#include <string>

namespace Jamgine
{

	enum ResourceType
	{
		RAW,
		TEXTURE,
		SCRIPT,
		SHADER,
	};

	class JResourceManager
	{
	public:
		
		//virtual ~JResourceManager() = 0;
		virtual void Init(unsigned p_memory) = 0;
		virtual void* LoadResource(std::string p_zipFile, unsigned p_lifeTime, std::string p_fileName, ResourceType p_type) = 0;
		virtual void* GetResource(std::string p_guid) = 0;
		virtual void FreeResources(unsigned p_lifeTime) = 0;

	private:

	};
}