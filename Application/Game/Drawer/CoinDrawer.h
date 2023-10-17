//#pragma once
//#include "BaseDrawer.h"
//
//namespace YGame
//{
//	class CoinDrawer : public BaseDrawer
//	{
//
//	public:
//
//		// アニメーション
//		enum class AnimationType : uint16_t
//		{
//			// 立ち
//			eIdle = 0b1,
//
//			// 獲得
//			eEarn = 0b1 << 1,
//		};
//
//	public:
//
//		/// <summary>
//		/// 生成
//		/// </summary>
//		/// <param name="pParent"> : 親ポインタ</param>
//		/// <param name="drawPriority"> : 描画優先度</param>
//		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
//		static CoinDrawer* Create(Transform* pParent, const size_t drawPriority);
//
//		/// <summary>
//		/// 静的初期化
//		/// </summary>
//		static void LoadResource();
//
//	public:
//
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="pParent"> : 親ポインタ</param>
//		/// <param name="drawPriority"> : 描画優先度</param>
//		void Initialize(Transform* pParent, const size_t drawPriority) override;
//
//		/// <summary>
//		/// 描画
//		/// </summary>
//		void Draw() override;
//
//	public:
//
//		CoinDrawer() = default;
//
//		~CoinDrawer() = default;
//
//	private:
//
//		// モデルポインタ
//		static std::array<Model*, 3> spModels_;
//
//	private:
//
//		/// <summary>
//		/// アニメーションタイマー挿入
//		/// </summary>
//		void InsertAnimationTimers() override;
//
//		/// <summary>
//		/// サブアニメーション再生
//		/// </summary>
//		/// <param name="index"> : アニメーション番号</param>
//		/// <param name="frame"> : 再生フレーム</param>
//		void GetReadyForAnimation(const uint16_t index, const uint32_t frame) override;
//
//		/// <summary>
//		/// アニメーション更新
//		/// </summary>
//		void UpdateAnimation() override;
//
//	};
//}
//