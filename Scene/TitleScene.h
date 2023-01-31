#pragma once
#include "BaseScene.h"

namespace YScene
{
	// タイトルシーン
	class TitleScene : public BaseScene
	{
	public:
#pragma region リソース

		// ----- テクスチャ ----- //

		// 無地画像
		UINT plainT_ = 0;

		// ----- オーディオ ----- //

		//UINT aA_ = 0;

		// ----- スプライト (2D) ----- //

		// 画面全部
		std::unique_ptr<YGame::Sprite2D> windowS_ = nullptr;

		// ----- スプライト (3D) ----- //


		// ----- モデル ----- //

		// 立方体モデル
		std::unique_ptr<YGame::Model> cubeM_ = nullptr;


#pragma endregion
#pragma region ゲームオブジェクト

		// 転送用ライトグループ
		std::unique_ptr<YGame::LightGroup> lightGroup_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection vp_;

#pragma endregion
	public:
		// 読み込み
		void Load() override;
		// 初期化
		void Initialize() override;
		// 終了処理
		void Finalize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;
	private:
		// 背景スプライト2D描画
		void DrawBackSprite2Ds();
		// モデル描画
		void DrawModels();
		// スプライト3D描画
		void DrawSprite3Ds();
		// 前景スプライト2D描画
		void DrawFrontSprite2Ds();
	public:
		// コンストラクタ
		TitleScene() = default;
		// デストラクタ
		~TitleScene() = default;
	};
}
