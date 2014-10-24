#pragma once

#include <istream>
#include <string>

namespace Jamgine
{
	class JPackageHandler
	{
	public:
		virtual std::istream* ReadFile(std::string p_package, std::string p_file, size_t& p_size) = 0;
		virtual std::istream* ReadPoint(std::string p_package, unsigned p_point, size_t p_size) = 0;

	};
}