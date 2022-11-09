#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "PipelineSet.h"
#include "RootParameterManager.h"
#include "Sprite.h"
#include "Model.h"
#include <memory>

class GameScene
{
public:
	// ----- リソース ----- //
	
	// 無地画像
	UINT plainTex = 0;
	
	// model
	std::unique_ptr<Game::Model> m1 = nullptr;
	
	// sprite
	std::unique_ptr<Game::Sprite> s1 = nullptr;

	// ----- オブジェクト ----- //

	// Transform1
	Game::Transform t1;
	// Transform2
	Game::Transform t2;
	// Transform3
	Game::Transform t3;

	// 転送用ビュープロジェクション
	Game::ViewProjection vp;

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
	static Game::TextureManager* pTexManager_;
public:
	// 静的初期化
	static void StaticInitialize(Game::TextureManager* pTexManager);
};

