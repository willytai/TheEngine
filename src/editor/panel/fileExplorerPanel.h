#ifndef __FILE_EXPLORER_PANEL_H__
#define __FILE_EXPLORER_PANEL_H__

#include "core/core.h"

#include <filesystem>

namespace Engine7414
{
	class FileExplorerPanel
	{
	public:
		FileExplorerPanel();
		~FileExplorerPanel() = default;

		void onImGui();
		void refreshDirectory();

	private:

	private:
		std::filesystem::path _currentDirectory = "./";
		std::filesystem::path _rootDirectory = "./";
		std::vector<std::pair<std::filesystem::path, bool> > _files;
	};
}

#endif