/**
 * @file PlayerDrawer.h
 * @brief プレイヤー描画クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseCharacterDrawer.h"
#include "SceneKey.h"
#include "Ease.h"

namespace YGame
{
    class PlayerDrawer final :
        public BaseCharacterDrawer
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

			// 丸影
			eCircleShadow = 0b1 << 7,
			
			// 通常色
			eNormalColor = 0b1 << 8,

			// 単色
			eSingleColor = 0b1 << 9,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<PlayerDrawer> Create(const DrawerInitSet& init, 
			const SceneKey sceneKey = SceneKey::ePlayKey);

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

		PlayerDrawer() = default;

		~PlayerDrawer() = default;
	
	private:

		bool isAttack_ = false;

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
