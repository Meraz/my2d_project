#pragma once
#include <Jamgine\Include\JPackageHandler.h>
#include <fstream>

namespace Jamgine
{

	class JTejpPackageHandler : public JPackageHandler
	{
	public:
		JTejpPackageHandler();
		~JTejpPackageHandler();

		std::istream* ReadFile(std::string p_package, std::string p_file) override;
		std::istream* ReadPoint(std::string p_package, unsigned p_point, size_t p_size) override;
	};
}