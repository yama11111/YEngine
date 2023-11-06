#pragma once
#include "BaseDrawer.h"
#include "Model.h"
#include "SlimeActor.h"
#include "Ease.h"
#include "CBOutline.h"

namespace YGame
{
	class NeedleAttackDrawer final :
		public BaseDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint32_t
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
		static NeedleAttackDrawer* Create(Transform* pParent, const size_t drawPriority);

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

		NeedleAttackDrawer() = default;

		~NeedleAttackDrawer() = default;

	private:


		std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

		// スライム
		SlimeActor slimeActor_;

		// 回転イージング
		YMath::Ease<float> rotaEas_;
		
		YMath::Timer popTimer_;
		YMath::Timer vanishTimer_;
		
		YMath::Timer wavePopTimer_;

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
