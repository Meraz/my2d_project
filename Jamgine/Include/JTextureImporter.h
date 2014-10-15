#pragma once
#include "DDSTextureLoader\DDSTextureLoader.h"

class JTextureImporter
{
public:
	JTextureImporter();
	~JTextureImporter();

	void* ConvertToSRV(void* p_data, unsigned int p_size);
private:
};