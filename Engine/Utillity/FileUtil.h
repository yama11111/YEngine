#pragma once
#include <string>

namespace YFile
{
	// String �� WString
	std::wstring StringToWString(const std::string& src);

	// �t�@�C�������o
	std::string FilePath(const std::string path);
	
	// �g���q�ϊ�
	std::string ReplaceExtension(const std::string fileName, const std::string extention);
	
	// �g���q�擾
	std::string FileExtension(const std::string path);

}
