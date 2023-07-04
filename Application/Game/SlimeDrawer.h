#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "HitActor.h"

namespace YGame
{
	class SlimeDrawer final :
		public BaseDrawer,
		public SlimeActor,
		public HitActor
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="location"> : 描画位置</param>
		void Initialize(Transform* pParent, const DrawLocation location) override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		// アニメーション
		enum class AnimationType : uint16_t
		{
			// 立ち
			eIdle	 = 0b1,

			// ジャンプ
			eJump	 = 0b1 << 1,

			// 着地
			eLanding = 0b1 << 2,

			// 被弾
			eHit	 = 0b1 << 3,

			// 死亡
			eDead	 = 0b1 << 4,
		};

	public:

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		void PlayAnimation(const uint16_t index, const uint32_t frame) override;

	public:

		SlimeDrawer() = default;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="location"> : 描画位置</param>
		SlimeDrawer(const DrawLocation location);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="location"> : 描画位置</param>
		SlimeDrawer(Transform* pParent, const DrawLocation location);

		~SlimeDrawer() = default;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

	private:

		// 立ち
		YMath::Timer IdleTimer_;

		// ジャンプ
		YMath::Timer JumpTimer_;

		// 着地
		YMath::Timer LandingTimer_;

		// 被弾
		YMath::Timer HitTimer_;

		// 死亡
		YMath::Timer DeadTimer_;


		// モデルポインタ
		static Model* spModel_;

	private:

		/// <summary>
		/// タイマー更新
		/// </summary>
		void TimerUpdate();

		/// <summary>
		/// アニメーションアップデート
		/// </summary>
		void AnimationUpdate();
	};
}