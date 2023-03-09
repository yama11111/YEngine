#pragma once
#include "BaseScene.h"

#include "Floor.h"
#include "Skydome.h"
#include "CollisionManager.h"
#include "CollisionPrimitive.h"
#include <array>

namespace YScene
{
	// コリジョンシーン
	class CollScene : public BaseScene
	{
	public:
#pragma region リソース

		// ----- テクスチャ ----- //

		// 無地画像
		UINT plainTex_ = 0;

		// ----- オーディオ ----- //

		//UINT aA_ = 0;

		// ----- スプライト (2D) ----- //

		// 画面全部
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// ----- スプライト (3D) ----- //

		// ----- モデル ----- //

		// 立方体モデル
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

		std::unique_ptr<YGame::Model> sphereMod_ = nullptr;
		std::unique_ptr<YGame::Model> groundMod_ = nullptr;
		std::unique_ptr<YGame::Model> triangleMod_ = nullptr;

#pragma endregion
#pragma region ゲームオブジェクト

		std::unique_ptr<YGame::ObjectModel> planeObj_ = nullptr;
		YGame::Plane plane_;
		std::unique_ptr<YGame::Color> planeColor_;

		std::unique_ptr<YGame::ObjectModel> rayObj_ = nullptr;
		YGame::Ray ray_;
		std::unique_ptr<YGame::Color> rayColor_;

		std::unique_ptr<YGame::ObjectModel> triangleObj_ = nullptr;
		YGame::Triangle triangle_;
		std::unique_ptr<YGame::Color> triangleColor_;

		std::unique_ptr<YGame::ObjectModel> sphereObj_ = nullptr;
		YGame::Sphere sphere_;
		std::unique_ptr<YGame::Color> sphereColor_;

		// 転送用ライトグループ
		std::unique_ptr<YGame::LightGroup> lightGroup_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection vp_;

		// アタリ判定マネージャー
		YGame::CollisionManager collMan_;

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
		// スプライト3D描画
		void DrawBackSprite3Ds();
		// モデル描画
		void DrawModels();
		// スプライト3D描画
		void DrawFrontSprite3Ds();
		// 前景スプライト2D描画
		void DrawFrontSprite2Ds();
	public:
		// コンストラクタ
		CollScene() = default;
		// デストラクタ
		~CollScene() = default;
	};
}
