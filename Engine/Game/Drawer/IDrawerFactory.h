#pragma once
#include "BaseDrawer.h"
#include <string>

namespace YGame
{
	// 抽象描画クラスファクトリークラス
	class IDrawerFactory
	{

	public:

		/// <summary>
		/// 描画クラス生成
		/// </summary>
		/// <param name="drawerName"> : 名前</param>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>描画クラス</returns>
		virtual std::unique_ptr<BaseDrawer> CreateDrawer(
			const std::string& drawerName, Transform* pParent, const size_t drawPriority) = 0;

	public:

		// デストラクタ
		virtual ~IDrawerFactory() = default;
	};
}
