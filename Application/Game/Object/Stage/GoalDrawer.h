/**
 * @file GoalDrawer.h
 * @brief ゴール描画クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class GoalDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<GoalDrawer> Create(const DrawerInitSet& init);


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

		GoalDrawer() = default;

		~GoalDrawer() = default;

	private:

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;
	};
}
