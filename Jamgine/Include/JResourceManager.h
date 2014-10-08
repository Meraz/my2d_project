#pragma once

#include <string>

namespace Jamgine
{
	class JResourceManager
	{
	public:
		
		//virtual ~JResourceManager() = 0;
		virtual void Init(unsigned p_memory) = 0;
		virtual void* GetResource(std::string p_guid, unsigned p_lifeTime) = 0;
		virtual void FreeResources(unsigned p_lifeTime) = 0;

	private:

	};
}