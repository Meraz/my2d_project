#pragma once

#include <string>

class Level
{
public:
	Level(unsigned int p_level);
	virtual ~Level();

private:
	std::string* m_requiredFiles;

};