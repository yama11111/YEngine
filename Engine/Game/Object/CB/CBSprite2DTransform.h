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
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string TypeName()
		{
			return "CBSprite2DTransform";
		}
	};
}