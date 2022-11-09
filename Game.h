#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "PipelineSet.h"
#include "RootParameterManager.h"
#include "Sprite.h"
#include "Model.h"
#include <memory>

class Game
{
public:
	// ----- リソース ----- //
	
	// 無地画像
	UINT plainTex = 0;
	
	// model
	std::unique_ptr<Object::Model> m1 = nullptr;
	
	// sprite
	std::unique_ptr<Object::Sprite> s1 = nullptr;

	// ----- オブジェクト ----- //

	// Transform1
	Object::Transform t1;
	// Transform2
	Object::Transform t2;
	// Transform3
	Object::Transform t3;

	// 転送用ビュープロジェクション
	Object::ViewProjection vp;

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
public:
	// コンストラクタ
	Game();
	// デストラクタ
	~Game();
private:
	// キー(シングルトン)
	static Input::Keys* keys_;
	// マウス(シングルトン)
	static Input::Mouse* mouse_;
	// パッド(シングルトン)
	static Input::Pad* pad_;
private:
	// 静的テクスチャマネージャーポインタ
	static DX::TextureManager* pTexManager_;
public:
	// 静的初期化
	static void StaticInitialize(DX::TextureManager* pTexManager);
};

