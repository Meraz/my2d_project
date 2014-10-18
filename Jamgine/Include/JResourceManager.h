#pragma once

#include <string>
#include <Jamgine\Include\MemoryAllocator\MemoryAllocator.h>
#include <Jamgine\Include\JTextureConverter.h>
namespace Jamgine
{

	enum ResourceType
	{
		RAW,
		TEXTURE,
		SCRIPT,
		SHADER,
	};

	enum LifeTime
	{
		GLOBAL,
		LEVEL,
		EVENT,
	};

	class JResourceManager
	{
	public:
		
		//virtual ~JResourceManager() = 0;
		virtual void Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory) = 0;
		virtual void* LoadResource(std::string p_zipFile, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type) = 0;
		virtual void* GetResource(std::string p_guid) = 0;
		virtual void FreeResources(LifeTime p_lifeTime, Marker p_marker) = 0;

		virtual void AttatchTextureConverter(JTextureConverter* p_converter) = 0;

	private:

	};
}