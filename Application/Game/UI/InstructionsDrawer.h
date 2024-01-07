/**
 * @file InstructionsDrawer.h
 * @brief 操作説明用のUIを表示するクラス
 * @author Yamanaka Rui
 * @date 2024/01/05
 */

#pragma once
#include "UIButton.h"
#include "ViewProjection.h"

namespace YGame
{
	class InstructionsDrawer final
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <returns>操作説明描画クラスポインタ (動的インスタンス)</returns>
		static InstructionsDrawer* Create(YMath::Matrix4* pParent, ViewProjection* pVP);

		/// <summary>
		/// 読み込み
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void Initialize(YMath::Matrix4* pParent, ViewProjection* pVP);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	private:

		// トランスフォーム
		Transform transform_;

		// ジャンプボタン
		std::unique_ptr<UIButton> buttonJump_;
		
		// 攻撃ボタン
		std::unique_ptr<UIButton> buttonAttack_;

	};
}
