#include <Jamgine/Include/JZipPackageHandler.h>
#include <ziplib/ZipFile.h>

namespace Jamgine
{

	JZipPackageHandler::JZipPackageHandler()
	{
	}

	JZipPackageHandler::~JZipPackageHandler()
	{
	}

	std::istream* JZipPackageHandler::ReadFile(std::string p_package, std::string p_file)
	{
		ZipArchive::Ptr archive = ZipFile::Open(p_package);

		if (archive == NULL)
		{
			return nullptr;
		}
		else
		{
			ZipArchiveEntry::Ptr entry = archive->GetEntry(p_file);

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
