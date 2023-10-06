#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include <string>

namespace YGame
{
	// モデル用トランスフォーム定数バッファ
	struct CBModelTransform 
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// ワールド行列
			YMath::Matrix4 matWorld = YMath::Matrix4::Identity();
			
			// ビュープロジェクション行列
			YMath::Matrix4 matViewProj = YMath::Matrix4::Identity();
			
			// カメラ座標
			YMath::Vector3 cameraPos{};
			
			float pad;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBModelTransform"; 
		}

	};
}
