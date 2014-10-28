#pragma once
#include <Jamgine\Include\JPackageHandler.h>
#include <fstream>
#include <sstream>

namespace Jamgine
{
	class JTejpPackageHandler : public JPackageHandler
	{
	public:
		JTejpPackageHandler();
		virtual ~JTejpPackageHandler();

		std::istream* ReadFile(std::string p_package, std::string p_file, size_t& p_size) override;
		std::istream* ReadPoint(std::string p_package, unsigned p_point, size_t p_size) override;
	private:
		//Must be member to deal with scope thingy
		std::stringbuf m_stringbuffer;
	};
}