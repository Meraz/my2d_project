#pragma once

namespace Jamgine
{
	class Texture2D
	{
	public:
		virtual Texture2D() = 0;
		virtual ~Texture2D() = 0;
		
		void* GetTextureData();

	private:

	};
}