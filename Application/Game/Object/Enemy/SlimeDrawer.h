/**
 * @file SlimeDrawer.h
 * @brief スライム描画クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseCharacterDrawer.h"
#include "Power.h"

namespace YGame
{
	class SlimeDrawer final :
		public BaseCharacterDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint32_t
		{
			// 立ち
			eIdle	 = 0b1,

			// 着地
			eLanding = 0b1 << 2,
			

			// 被弾
			eHit	 = 0b1 << 3,

			// 死亡
			eDead	 = 0b1 << 4,
			
			// フィーバー
			eFever	 = 0b1 << 5,

			// 丸影
			eCircleShadow = 0b1 << 6,
			
			// ライン描画
			eShowLine = 0b1 << 7,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<SlimeDrawer> Create(const DrawerInitSet& init);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		void Initialize(const DrawerInitSet& init) override;

		/// <summary>
		/// 被弾アニメーション
		/// </summary>
		/// <param name="damage"> : ダメージ</param>
		void PlayHitAnimation(const uint32_t damage);

	public:

		SlimeDrawer() = default;

		~SlimeDrawer() = default;

	private:

		// 虹
		YMath::SplineEase<YMath::Vector4> rainbowEas_;

		std::unique_ptr<ConstBufferObject<CBColor>> cbLineColor_;
		YMath::Power lineScalePow_;

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;

		/// <summary>
		/// タイマー初期化
		/// </summary>
		void InitializeTimers() override;

		/// <summary>
		/// アニメーション準備
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		void GetReadyForAnimation(const uint32_t index) override;

		/// <summary>
		/// アニメーション更新
		/// </summary>
		void UpdateAnimation() override;
	};
}