#pragma once
#include "BaseGraphic.h"

namespace YGame
{
	class DefaultGraphic
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// デフォルト値のグラフィックのポインタ取得
		/// </summary>
		/// <param name="tag"> : タグ</param>
		/// <returns>デフォルトのグラフィックのポインタ</returns>
		static BaseGraphic* Ptr(const std::string& tag);
	};
}

