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
	// ----- Input ----- //
	Input::Keys* keys = nullptr;
	Input::Mouse* mouse = nullptr;
	Input::Pad* pad = nullptr;
	// ----------------- //

	// ----- Pipeline ----- //
	DX::RootParameterManager rpM;
	DX::ConstBufferManager cbM;
	DX::PipelineSet pplnSet2D;
	DX::PipelineSet pplnSet3D;
	DX::TextureManager texM;
	// -------------------- //

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
};

