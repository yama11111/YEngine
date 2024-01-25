/**
 * @file CBCircleShadow.h
 * @brief 丸影の定数バッファ用構造体
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// 丸影用定数バッファ
	struct CBCircleShadow
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{

			// 向き
			YMath::Vector3 shadowDir = { 0.0f,-1.0f,0.0f };

			float pad1;

			// キャスター座標
			YMath::Vector3 casterPos;

			// キャスターから影の距離
			float distanceFromCasterToShadow = 100.0f;

			// 距離減衰係数
			YMath::Vector3 shadowAtten = { 0.5f,0.6f,0.0f };

			// 減衰開始角度
			float shadowStartFactorAngleCos = 0.0f;

			// 減衰終了角度
			float shadowEndFactorAngleCos = 0.5f;

			// 動作フラグ
			float active = 0.0f;

			float pad2;
			
			float pad3;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBCircleShadow";
		}
	};
}
