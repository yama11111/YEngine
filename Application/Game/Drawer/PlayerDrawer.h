#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "HitActor.h"
#include "CBOutline.h"

namespace YGame
{
    class PlayerDrawer final :
        public BaseDrawer
    {

	public:

		// アニメーション
		enum class AnimationType : uint32_t
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

	public:

		PlayerDrawer() = default;

		~PlayerDrawer() = default;
	
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
		void GetReadyForAnimation(const uint32_t index) override;

		/// <summary>
		/// アニメーション更新
		/// </summary>
		void UpdateAnimation() override;
    };
}
