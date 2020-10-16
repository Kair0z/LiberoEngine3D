#pragma once
#include "Libero/Interfaces/ILocator.h"
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

namespace Libero
{
	class FileMaster
	{
	public:
		using rDirEntry = fs::directory_entry const&;
		using Path = fs::path;

	public:
		FileMaster(Path root = "../Resources/Assets");

		Path GetRoot() const;

		bool AddFolder(Path path);

		template <class Fn = std::function<void(rDirEntry)>>
		void ForEachFolder(Fn fn, Path inPath)
		{
			for (rDirEntry entry : fs::directory_iterator(inPath))
			{
				fn(entry);
			}
		}

	private:
		Path m_Root;
	};

	class FileLocator : public ILocator<FileMaster>{};
}


