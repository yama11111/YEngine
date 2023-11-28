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

		// ジャンプ時移動用構造体
		struct MoveOnJumpSet 
		{
			bool isAlive = false;
			bool isActPower = false;
			YMath::Power power;
		};
	
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

		
		// ジャンプ時移動配列
		std::list<MoveOnJumpSet> moveOnJumpSets_;
	};
}
