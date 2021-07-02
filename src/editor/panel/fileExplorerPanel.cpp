#include "editor/panel/fileExplorerPanel.h"

#include <imgui/imgui.h>

namespace Engine7414
{
	FileExplorerPanel::FileExplorerPanel() {
		this->refreshDirectory();
		if (!_currentDirectory.is_absolute()) {

		}
	}

	void FileExplorerPanel::onImGui() {
		bool refresh = false;
		ImGui::Begin("File Browser");
		if (_currentDirectory != _rootDirectory) {
			if (ImGui::Button("<-")) {
				_currentDirectory = _currentDirectory.parent_path();
				CORE_INFO("{}", _currentDirectory);
				refresh = true;
			}
		}
		for (auto& [path, isDir] : _files) {
			if (isDir) {
				if (ImGui::Button(path.string().c_str())) {
					_currentDirectory /= path;
					refresh = true;
				}
			}
			else ImGui::Text("%s", path.string().c_str());
		}
		ImGui::End();
		this->refreshDirectory();
	}

	void FileExplorerPanel::refreshDirectory() {
		_files.clear();
		for (auto& entry : std::filesystem::directory_iterator(_currentDirectory)) {
			_files.emplace_back( std::move(entry.path().filename()), entry.is_directory() );
		}
	}
}