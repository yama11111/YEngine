#pragma once
#include "Camera.h"
#include "Ease.h"
#include "Power.h"
#include <list>

namespace YGame
{
	class GameCamera final
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

	public:

		/// <summary>
		/// ジャンプ時移動
		/// </summary>
		void MoveOnJump();

		/// <summary>
		/// 加速時移動
		/// </summary>
		void MoveOnAccel();

		/// <summary>
		/// カメラシェイク
		/// </summary>
		/// <param name="swing"></param>
		/// <param name="dekey"></param>
		/// <param name="place"></param>
		void Shaking(const float swing, const float dekey, const float place);
	
	public:

		/// <summary>
		/// プレイヤー位置ポインタ設定
		/// </summary>
		/// <param name="pFollowPoint"> : プレイヤー位置ポインタ</param>
		void SetPlayerPosPtr(YMath::Vector3* pPlayerPos);
	
	public:
		
		/// <summary>
		/// ビュープロジェクション取得
		/// </summary>
		/// <returns></returns>
		ViewProjection GetViewProjection() const;

	private:

		// カメラ
		Camera camera_;
		// 注視点
		YMath::Vector3 target_;
		// 距離
		YMath::Vector3 distance_;

		// プレイヤー位置ポインタ
		YMath::Vector3* pPlayerPos_ = nullptr;
		// 1F前のプレイヤー位置
		YMath::Vector3 elderPlayerPos_;
		
		// 移動
		YMath::Power movePower_;

		// 加速時移動
		YMath::Power accelPower_;
		bool isActAccelPower_ = false;
	
	private:
	
		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();

	};
}
