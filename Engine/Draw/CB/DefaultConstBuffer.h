#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	class DefaultConstBuffer
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// デフォルト値の定数バッファのポインタ取得
		/// </summary>
		/// <param name="tag"> : タグ</param>
		/// <returns>デフォルト値の定数バッファのポインタ</returns>
		static BaseConstBuffer* Ptr(const std::string& tag);
	};
}

