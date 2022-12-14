#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include "AudioManager.h"
#include "CollisionManager.h"
#include <memory>

#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "MapChipManager.h"
#include "CameraManager.h"
#include "SceneManager.h"

namespace Game
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
		// マップ2D表示用画像
		UINT mapDispT_ = 0;

		// ----- オーディオ ----- //

		// 
		UINT aA_ = 0;

		// ----- モデル ----- //
		
		// 立方体モデル
		std::unique_ptr<Model> cubeM_ = nullptr;
		// 天球モデル
		std::unique_ptr<Model> skydomeM_ = nullptr;

		// アシンプ確認用モデル
		std::unique_ptr<Model> aliciaM_ = nullptr;
		std::unique_ptr<Model> zundamonM_ = nullptr;

		// ----- スプライト ----- //
		
		// 画面全部
		std::unique_ptr<Sprite> curtenS_ = nullptr;
		// マップ2D表示用
		//std::unique_ptr<Sprite> mapDispS_ = nullptr;

#pragma endregion
#pragma region ゲームオブジェクト

		// 床
		std::vector<std::vector<Object>> floor;

		// プレイヤー
		std::unique_ptr<Player> player_ = nullptr;

		Object sprite_;
		Object enemy_;

		Object alicia_;
		Object zundamon_;

		// 天球
		Skydome skydome_;

		//MapChip map_;

		// カメラ
		Camera camera_;

		// 転送用ビュープロジェクション
		ViewProjection vp_;

		// アタリ判定マネージャー
		Collision::CollisionManager collMan_;

		// カメラマネージャー
		CameraManager cameraMan_;

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
		// 前景スプライト描画
		void DrawFrontSprites();
	public:
		// コンストラクタ
		GameScene();
		// デストラクタ
		~GameScene();
	private:
		// キー(シングルトン)
		static Input::Keys* keys_;
		// マウス(シングルトン)
		static Input::Mouse* mouse_;
		// パッド(シングルトン)
		static Input::Pad* pad_;
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
