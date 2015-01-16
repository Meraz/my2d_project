#pragma once

#include <Jamgine/Include/ErrorMessage.h>

namespace Jamgine
{
	namespace Render
	{
		class Texture2D
		{
		public:
		
			/* Comment here */ // TODO
			virtual ErrorMessage LoadTexture(void* p_memory) = 0;

			/* Comment here */ // TODO
			virtual void* GetRawData() = 0;
		};
	}
}