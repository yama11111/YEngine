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

	public:
	
		/// <summary>
		/// デフォルト値の定数バッファのポインタ取得
		/// </summary>
		/// <param name="typeName"> : 定数バッファタイプ名</param>
		/// <returns>デフォルト値の定数バッファのポインタ</returns>
		static YDX::BaseConstBuffer* Ptr(const std::string& typeName);
	};
}

