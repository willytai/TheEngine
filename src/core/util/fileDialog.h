#ifndef __FILE_DIALOG_H__
#define __FILE_DIALOG_H__

#include <string>

namespace Engine7414 {
	class FileDialog
	{
	public:
		// returns empty string when cancelled
		static std::string fileExplorer(bool file_must_exist, const char* filter = "");
	};
}

#endif