#ifdef _WIN64
#include "core/util/fileDialog.h"
#include "core/app.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Engine7414 {
	std::string FileDialog::fileExplorer(bool file_must_exist, const char* filter) {
		CHAR file[256] = { 0 };

		OPENFILENAMEA handle;
		memset(&handle, 0, sizeof(OPENFILENAME));
		handle.lStructSize = sizeof(OPENFILENAME);
		handle.hwndOwner = glfwGetWin32Window((GLFWwindow*)App::getWindow()->nativeWindow());
		handle.lpstrFile = file;
		handle.nMaxFile = sizeof(file);
		handle.lpstrFilter = filter;
		handle.nFilterIndex = 1;
		handle.Flags = OFN_PATHMUSTEXIST |
					   OFN_NOCHANGEDIR   |
					   (file_must_exist?OFN_FILEMUSTEXIST:0);
		if (file_must_exist && GetOpenFileNameA(&handle)) return file;
		if (!file_must_exist && GetSaveFileNameA(&handle)) return file;
		return std::string();
	}
}

#endif