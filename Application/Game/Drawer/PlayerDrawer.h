#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "HitActor.h"

namespace YGame
{
    class PlayerDrawer final :
        public BaseDrawer
    {

	public:

		// アニメーション
		enum class AnimationType : uint16_t
		{
			// 立ち
			eIdle	 = 0b1,
			
			// 移動
			eMove	 = 0b1 << 1,
			
			// ジャンプ
			eJump	 = 0b1 << 2,
			
			// 着地
			eLanding = 0b1 << 3,
			
			// 攻撃
			eAttack	 = 0b1 << 4,
			
			// 被弾
			eHit	 = 0b1 << 5,
			
			// 死亡
			eDead	 = 0b1 << 6,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static PlayerDrawer* Create(Transform* pParent, const size_t drawPriority);

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
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		PlayerDrawer() = default;

		~PlayerDrawer() = default;
	
	private:

		// スライム
		SlimeActor slimeActor_;
		
		// 被弾
		HitActor hitActor_;

		// モデルポインタ
		static std::array<Model*, 3> spModels_;

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
