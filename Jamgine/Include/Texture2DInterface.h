#pragma once

#include <Jamgine/Include/ErrorMessage.h>

namespace Jamgine
{
	class Texture2DInterface
	{
	public:
		virtual ErrorMessage LoadTexture(void* p_memory) = 0;

		virtual void* GetRawData() = 0;
	};
}