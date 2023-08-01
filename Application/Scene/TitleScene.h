#pragma once
#include "BaseScene.h"
#include "DrawObjectForSprite2D.h"

namespace YGame
{
	// タイトルシーン
	class TitleScene : public BaseScene
	{

	private:

#pragma region リソース

		Sprite2D* pLogoSpr_ = nullptr;
		
		Sprite2D* pStartSpr_ = nullptr;
		
		Sprite2D* pButtonSpr_ = nullptr;

#pragma endregion

#pragma region ゲームオブジェクト

		std::unique_ptr<DrawObjectForSprite2D> logoObj_;

		std::unique_ptr<DrawObjectForSprite2D> startObj_;
		
		std::unique_ptr<DrawObjectForSprite2D> buttonObj_; 


		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

#pragma endregion

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
