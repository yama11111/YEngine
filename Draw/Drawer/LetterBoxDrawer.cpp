#include "LetterBoxDrawer.h"
#include "Def.h"
#include <cassert>

using YGame::LetterBoxDrawerCommon;
using YGame::LetterBoxDrawer;
using YGame::Texture;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YGame::Color;

Sprite2D* LetterBoxDrawerCommon::spSpr_ = nullptr;

void LetterBoxDrawerCommon::StaticInitialize()
{
	// テクスチャ取得 (白1x1)
	Texture* pTex = Texture::Load("white1x1.png", false);

	// スプライト作成
	spSpr_ = Sprite2D::Create({ false, { WinSize.x_, 1.0f } }, { pTex });
}

void LetterBoxDrawer::Initialize(const float topHeight, const float bottomHeight)
{
	// 0良い小さいなら弾く
	assert(topHeight_ >= 0);
	assert(bottomHeight_ >= 0);

	// 代入
	topHeight_ = topHeight;
	bottomHeight_ = bottomHeight;

	// ----- 生成 ----- //
	
	// 色生成
	color_.reset(Color::Create());

	// 上 (幅 : ウィンドウ、位置 : 指定)
	sprObjs_[0].reset(Sprite2DObject::Create({}, color_.get()));
	// 下 (幅 : ウィンドウ、位置 : ウィンドウ - 指定)
	sprObjs_[1].reset(Sprite2DObject::Create({}, color_.get()));

	// リセット
	Reset();
}

void LetterBoxDrawer::Reset()
{
	// 色初期化 (黒)
	color_->SetRGBA({ 0.0f,0.0f,0.0f,1.0f });
	
	// ----- オブジェクト初期化 ----- //
	
	// 上 (幅 : ウィンドウ、位置 : 指定)
	sprObjs_[0]->Initialize(
		{
			{ 0.0f, +topHeight_ / 2.0f, 0.0f },
			{},
			{ WinSize.x_, topHeight_, 0.0f }
		}
	);
	// 下 (幅 : ウィンドウ、位置 : ウィンドウ - 指定)
	sprObjs_[1]->Initialize(
		{
			{ 0.0f, WinSize.y_ - (bottomHeight_ / 2.0f), 0.0f },
			{},
			{ WinSize.x_, bottomHeight_, 0.0f }
		}
	);
}

void LetterBoxDrawer::Update()
{
	// 更新
	for (size_t i = 0; i < sprObjs_.size(); i++)
	{
		sprObjs_[i]->UpdateMatrix();
	}
}

void LetterBoxDrawer::Draw()
{
	// 描画
	for (size_t i = 0; i < sprObjs_.size(); i++)
	{
		spSpr_->Draw(sprObjs_[i].get());
	}
}
