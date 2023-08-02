#include "FileUtil.h"
#include <iostream>


// https://teratail.com/questions/9thjy2cqvqvbib
std::wstring YFile::StringToWString(const std::string& src)
{
	const char* cs = src.c_str();
	
	std::wstring ws;
	
	ws.resize(strlen(cs) + 1);
	
	size_t st = 0;

	mbstowcs_s(&st, &ws[0], ws.size(), cs, strlen(cs));

	return ws;
}

// https://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?string%A4%CB%A4%E8%A4%EB%CA%B8%BB%FA%CE%F3%BD%E8%CD%FD
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