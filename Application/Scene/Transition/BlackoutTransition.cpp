#include "BlackoutTransition.h"
#include "Def.h"
#include "PipelineManager.h"
#include "MathVector.h"

using YGame::BlackoutTransition;
using YMath::Vector2;

YGame::Sprite2D* BlackoutTransition::spCurtenSpr_ = nullptr;
YMath::Ease<float> BlackoutTransition::sBlendEas_;

void BlackoutTransition::LoadResource()
{
	// テクスチャ読み込み
	Texture* pTex = Texture::Load("white1x1.png", false);
	
	// スプライト生成
	spCurtenSpr_ = Sprite2D::Create({ {"Texture0", pTex} });

	// 透過イージング初期化
	sBlendEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void BlackoutTransition::Initialize()
{
	if (obj_ == nullptr)
	{
		obj_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spCurtenSpr_, false));
	}
	if (cbColor_ == nullptr)
	{
		cbColor_.reset(ConstBufferObject<CBColor>::Create(false));
		obj_->InsertConstBuffer(cbColor_.get());
	}

	Reset();
}

void BlackoutTransition::Finalize()
{
}

void BlackoutTransition::Reset()
{
	BaseTransition::Reset();

	blendPow_.Reset();

	// 画面中央
	Vector2 p = WinSize / 2.0f;
	obj_->transform_.pos_ = { p.x, p.y, 0.0f };
	obj_->transform_.scale_ = { WinSize.x, WinSize.y, 0.0f };
	obj_->Update();
	
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,0.0f };
}

void BlackoutTransition::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// リセット
	Reset();
	
	// 動作開始
	isAct_ = true;
	isFalling_ = true;

	blendPow_.Initialize(changeFrame);

	loadTim_.Initialize(loadFrame);
}

void BlackoutTransition::UpdateChange()
{
	// 動作中じゃないなら弾く
	if (isAct_ == false) { return; }

	// 瞬間フラグをfalseに
	isChangeMoment_ = false;
	
	// ブレンド動作(暗転)フラグ
	bool act = false;

	// 暗転中 なら
	if (step_ == Step::Close)
	{
		// ブレンドする
		act = true;
		
		// ブレンドが最大(真っ暗)なら
		if (blendPow_.IsMax())
		{
			// 段階 → 読み込み
			step_ = Step::Load;
			
			
			// 幕開けフラグをtfalseに
			isFalling_ = false;

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
			step_ = Step::Open;


			// 瞬間フラグをfalseに
			isChangeMoment_ = false;

			// 幕開けフラグをtrueに
			isRising_ = true;
		}
	}
	// 明転中 なら
	else if (step_ == Step::Open)
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

void BlackoutTransition::UpdateBlend()
{
	// 動作中じゃないなら弾く
	if (isAct_ == false) { return; }

	// ブレンド値初期化
	float blendVal = 0.0f;
	
	// 暗転 or 読み込み中 なら
	if (step_ == Step::Close || step_ == Step::Load)
	{
		// イーズイン
		blendVal = sBlendEas_.In(blendPow_.Ratio());
	}
	// 明転中 なら
	else if (step_ == Step::Open)
	{
		// イーズアウト
		blendVal = sBlendEas_.Out(blendPow_.Ratio());
	}

	// 色変更
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,blendVal };
}

void BlackoutTransition::Update()
{
	UpdateChange();
	UpdateBlend();
}

void BlackoutTransition::Draw()
{
	obj_->Draw("Sprite2DDefault", 0);
}
