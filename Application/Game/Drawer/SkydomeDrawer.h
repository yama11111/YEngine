#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class SkydomeDrawer final : public BaseDrawer
	{

	public:

		// アニメーション
		enum class AnimationType : uint16_t
		{
			// 立ち
			eIdle = 0b1,
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static SkydomeDrawer* Create(Transform* pParent, const size_t drawPriority);

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

		SkydomeDrawer() = default;

		~SkydomeDrawer() = default;

	private:

		// テクスチャ設定
		std::unique_ptr<ConstBufferObject<CBTexConfig>> backTexConfig_;
	
	private:

		// モデルポインタ
		static Model* spModel_;

	private:

		/// <summary>
		/// アニメーションタイマー挿入
		/// </summary>
		void InsertAnimationTimers() override;

		/// <summary>
		/// アニメーション更新
		/// </summary>
		void UpdateAnimation() override;
	};
}
