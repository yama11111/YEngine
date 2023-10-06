#include "WaveTransition.h"
#include "WindBlocks.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "PipelineManager.h"
#include "ColorConfig.h"
#include "Def.h"
#include <cassert>

using YGame::WaveTransition;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YGame::Sprite2D* WaveTransition::spBlockSpr_ = nullptr;

namespace 
{
	const uint32_t kFirstPercent	 =  6;
	const uint32_t kSecondPercent	 =  8;
	const uint32_t kThirdPercent	 = 10;
}

void WaveTransition::LoadResource()
{
	// スプライト生成
	spBlockSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("white1x1.png", false)} });
}

void WaveTransition::Initialize()
{
	// 初期化
	for (size_t i = 0; i < waves_.size(); i++)
	{
		if (waves_[i] == nullptr)
		{
			// ブロック生成 + 初期化
			waves_[i].reset(new Wave());

			waves_[i]->obj_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spBlockSpr_, false));
			waves_[i]->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));
			waves_[i]->obj_->InsertConstBuffer(waves_[i]->cbColor_.get());
		}

		waves_[i]->obj_->transform_.pos_ = { 0.0f, +WinSize.y_ / 2.0f, 0.0f };
		waves_[i]->obj_->transform_.scale_ = { 0.0f, WinSize.y_, 0.0f };
		waves_[i]->obj_->Update();
	}
	waves_[0]->cbColor_->data_.baseColor = ColorConfig::skTurquoise[4];
	waves_[1]->cbColor_->data_.baseColor = ColorConfig::skTurquoise[3];
	waves_[2]->cbColor_->data_.baseColor = ColorConfig::skTurquoise[1];

	scaleXEas_[0].Initialize(0.0f, WinSize.x_, 3.0f);
	scaleXEas_[1].Initialize(WinSize.x_, 0.0f, 3.0f);

	Reset();
}

void WaveTransition::Reset()
{
	BaseTransition::Reset();

	for (size_t i = 0; i < waves_.size(); i++)
	{
		waves_[i]->actTim_.Reset(false);
	}
}

void WaveTransition::Finalize()
{
}

void WaveTransition::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	Reset();

	loadTim_.Initialize(loadFrame);

	// タイマー初期化 + 開始
	uint32_t framePerTen = changeFrame / 10;
	waves_[0]->actTim_.Initialize(framePerTen * kFirstPercent, true);
	waves_[1]->actTim_.Initialize(framePerTen * kSecondPercent, true);
	waves_[2]->actTim_.Initialize(framePerTen * kThirdPercent, true);

	// 動作開始
	isAct_ = true;
	isFalling_ = true;
}

void WaveTransition::UpdateChange()
{
	if (isAct_ == false) { return; }

	isChangeMoment_ = false;

	if (step_ == Step::Close)
	{
		if (waves_[waves_.size() - 1]->actTim_.IsEnd())
		{
			// 閉じる → 読み込み
			step_ = Step::Load;

			isFalling_ = false;
			isChangeMoment_ = true;

			loadTim_.Reset(true);
		}

	}
	else if (step_ == Step::Load)
	{
		loadTim_.Update();

		if (loadTim_.IsEnd())
		{
			// 読み込み → 開く
			step_ = Step::Open;

			isRising_ = true;

			// タイマー再設定 + スタート
			uint32_t framePerTen = waves_[2]->actTim_.EndFrame() / 10;
			waves_[2]->actTim_.Initialize(framePerTen * kFirstPercent, true);
			waves_[1]->actTim_.Initialize(framePerTen * kSecondPercent, true);
			waves_[0]->actTim_.Initialize(framePerTen * kThirdPercent, true);
		}
	}
	else if (step_ == Step::Open)
	{
		if (waves_[0]->actTim_.IsEnd())
		{
			// 終了
			Reset();

			isEnd_ = true;
		}
	}
}

void WaveTransition::UpdateBlock()
{
	if (isAct_ == false) { return; }

	// 0 → 開く、ロード
	// 1 → 閉じる
	size_t stepIndex = 0;
	if (step_ == Step::Open) { stepIndex = 1; }

	for (size_t i = 0; i < waves_.size(); i++)
	{
		Transform::Status anime;

		waves_[i]->actTim_.Update();

		float scaleVal = 0.0f;
		if (stepIndex == 0) { scaleVal = scaleXEas_[stepIndex].InOut(waves_[i]->actTim_.Ratio(), 0.6f); }
		else { scaleVal = scaleXEas_[stepIndex].InOut(waves_[i]->actTim_.Ratio(), 0.6f); }
		
		anime.scale_.x_ = scaleVal;

		if (isReverce_ == false)
		{
			if (stepIndex == 0) { anime.pos_.x_ = scaleVal / 2.0f; }
			else { anime.pos_.x_ = scaleXEas_[0].End() - (scaleVal / 2.0f); }
		}
		else
		{
			if (stepIndex == 0) { anime.pos_.x_ = scaleXEas_[0].End() - (scaleVal / 2.0f); }
			else { anime.pos_.x_ = scaleVal / 2.0f; }
		}

		waves_[i]->obj_->Update(anime);
	}
}

void WaveTransition::Update()
{
	UpdateChange();
	UpdateBlock();
}

void WaveTransition::Draw()
{
	for (size_t i = 0; i < waves_.size(); i++)
	{
		waves_[i]->obj_->Draw("Sprite2DDefault", 0);
	}
}
