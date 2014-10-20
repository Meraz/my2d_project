#include <TestGame/Include/Level.h>

Level::Level(unsigned int p_level)
:m_requiredFiles(nullptr)
{
	if(p_level == 0)
	{
		m_requiredFiles = new std::string[5];
	}
	else if (p_level == 1) 
	{

	}

}

Level::~Level()
{

}