#pragma once
#include <Jamgine\Include\JPackageHandler.h>
#include <ziplib/ZipFile.h>
#include <atomic>
#include <sstream>
namespace Jamgine
{

	class JZipPackageHandler : public JPackageHandler
	{
	public:
		JZipPackageHandler();
		virtual ~JZipPackageHandler();

		std::istream* ReadFile(std::string p_package, std::string p_file, size_t& p_size) override;
		std::istream* ReadPoint(std::string p_package, unsigned p_point, size_t p_size) override; //Does nothing on .zip
		void WipeBuffers() override; //Does nothing on .zip
	private:
		ZipArchive::Ptr m_archive;
		std::atomic_flag m_lock;
	};
}

