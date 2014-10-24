#include <Jamgine/Include/JZipPackageHandler.h>

namespace Jamgine
{

	JZipPackageHandler::JZipPackageHandler()
	{
	}

	JZipPackageHandler::~JZipPackageHandler()
	{
	}

	std::istream* JZipPackageHandler::ReadFile(std::string p_package, std::string p_file, size_t& p_size)
	{
		m_archive = ZipFile::Open(p_package);

		if (m_archive == NULL)
		{
			return nullptr;
		}
		else
		{
			ZipArchiveEntry::Ptr entry = m_archive->GetEntry(p_file);
			p_size = entry->GetSize();
			if (entry == NULL)
			{
				return nullptr;
			}
			else
			{
				return entry->GetDecompressionStream();
			}
		}
	}


	std::istream* JZipPackageHandler::ReadPoint(std::string p_package, unsigned p_point, size_t p_size)
	{
		return nullptr;
	}
}
