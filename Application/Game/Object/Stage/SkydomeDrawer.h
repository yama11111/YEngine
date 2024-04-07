/**
 * @file SkydomeDrawer.h
 * @brief 天球描画クラス
 * @author Yamanaka Rui
 * @date 2024/03/12
 */

#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class SkydomeDrawer final :
		public BaseDrawer
	{

	public:

		// 種類
		enum class Type : size_t
		{
			eWhite, ePurple, eGreen, eNum
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<SkydomeDrawer> Create(const DrawerInitSet& init, const Type type);

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

		// 種類
		Type type_ = Type::eWhite;

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;

		/// <summary>
		/// アニメーション更新
		/// </summary>
		void UpdateAnimation() override;
	};
}