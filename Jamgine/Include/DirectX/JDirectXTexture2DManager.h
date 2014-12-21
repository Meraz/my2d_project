#pragma once

#include <Jamgine/Include/DirectX/JDirectXTexture2D.h>

#include <Jamgine/Include/ErrorMessage.h>
#include <map>

namespace Jamgine
{
	class JDirectXTexture2DManager
	{
	public:
		static ErrorMessage CreateTexture2DManager(JDirectXTexture2DManager** p_textureManager);
		void Initialize(ID3D11Device* p_device);

		ErrorMessage GetTexture(Texture2D** p_texture2D, std::string p_filePath);

	private:
		JDirectXTexture2DManager();
		//virtual ~JDirectXTexture2DManager();
		ID3D11Device* m_device;
		
		static void ReleaseTexture2DManager(); // TODO should this be private?
		static JDirectXTexture2DManager* m_texture2DManager;

		std::map<std::string, JDirectXTexture2D*> m_texture;

		/*
			Hashmap som h�ller p_filePath som nyckel
			N�r man k�r metoden LoadTexture s� kollar den om texturen redan �r inladdad.
			I s� fall returneras en pekare till dne redan inladdade texturen
			annars s� laddas texturen in och en pekare returneras till den nyinladdade texturen.
		*/


	};
}