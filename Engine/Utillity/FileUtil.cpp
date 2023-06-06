#include "FileUtil.h"

std::string YFile::FilePath(const std::string path)
{
	size_t pos1;

	pos1 = path.rfind('\\');
	if (pos1 != std::string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	pos1 = path.rfind('/');
	if (pos1 != std::string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	return path;
}

std::string YFile::ReplaceExtension(const std::string fileName, const std::string extention)
{
	std::string result = fileName;

	std::string::size_type pos;
	pos = result.find_last_of(".");

	if (pos == std::string::npos) { return fileName; }

	return result.substr(0, pos) + "." + extention;
}

std::string YFile::FileExtension(const std::string path)
{
	size_t idx = path.rfind('.') + 1;
	return path.substr(idx, path.length() - idx);
}