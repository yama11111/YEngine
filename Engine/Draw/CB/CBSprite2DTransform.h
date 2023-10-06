#pragma once
#include "Matrix4.h"
#include <string>

namespace YGame
{
	// スプライト2D用定数バッファ
	struct CBSprite2DTransform
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 3D変換行列
			YMath::Matrix4 matWorld = YMath::Matrix4::Identity();
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBSprite2DTransform";
		}
	};
}