#pragma once
#include <Jamgine\Include\JPackageHandler.h>
#include <fstream>
#include <sstream>
#include <atomic>
#include <vector>
namespace Jamgine
{
	class JTejpPackageHandler : public JPackageHandler
	{
	public:
		JTejpPackageHandler();
		virtual ~JTejpPackageHandler();

		std::istream* ReadFile(std::string p_package, std::string p_file, size_t& p_size) override;
		std::istream* ReadPoint(std::string p_package, unsigned p_point, size_t p_size) override;
		void WipeBuffers() override;
	private:
		//Must be member to deal with scope thingy
		std::vector<std::stringbuf*> m_stringbuffers;
		std::atomic_flag m_lock;
	};
}