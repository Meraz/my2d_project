#pragma once

#include <Jamgine/Include/Texture2DInterface.h>
#include <Jamgine/Include/DDSTextureLoader/DDSTextureLoader.h>
#include <Jamgine/Include/ErrorMessage.h>
#include <string>

namespace Jamgine
{
	class Texture2D : public Texture2DInterface
	{
	public:
		Texture2D();
		ErrorMessage LoadTexture(ID3D11Device* p_device, std::string p_filepath);
		virtual ~Texture2D();
		virtual void* GetRawData();
		ID3D11ShaderResourceView* GetShaderResourceView();
	
	private:
		ID3D11Buffer* m_texture2DBuffer;
		ID3D11ShaderResourceView* m_texture2D_SRV;
	};
}