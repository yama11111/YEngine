#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include "Billboard.h"
#include "AudioManager.h"
#include "CollisionManager.h"
#include <memory>

#include "Floor.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Skydome.h"
#include "MapChipManager.h"
#include "CameraManager.h"
#include "SceneManager.h"

#include "Lerp.h"
#include "Timer.h"
#include "Power.h"
#include <array>

namespace YGame
{
	class GameScene
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
		std::unique_ptr<Sprite> windowS_ = nullptr;
		// シーン遷移用
		std::unique_ptr<Sprite> curtenS_ = nullptr;
		// マップ2D表示用
		std::unique_ptr<Sprite> mapDispS_ = nullptr;

		// ----- モデル ----- //
		
		// 立方体モデル
		std::unique_ptr<Model> cubeM_ = nullptr;
		// 天球モデル
		std::unique_ptr<Model> skydomeM_ = nullptr;
		// スライムモデル
		std::unique_ptr<Model> slimeM_ = nullptr;
		
		std::array<std::unique_ptr<Model>, 3> playerMods_;

		// ----- ビルボード ----- //


#pragma endregion
#pragma region ゲームオブジェクト

		// プレイヤー
		Object player_;
		std::array<Object, 3> playerModTranss_;
		enum class Parts 
		{
			Body,
			Face,
			Tail,
		};

		// マップマネージャー
		MapChipManager mapMan_;

		// パーティクルマネージャー
		YParticle::ParticleManager particleMan_;

		// 天球
		Skydome skydome_;

		// カメラマネージャー
		CameraManager cameraMan_;

		// 転送用ビュープロジェクション
		ViewProjection vp_;

		// アタリ判定マネージャー
		YCollision::CollisionManager collMan_;

		// シーンマネージャー
		SceneManager sceneMan_;

#pragma endregion
	public:
		// 読み込み
		void Load();
		// 初期化
		void Initialize();
		// 更新
		void Update();
		// 描画
		void Draw();
	private:
		// 背景スプライト描画
		void DrawBackSprites();
		// モデル描画
		void DrawModels();
		// ビルボード描画
		void DrawBillboards();
		// 前景スプライト描画
		void DrawFrontSprites();
	public:
		// コンストラクタ
		GameScene();
		// デストラクタ
		~GameScene();
	private:
		// キー(シングルトン)
		static YInput::Keys* keys_;
		// マウス(シングルトン)
		static YInput::Mouse* mouse_;
		// パッド(シングルトン)
		static YInput::Pad* pad_;
	private:
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
		// 静的オーディオマネージャーポインタ
		static AudioManager* pAudioManager_;
	public:
		// 静的初期化
		static void StaticInitialize(TextureManager* pTexManager, AudioManager* pAudioManager);
	};
}
