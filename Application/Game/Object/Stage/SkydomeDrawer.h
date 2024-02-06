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
		/// <param name="pParentWorldPos"> : 親ワールド座標ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<SkydomeDrawer> Create(
			Transform* pParent,
			YMath::Vector3* pParentWorldPos,
			const size_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pParentWorldPos"> : 親ワールド座標ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(
			Transform* pParent,
			YMath::Vector3* pParentWorldPos,
			const size_t drawPriority) override;

	public:

		SkydomeDrawer() = default;

		~SkydomeDrawer() = default;

	private:

		// テクスチャ設定
		std::unique_ptr<ConstBufferObject<CBTexConfig>> backTexConfig_;

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
		/// アニメーション更新
		/// </summary>
		void UpdateAnimation() override;
	};
}
