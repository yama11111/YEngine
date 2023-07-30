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

		// アニメーション
		enum class AnimationType : uint16_t
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
		static SlimeDrawer* Create(Transform* pParent, const uint16_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(Transform* pParent, const uint16_t drawPriority) override;

	public:

		SlimeDrawer() = default;

		~SlimeDrawer() = default;

	private:

		// モデルポインタ
		static Model* spModel_;

	private:

		/// <summary>
		/// アニメーションタイマー挿入
		/// </summary>
		void InsertAnimationTimers() override;

		/// <summary>
		/// サブアニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		void PlaySubAnimation(const uint16_t index, const uint32_t frame) override;

		/// <summary>
		/// アニメーション更新
		/// </summary>
		void UpdateAnimtion() override;
	};
}