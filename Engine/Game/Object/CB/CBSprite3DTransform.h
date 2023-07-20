#pragma once
#include "Matrix4.h"
#include <string>

namespace YGame
{
	// スプライト3D用定数バッファ
	struct CBSprite3DTransform
	{

	public:

		// 定数バッファデータ構造体
		struct CBData
		{
			// 3D変換行列
			YMath::Matrix4 matWorld = YMath::Matrix4::Identity();
			
			// ビルボード行列
			YMath::Matrix4 matBill = YMath::Matrix4::Identity();
		};

	public:

		/// <summary>
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string KeyName()
		{
			return "CBSprite3DTransform";
		}
	};
}