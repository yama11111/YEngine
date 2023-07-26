#include "Blackout.h"
#include "Def.h"
#include "PipelineManager.h"
#include "MathVector.h"

using YScene::Blackout;
using YGame::PipelineManager;
using YGame::Transform;
using YGame::Object;
using YGame::Sprite2D;
using YGame::Texture;
using YGame::ConstBuffer;
using YGame::CBSprite2DTransform;
using YGame::CBColor;
using YGame::CBTexConfig;
using YMath::Vector2;

YGame::Sprite2D* Blackout::spCurtenSpr_ = nullptr;
YMath::Ease<float> Blackout::sBlendEas_;

void Blackout::StaticInitialize()
{
	// テクスチャ読み込み
	Texture* pTex = Texture::Load("white1x1.png", false);
	
	// スプライト生成
	spCurtenSpr_ = Sprite2D::Create({ {"Texture0", pTex} });

	// 透過イージング初期化
	sBlendEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void Blackout::Initialize()
{
	// 初期化
	transform_.reset(new Transform());
	obj_.reset(new Object());
	cbTransform_.reset(ConstBuffer<CBSprite2DTransform>::Create(false));
	obj_->InsertConstBuffer(cbTransform_.get());
	cbColor_.reset(ConstBuffer<CBColor>::Create(false));
	obj_->InsertConstBuffer(cbColor_.get());
	cbTexConfig_.reset(ConstBuffer<CBTexConfig>::Create(false));
	obj_->InsertConstBuffer(cbTexConfig_.get());

	obj_->SetGraphic(spCurtenSpr_);

	Reset();
}

void Blackout::Finalize()
{
}

void Blackout::Reset()
{
	// リセット
	step_ = Step::Dark;
	
	isAct_ = false;
	isFalling_ = false;
	isChangeMoment_ = false;
	isRising_ = false;
	isEnd_ = false;
	loadTim_.Reset(false);

	blendPow_.Reset();

	// 画面中央
	Vector2 p = WinSize / 2.0f;
	transform_->pos_ = { p.x_, p.y_, 0.0f };
	transform_->scale_ = { WinSize.x_, WinSize.y_, 0.0f };
	transform_->UpdateMatrix();
	cbTransform_->data_.matWorld = transform_->m_ * YMath::MatOrthoGraphic();
	
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,0.0f };
}

void Blackout::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// リセット
	Reset();
	
	// 動作開始
	isAct_ = true;
	isFalling_ = true;

	blendPow_.Initialize(changeFrame);

	loadTim_.Initialize(loadFrame);
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
			step_ = Step::Bright;


			// 瞬間フラグをfalseに
			isChangeMoment_ = false;

			// 幕開けフラグをtrueに
			isRising_ = true;
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
		blendVal = sBlendEas_.In(blendPow_.Ratio());
	}
	// 明転中 なら
	else if (step_ == Step::Bright)
	{
		// イーズアウト
		blendVal = sBlendEas_.Out(blendPow_.Ratio());
	}

	// 色変更
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,blendVal };
}

void Blackout::Update()
{
	UpdateChange();
	UpdateBlend();
}

void Blackout::Draw()
{
	PipelineManager::GetInstance()->EnqueueDrawSet("Sprite2DDefault", 2, obj_.get());
}
