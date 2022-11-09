#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include <memory>

namespace Game
{
	class GameScene
	{
	public:
		// ----- リソース ----- //

		// 無地画像
		UINT plainTex = 0;

		// model
		std::unique_ptr<Model> m1 = nullptr;

		// sprite
		std::unique_ptr<Sprite> s1 = nullptr;

		// ----- オブジェクト ----- //

		// Transform1
		Transform t1;
		// Transform2
		Transform t2;
		// Transform3
		Transform t3;

		// 転送用ビュープロジェクション
		ViewProjection vp;
	public:
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
	public:
		// 静的初期化
		static void StaticInitialize(TextureManager* pTexManager);
	};
}
