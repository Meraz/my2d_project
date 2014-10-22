#include <Jamgine\Include\JTejpPackageHandler.h>


namespace Jamgine
{

	JTejpPackageHandler::JTejpPackageHandler()
	{
	}


	JTejpPackageHandler::~JTejpPackageHandler()
	{
	}

	std::istream* ReadFile(std::string p_package, std::string p_file)
	{
		int firstColon = 0;
		int secondColon = 0;
		int size = 0;
		int pos = 0;
		int tableSize = 0;
		std::string line;
		std::ifstream* stream;
		stream->open(p_package);
		stream->getline(line.c_str, 256);
		if (line.compare("TABLE_START") == 0)
		{
			stream->getline(line.c_str, 256); 
			
			while (line.substr(0, line.find(':')).compare("TABLE_END") != 0)
			{
				stream->getline(line.c_str, 256);
				if (line.substr(0, line.find(':')).compare(p_file.c_str) == 0)
				{
					firstColon = line.find(':');
					secondColon = line.find(':', firstColon);
					size = atoi(line.substr(firstColon + 1, secondColon).c_str);
					pos = atoi(line.substr(secondColon + 1, line.find('\n')).c_str);
				}
			}
			//found end of table, read size
			tableSize = atoi(line.substr(line.find(':'), line.find('\n')).c_str);
			pos += tableSize;
			stream->seekg(pos);
			char* buffer = new char[size];
			stream->read(buffer, size);
			
			//TODO read the stream into a char* returnparameter
			stream->close();
		}
		else
		{
			//no table
			
		}
		stream->close();
		return stream;
	}

	std::istream* ReadPoint(std::string p_package, unsigned p_point, size_t p_size)
	{

	}
}
