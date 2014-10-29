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
		SHADER,
	};

	enum class LifeTime
	{
		GLOBAL,
		LEVEL,
		EVENT,
		UNDEFINED,
	};

	class JResourceManager
	{
	public:
		virtual void Init(unsigned p_globalMemory, unsigned p_levelMemory, unsigned p_eventMemory) = 0;


		virtual void LoadResource(std::string p_package, LifeTime p_lifeTime, std::string p_fileName, ResourceType p_type) = 0;
		virtual void* GetResource(std::string p_guid, LifeTime p_lifeTime) = 0;
		virtual void FreeResources(LifeTime p_lifeTime, Marker p_marker) = 0;
		virtual void WipeResourceStack(LifeTime p_lifeTime) = 0;
		virtual void SwapLevelBuffers() = 0;
		virtual void AttachTextureConverter(JTextureConverter* p_converter) = 0;
		virtual void Update() = 0;
	};
}