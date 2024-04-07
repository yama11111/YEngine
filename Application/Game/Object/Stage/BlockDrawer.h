/**
 * @file BlockDrawer.h
 * @brief ブロック描画クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseStageDrawer.h"
#include "SceneKey.h"

namespace YGame
{
    class BlockDrawer final :
		public BaseStageDrawer
	{

	public:

		// 種類
		enum class Type : size_t
		{
			eGreen, ePurple, eColorless, eNum
		};
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <param name="isBackground"> : 背景フラグ</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<BlockDrawer> Create(
			const DrawerInitSet& init, 
			const Type type,
			const bool isBackground,
			const SceneKey scene = SceneKey::ePlayKey);

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

		BlockDrawer() = default;

		~BlockDrawer() = default;

	private:
		
		// 種類
		Type type_ = Type::eGreen;

		// 背景フラグ
		bool isBackground_ = false;

		SceneKey scene_ = SceneKey::ePlayKey;

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
