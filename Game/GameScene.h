#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include "AudioManager.h"
#include <memory>

#include "Skydome.h"
#include "SceneManager.h"
#include "CameraManager.h"

namespace Game
{
	class GameScene
	{
	public:
		// ----- テクスチャ ----- //
		
		// 無地画像
		UINT plainT_ = 0;
		// プレイヤー画像
		UINT playerT_ = 0;
		// エネミー画像
		UINT enemyT_ = 0;

		// ----- オーディオ ----- //

		// 
		UINT aA_ = 0;

		// ----- モデル ----- //
		
		// 立方体モデル
		std::unique_ptr<Model> cubeM_ = nullptr;
		// 天球モデル
		std::unique_ptr<Model> skydomeM_ = nullptr;

		// ----- スプライト ----- //
		
		// sprite
		std::unique_ptr<Sprite> quadS_ = nullptr;
		// 
		std::unique_ptr<Sprite> curtenS_ = nullptr;

		// ----- オブジェクト ----- //
		
		// 床
		std::vector<std::vector<Object>> floor;

		// 
		Object sprite_;
		Object player_;
		Object enemy_;

		Skydome skydome_;

		// 転送用ビュープロジェクション
		ViewProjection vp_;

		// シーンマネージャー
		SceneManager sceneMan_;
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
