#pragma once
#include <string>

namespace YFile
{
	// String → WString
	std::wstring StringToWString(const std::string& src);

	// ファイル名抽出
	std::string FilePath(const std::string path);
	
	// 拡張子変換
	std::string ReplaceExtension(const std::string fileName, const std::string extention);
	
	// 拡張子取得
	std::string FileExtension(const std::string path);

}
