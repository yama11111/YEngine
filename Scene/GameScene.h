#pragma once
#include "BaseScene.h"

#include "Floor.h"
#include "Skydome.h"
#include "Player.h"
#include "PlayerDrawer.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "MapChipManager.h"
#include "CameraManager.h"

namespace YScene
{
	class GameScene : public BaseScene
	{
	public:
#pragma region リソース

		// ----- テクスチャ ----- //
		
		// 無地画像
		UINT plainT_ = 0;
		// プレイヤー画像
		UINT playerT_ = 0;
		// エネミー画像
		UINT enemyT_ = 0;
		// マップ画像
		UINT mapT_ = 0;
		// マップ2D表示用画像
		UINT mapDispT_ = 0;

		// ----- オーディオ ----- //

		//UINT aA_ = 0;

		// ----- スプライト ----- //
		
		// 画面全部
		std::unique_ptr<YGame::Sprite2D> windowS_ = nullptr;
		// シーン遷移用
		std::unique_ptr<YGame::Sprite2D> curtenS_ = nullptr;
		// マップ2D表示用
		std::unique_ptr<YGame::Sprite2D> mapDispS_ = nullptr;

		// ----- モデル ----- //
		
		// 立方体モデル
		std::unique_ptr<YGame::Model> cubeM_ = nullptr;
		// 天球モデル
		std::unique_ptr<YGame::Model> skydomeM_ = nullptr;
		// スライムモデル
		std::unique_ptr<YGame::Model> slimeM_ = nullptr;

		// ずんだもんモデル
		std::unique_ptr<YGame::Model> zundamonM_ = nullptr;

		// ----- ビルボード ----- //


#pragma endregion
#pragma region ゲームオブジェクト

		// プレイヤー
		std::unique_ptr<YGame::ObjectModel> player_;
		YDrawer::PlayerDrawer playerDra_;

		// マップマネージャー
		MapChipManager mapMan_;

		// パーティクルマネージャー
		//YParticle::ParticleManager particleMan_;

		// 天球
		//Skydome skydome_;

		// カメラマネージャー
		YCamera::CameraManager cameraMan_;

		// 転送用ライトグループ
		std::unique_ptr<YGame::LightGroup> lightGroup_;
		YMath::Vec3 lightDire1_;
		YMath::Vec3 lightDire2_;

		// 転送用ビュープロジェクション
		YGame::ViewProjection vp_;

		// アタリ判定マネージャー
		YCollision::CollisionManager collMan_;

		// シーンマネージャー
		//SceneManager sceneMan_;

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
		GameScene() = default;
		// デストラクタ
		~GameScene() = default;
	};
}
