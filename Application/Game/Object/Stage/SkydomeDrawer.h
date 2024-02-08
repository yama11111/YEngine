#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class SkydomeDrawer final : 
		public BaseDrawer
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
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<SkydomeDrawer> Create(const DrawerInitSet& init);

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
