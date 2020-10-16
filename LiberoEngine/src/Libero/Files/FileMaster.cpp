#include "Liber_pch.h"
#include "FileMaster.h"

namespace fs = std::filesystem;

namespace Libero
{
	FileMaster::FileMaster(Path root)
		: m_Root{root}
	{

	}

	FileMaster::Path FileMaster::GetRoot() const
	{
		return m_Root;
	}

	bool FileMaster::AddFolder(Path path)
	{
		return fs::create_directory(path);
	}
}