#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// 平行光源定数バッファ
	struct CBDirectionalLight
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 向き
			YMath::Vector3 lightVec = { 1.0f,-1.0f,1.0f };
			
			float pad;
			
			// 色
			YMath::Vector3 lightColor = { 1.0f,1.0f,1.0f };
			
			// 動作フラグ
			float active = 0.0f;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBDirectionalLight";
		}
	};
}
