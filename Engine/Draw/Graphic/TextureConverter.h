#pragma once
#include <string>

namespace YGame
{
	class TextureConverter
	{
	
	public:

		/// <summary>
		/// WIC → DDS変換
		/// </summary>
		/// <param name="filePath"> : ファイルパス</param>
		void ConvertTextureWICToDDS(const std::string& filePath);

	};
}
