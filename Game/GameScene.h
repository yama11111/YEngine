#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include "AudioManager.h"
#include <memory>

#include "PlayerDrawer.h"
#include "EnemyDrawer.h"
#include "SceneManager.h"

namespace Game
{
	class GameScene
	{
	public:
		// ----- リソース ----- //

		// 無地画像
		UINT plainT_ = 0;

		UINT playerT_ = 0;
		UINT enemyT_ = 0;

		UINT aA_ = 0;

		// model
		std::unique_ptr<Model> cubeM_ = nullptr;
		std::unique_ptr<Model> loadM_ = nullptr;

		// sprite
		std::unique_ptr<Sprite> quadS_ = nullptr;
		std::unique_ptr<Sprite> sceneS_ = nullptr;

		// ----- オブジェクト ----- //
		std::vector<std::vector<Transform>> floor;

		// Transform
		Transform sprite_;
		Transform model_;
		Transform player_;
		Transform enemy_;

		// 転送用ビュープロジェクション
		ViewProjection vp_;

		SceneManager sceneM_;
	public:
		// 読み込み
		void Load();
		// 初期化
		void Initialize();
		// 更新
		void Update();
		// 描画
		void Draw();
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
