#include <Jamgine/Include/JZipPackageHandler.h>

namespace Jamgine
{

	JZipPackageHandler::JZipPackageHandler()
	{
		m_lock.clear();
	}

	JZipPackageHandler::~JZipPackageHandler()
	{
	}

	std::istream* JZipPackageHandler::ReadFile(std::string p_package, std::string p_file, size_t& p_size)
	{
		while (m_lock.test_and_set(std::memory_order_acquire))
		{
			//Keep on spinning in the free world
		}
		
		m_archive = ZipFile::Open(p_package);

		if (m_archive == NULL)
		{
			m_lock.clear();
			return nullptr;
		}
		else
		{
			ZipArchiveEntry::Ptr entry = m_archive->GetEntry(p_file);
			
			if (entry == NULL)
			{
				m_lock.clear();
				return nullptr;
			}
			else
			{
				p_size = entry->GetSize();
				m_lock.clear();
				return entry->GetDecompressionStream();
			}
		}
		
	}


	std::istream* JZipPackageHandler::ReadPoint(std::string p_package, unsigned p_point, size_t p_size)
	{
		std::cout << "reading from point in a .zip file is not allowed" << std::endl;
		return nullptr;
	}

	void JZipPackageHandler::WipeBuffers()
	{

	}
}
