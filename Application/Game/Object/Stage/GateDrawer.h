#pragma once
#include "BaseDrawer.h"
#include "Ease.h"
#include "Timer.h"

namespace YGame
{
	class GateDrawer final :
		public BaseDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint32_t
		{
			// 立ち
			eIdle = 0b1,

			// 拡張
			eExtend = 0b1 << 1,
			
			// 収縮
			eShrink = 0b1 << 2,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<GateDrawer> Create(const DrawerInitSet& init);

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

		GateDrawer() = default;

		~GateDrawer() = default;

	private:

		std::unique_ptr<ConstBufferObject<CBColor>> cbInsideColor_;

		YMath::Ease<float> extendRotaEas_;
		YMath::Ease<float> extendScaleEas_;

		YMath::Ease<float> shrinkRotaEas_;
		YMath::Ease<float> shrinkScaleEas_;

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
