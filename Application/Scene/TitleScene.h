#pragma once
#include "BaseScene.h"
#include "TitleDrawer.h"

namespace YGame
{
	// タイトルシーン
	class TitleScene : public BaseScene
	{

	private:

		TitleDrawer titleDra_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

	public:
		
		/// <summary>
		/// 読み込み
		/// </summary>
		void Load() override;
		
		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize() override;
		
		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize() override;
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;
		
		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;
	
	public:
		
		// コンストラクタ
		TitleScene() = default;
		
		// デストラクタ
		~TitleScene() = default;
	};
}
