#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "Ease.h"

namespace YGame
{
	class SnortAttackDrawer final:
		public BaseDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint16_t
		{
			// 攻撃
			eAttack = 0b1,
		};
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static SnortAttackDrawer* Create(Transform* pParent, const size_t drawPriority);

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

		SnortAttackDrawer() = default;

		~SnortAttackDrawer() = default;

	private:

		// スライム
		SlimeActor slimeActor_;

		// 回転イージング
		YMath::Ease<float> rotaEas_;

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
		void UpdateAnimation() override;
	};
}
