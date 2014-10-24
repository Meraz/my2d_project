#include <Jamgine\Include\JTejpPackageHandler.h>
#include <sstream>

namespace Jamgine
{

	JTejpPackageHandler::JTejpPackageHandler()
	{
	}


	JTejpPackageHandler::~JTejpPackageHandler()
	{
	}

	std::istream* JTejpPackageHandler::ReadFile(std::string p_package, std::string p_file, size_t& p_size)
	{
		int firstColon = 0;
		int secondColon = 0;
		int size = 0;
		int pos = 0;
		int tableSize = 0;
		char chars[256];
		std::string line;
		std::ifstream* stream = new std::ifstream();
		std::istream* returnStream;
		stream->open(p_package);
		stream->getline(chars, 256);
		line = chars;

	//	std::stringbuf stringbuffer;
		if (line.compare("TABLE_START") == 0)
		{
			stream->getline(chars, 256); 
			line = chars;
			while (line.substr(0, line.find(':')).compare("TABLE_END") != 0)
			{
				if (line.substr(0, line.find(':')).compare(p_file.c_str()) == 0)
				{
					firstColon = line.find(':');
					secondColon = line.find(':', firstColon + 1);
					size = atoi(line.substr(firstColon + 1, secondColon).c_str());
					pos = atoi(line.substr(secondColon + 1, line.find('\n')).c_str());
				}
				stream->getline(chars, 256);
				line = chars;
			}
			if (pos == 0 && size == 0)
				return nullptr;
			//found end of table, read size
			stream->getline(chars, 256);
			line = chars;
			tableSize = atoi(line.substr(line.find(':')+1, line.find('\n')).c_str());
			pos += tableSize;
			stream->seekg(pos);
			char* buffer = new char[size];
			stream->read(buffer, size);
			returnStream = new std::istream(&stringbuffer);
			returnStream->rdbuf()->sputn(buffer, size);
			p_size = size;
			//delete buffer;
		}
		else
		{
			//no table
			return nullptr;
		}
		stream->close();
		return returnStream;
	}

	std::istream* JTejpPackageHandler::ReadPoint(std::string p_package, unsigned p_point, size_t p_size)
	{
		std::ifstream stream;
		std::istream* returnStream;
		char* buffer = new char[p_size];
		stream.open(p_package);

		stream.seekg(p_point);
		stream.read(buffer, p_size);

		std::stringbuf stringbuffer;
		returnStream = new std::istream(&stringbuffer);
		returnStream->rdbuf()->sputn(buffer, p_size);

		delete buffer;

		return returnStream;
	}
}
