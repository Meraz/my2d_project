#pragma once

#include <Jamgine/Include/Texture2D.h>

#include <Jamgine/Include/ErrorMessage.h>

namespace Jamgine
{
	class Texture2DManager
	{
	public:
		virtual Texture2DManager() = 0;
		virtual Texture2DManager() = 0;


		ErrorMessage::ErrorMessage LoadTexture(Texture2D** p_texture2D, char* p_filePath);

	private:
		/*
			Hashmap som håller p_filePath som nyckel
			När man kör metoden LoadTexture så kollar den om texturen redan är inladdad.
			I så fall returneras en pekare till dne redan inladdade texturen
			annars så laddas texturen in och en pekare returneras till den nyinladdade texturen
		*/


	};
}