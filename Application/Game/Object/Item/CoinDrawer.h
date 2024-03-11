/**
 * @file CoinDrawer.h
 * @brief コイン描画クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseCharacterDrawer.h"
#include "Ease.h"

namespace YGame
{
	class CoinDrawer final : 
		public BaseCharacterDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint32_t
		{
			// 立ち
			eIdle = 0b1,

			// 獲得
			eEarn = 0b1 << 1,
			
			// 丸影
			eCircleShadow = 0b1 << 2,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<CoinDrawer> Create(const DrawerInitSet& init);

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

	public:

		CoinDrawer() = default;

		~CoinDrawer() = default;

	private:

		// 立ちアニメーション用
		YMath::SplineEase<float> idlePosEas_;
		YMath::SplineEase<float> idleRotaEas_;

		// 獲得アニメーション用
		YMath::Ease<float> earnPosEas_;
		YMath::Ease<float> earnRotaEas_;

		YMath::Timer emitTimer_;
		uint32_t emitCounter_ = 0;

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

