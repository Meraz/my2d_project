#pragma once

#include <string>
#include <Jamgine/Include/JResourceManager.h>

class Level
{
public:
	Level(unsigned int p_level);
	virtual ~Level();

	void Update();
	void Render();

private:
	std::string* m_requiredFiles;
	Jamgine::JResourceManager* m_resourceManager;
};