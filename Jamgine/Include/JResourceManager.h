#pragma once

#include <string>
#include <Jamgine\Include\MemoryAllocator\MemoryAllocator.h>
#include <Jamgine\Include\JTextureConverter.h>
namespace Jamgine
{
	enum class ResourceType
	{
		RAW,
		TEXTURE,
		SCRIPT,
		SHADER,
	};

	enum class LifeTime
	{
		GLOBAL,
		LEVEL,
		EVENT,
	};

	class JResourceManager
	{
	public:
		virtual void Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory) = 0;

		/* 
			p_package: .zip .silvertejp 
			p_lifeTime: enum
			p_fileName: filename in package
			p_type: enum
		*/
		virtual void LoadResource(std::string p_package, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type) = 0;
		virtual void* GetResource(std::string p_guid) = 0;
		virtual void FreeResources(LifeTime p_lifeTime, Marker p_marker) = 0;
		virtual void SwapLevelBuffers() = 0;
		virtual void AttatchTextureConverter(JTextureConverter* p_converter) = 0;
		virtual void Update() = 0;
	};
}