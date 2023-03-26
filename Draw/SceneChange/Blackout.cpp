#include "Blackout.h"
#include "Def.h"

using YGame::Blackout;
using YMath::Vector2;

std::unique_ptr<YGame::Sprite2D> Blackout::sCurtenSpr_ = nullptr;

void Blackout::StaticInitialize()
{
	// テクスチャ読み込み
	UINT texIdx = TextureManager::GetInstance()->Load("white1x1.png", false);
	
	// スプライト生成
	sCurtenSpr_.reset(Sprite2D::Create({ WinSize }, { texIdx }));
}

void Blackout::Initialize(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// 初期化
	color_.reset(Color::Create({ 0.0f,0.0f,0.0f,0.0f }));
	obj_.reset(Sprite2DObject::Create({}, color_.get()));

	blendEas_.Initialize(0.0f, 1.0f, 3.0f);
	blendPow_.Initialize(changeFrame);

	loadTim_.Initialize(loadFrame);

	Reset();
}

void Blackout::Reset()
{
	// リセット
	step_ = Step::Dark;
	
	isAct_ = false;
	isChangeMoment_ = false;
	isEnd_ = false;
	loadTim_.Reset(false);

	blendPow_.Reset();

	// 画面中央
	Vector2 p = WinSize / 2.0f;
	obj_->pos_ = { p.x_, p.y_, 0.0f };
	obj_->UpdateMatrix();
	
	color_->SetRGBA({ 0.0f,0.0f,0.0f,1.0f });
}

void Blackout::Activate()
{
	// リセット
	Reset();
	
	// 動作開始
	isAct_ = true;
}

void Blackout::UpdateChange()
{
	// 動作中じゃないなら弾く
	if (isAct_ == false) { return; }

	// 瞬間フラグをfalseに
	isChangeMoment_ = false;
	
	// ブレンド動作(暗転)フラグ
	bool act = false;

	// 暗転中 なら
	if (step_ == Step::Dark)
	{
		// ブレンドする
		act = true;
		
		// ブレンドが最大(真っ暗)なら
		if (blendPow_.IsMax())
		{
			// 段階 → 読み込み
			step_ = Step::Load;
			// 瞬間フラグをtrueに
			isChangeMoment_ = true;
			// 読み込みタイマー開始
			loadTim_.SetActive(true);
		}
	}
	// 読み込み中 なら
	else if (step_ == Step::Load)
	{
		// ブレンドする
		act = true;
		
		// 読み込みタイマー更新
		loadTim_.Update();
		
		// 読み込みタイマーが終了したら
		if (loadTim_.IsEnd())
		{
			// 段階 → 明転
			step_ = Step::Bright;
		}
	}
	// 明転中 なら
	else if (step_ == Step::Bright)
	{
		// ブレンドしない
		act = false;
		
		// ブレンドが最小(透明) なら
		if (blendPow_.IsZero())
		{
			// リセット
			Reset();
			// 終了フラグをtrueに
			isEnd_ = true;
		}
	}

	// ブレンド値更新
	blendPow_.Update(act);
}

void Blackout::UpdateBlend()
{
	// 動作中じゃないなら弾く
	if (isAct_ == false) { return; }

	// ブレンド値初期化
	float blendVal = 0.0f;
	
	// 暗転 or 読み込み中 なら
	if (step_ == Step::Dark || step_ == Step::Load)
	{
		// イーズイン
		blendVal = blendEas_.In(blendPow_.Ratio());
	}
	// 明転中 なら
	else if (step_ == Step::Bright)
	{
		// イーズアウト
		blendVal = blendEas_.Out(blendPow_.Ratio());
	}

	// 色変更
	color_->SetRGBA({ 0.0f,0.0f,0.0f,blendVal });
}

void Blackout::Update()
{
	UpdateChange();
	UpdateBlend();
}

void Blackout::Draw()
{
	sCurtenSpr_->Draw(obj_.get());
}
