#pragma once
#include "BaseScene.h"

#include "Floor.h"
#include "Skydome.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "CollisionPrimitive.h"
#include "MapChipManager.h"
#include "CameraManager.h"
#include "ParticleManager.h"
#include <array>

namespace YScene
{
	// ゲームデモシーン
	class DemoScene : public BaseScene
	{
	public:
#pragma region リソース

		// ----- テクスチャ ----- //

		// 無地画像
		UINT plainTex_ = 0;

		// マップチップ2D画像
		UINT mapDispTex_ = 0;
		// マップチップ3D画像
		UINT mapTex_ = 0;

		// ----- オーディオ ----- //

		// ----- スプライト (2D) ----- //

		// 画面全部
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// マップ2D表示用
		std::unique_ptr<YGame::Sprite2D> mapDispSpr_ = nullptr;

		// ----- スプライト (3D) ----- //
		std::unique_ptr<YGame::Sprite3D> filterSpr_ = nullptr;

		// ----- モデル ----- //

		// 立方体モデル
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

		// 天球モデル
		std::unique_ptr<YGame::Model> skydomeMod_ = nullptr;
		// ビルモデル
		std::unique_ptr<YGame::Model> buildingMod_ = nullptr;
		// バリアモデル
		std::unique_ptr<YGame::Model> barrierMod_ = nullptr;


#pragma endregion
#pragma region ゲームオブジェクト

		YMath::Vector3 center_;

		// プレイヤー
		Player player_;

		std::unique_ptr<YGame::Color> color_;

		bool isA = false;
		std::unique_ptr<YGame::Color> fcolor_;
		std::unique_ptr <YGame::ObjectSprite3D> filter_;
		
		// ビル
		std::array<std::unique_ptr<YGame::ObjectModel>, 8> buildings_;
		std::unique_ptr<YGame::Color> buildingColor_;

		// マップマネージャー
		YGame::MapChipManager mapMan_;

		// パーティクルマネージャー
		YGame::ParticleManager particleMan_;

		// 天球
		YGame::Skydome skydome_;

		// カメラマネージャー
		YGame::CameraManager cameraMan_;

		// 転送用ライトグループ
		std::unique_ptr<YGame::LightGroup> lightGroup_;
		std::unique_ptr<YGame::LightGroup> lightGroup2_;

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
		DemoScene() = default;
		// デストラクタ
		~DemoScene() = default;
	};
}