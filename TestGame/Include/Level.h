#pragma once

#include <string>
#include <Jamgine/Include/JResourceManager.h>
#include <Jamgine/Include/JTextureConverter.h>
#include <Jamgine/Include/Jamgine.h>
#include <vector>
#include <TestGame/Include/Entity/RenderEntity.h>

class Level
{
	public:
		Level(Jamgine::JResourceManager* p_resourceManager, unsigned int p_level, Jamgine::JamgineEngine* p_engine);
		virtual ~Level();

		void Update(double p_deltaTime);
		void Render();

	private:
		std::string* m_requiredFiles;
		Jamgine::JResourceManager* m_resourceManager;
		Jamgine::JamgineEngine* m_engine;

		std::vector<RenderEntity*> m_entity;

};