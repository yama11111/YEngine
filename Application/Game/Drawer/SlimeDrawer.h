#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "HitActor.h"
#include "CBOutline.h"

namespace YGame
{
	class SlimeDrawer final :
		public BaseDrawer
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
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<SlimeDrawer> Create(Transform* pParent, const size_t drawPriority);

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

		/// <summary>
		/// 被弾アニメーション
		/// </summary>
		/// <param name="damage"> : ダメージ</param>
		/// <param name="isStepOn"> : 踏まれたか</param>
		void PlayHitAnimation(const uint32_t damage, const bool isStepOn);

	public:

		SlimeDrawer() = default;

		~SlimeDrawer() = default;

	private:

		std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

		// スライム
		SlimeActor slimeActor_;

		// 被弾
		HitActor hitActor_;

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