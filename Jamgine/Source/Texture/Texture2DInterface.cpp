#pragma once

namespace Jamgine
{
	class Texture2DInterface
	{
	public:
//		virtual ~Texture2DInterface() = 0;
		
		virtual void* GetData() = 0;

	private:

	};
}