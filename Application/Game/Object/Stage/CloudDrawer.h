#pragma once
#include "BaseDrawer.h"
#include "Ease.h"
#include "Timer.h"

namespace YGame
{
	class CloudDrawer final:
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<CloudDrawer> Create(const DrawerInitSet& init);

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

		CloudDrawer() = default;

		~CloudDrawer() = default;

	private:

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;
	};
}
