#pragma once
#include <string>

namespace YGame
{
	// 時間用定数バッファ
	struct CBTime
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 時間
			float time = 0.0f;
			
			float pad1;
			
			float pad2;
			
			float pad3;
		};

	public:

		/// <summary>
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string TypeName()
		{
			return "CBTime";
		}
	};
}
