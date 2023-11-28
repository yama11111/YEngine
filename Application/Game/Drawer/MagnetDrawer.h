#pragma once
#include "BaseDrawer.h"
#include "Ease.h"
#include "SlimeActor.h"
#include "CBOutline.h"

namespace YGame
{
	class MagnetDrawer : public BaseDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint32_t
		{
			// 立ち
			eIdle = 0b1,

			// 獲得
			eEarn = 0b1 << 1,

			// 吸引
			eSuction = 0b1 << 2,

			// 死亡
			eDead = 0b1 << 3,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<MagnetDrawer> Create(Transform* pParent, const size_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(Transform* pParent, const size_t drawPriority) override;

	public:

		MagnetDrawer() = default;

		~MagnetDrawer() = default;

	private:

		std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

		// 立ちアニメーション用
		YMath::SplineEase<float> idlePosEas_;
		YMath::SplineEase<float> idleRotaEas_;

		// 獲得アニメーション用
		YMath::Ease<float> earnPosEas_;
		YMath::Ease<float> earnRotaEas_;

		YMath::Timer emitTimer_;
		uint32_t emitCounter_ = 0;

		SlimeActor slimeActor_;

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
