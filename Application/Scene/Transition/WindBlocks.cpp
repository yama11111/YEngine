#include "WindBlocks.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "PipelineManager.h"
#include "Def.h"
#include <cassert>

using YGame::WindBlocks;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YGame::Sprite2D* WindBlocks::spBlockSpr_ = nullptr;

namespace
{
	const size_t kBlockNum_ = 8;
	const float kBlockHeight_ = WinSize.y / static_cast<float>(kBlockNum_);
}

void WindBlocks::LoadResource()
{
	// スプライト生成
	spBlockSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("white1x1.png", false)} });
}

void WindBlocks::Initialize()
{
	if (blocks_.empty())
	{
		// クリア + リサイズ
		blocks_.clear();
		blocks_.resize(kBlockNum_);

		// 初期化
		for (size_t i = 0; i < blocks_.size(); i++)
		{
			// ブロック生成 + 初期化
			blocks_[i].reset(new Block());

			blocks_[i]->obj_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spBlockSpr_, false));
			blocks_[i]->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));
			blocks_[i]->obj_->InsertConstBuffer(blocks_[i]->cbColor_.get());
		}
	}

	// 初期化
	for (size_t i = 0; i < blocks_.size(); i++)
	{
		Vector2 p = { 0.0f, WinSize.y - kBlockHeight_ * i };

		blocks_[i]->obj_->transform_.pos_ = { p.x, p.y - (kBlockHeight_ / 2.0f), 0.0f };
		blocks_[i]->obj_->transform_.scale_ = { WinSize.x, kBlockHeight_, 0.0f };
		blocks_[i]->cbColor_->data_.baseColor = { 1.0f,1.0f,1.0f,0.0f };
		blocks_[i]->cbColor_->data_.texColorRate = { 1.0f,1.0f,1.0f,1.0f };
	}

	posXEas_[0].Initialize(0.0f, WinSize.x / 2.0f, 3.0f);
	posXEas_[1].Initialize(WinSize.x / 2.0f, WinSize.x, 3.0f);

	colorEas_.Initialize(YMath::GetColor(75, 17, 10, 0), YMath::GetColor(134, 34, 9, 255), 2.0f);

	Reset();
}

void WindBlocks::Reset()
{
	// リセット
	step_ = Step::Close;

	isAct_ = false;
	isFalling_ = false;
	isChangeMoment_ = false;
	isRising_ = false;
	isEnd_ = false;

	loadTim_.Reset(false);

	for (size_t i = 0; i < blocks_.size(); i++)
	{
		blocks_[i]->actTim_.Reset(false);
		blocks_[i]->colorPow_.Reset();
		blocks_[i]->isActColorPow_ = false;
	}
}

void WindBlocks::Finalize()
{
}

void WindBlocks::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// リセット
	Reset();

	// 読み込みタイマー初期化
	loadTim_.Initialize(loadFrame);

	// タイマー初期化 + 開始
	uint32_t frame = changeFrame / static_cast<uint32_t>(blocks_.size());
	for (size_t i = 0; i < blocks_.size(); i++)
	{
		blocks_[i]->actTim_.Initialize(frame);
		blocks_[i]->colorPow_.Initialize(frame);
	}

	// 動作開始
	isAct_ = true;
	isFalling_ = true;

	PropagateBlock(0, true);
}

void WindBlocks::UpdateChange()
{
	if (isAct_ == false) { return; }

	isChangeMoment_ = false;

	if (step_ == Step::Close)
	{
		if (blocks_[blocks_.size() - 1]->actTim_.IsEnd())
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

			// タイマースタート
			for (size_t i = 0; i < blocks_.size(); i++)
			{
				blocks_[i]->actTim_.Reset(false);
			}
			PropagateBlock(0, false);
		}
	}
	else if (step_ == Step::Open)
	{
		if (blocks_[blocks_.size() - 1]->actTim_.IsEnd())
		{
			// 終了
			Reset();

			isEnd_ = true;
		}
	}
}

void WindBlocks::PropagateBlock(const size_t index, const bool isActColorPow)
{
	if (blocks_.size() <= index) { return; }

	blocks_[index]->actTim_.SetActive(true);
	blocks_[index]->isActColorPow_ = isActColorPow;
}

void WindBlocks::UpdateBlock()
{
	if (isAct_ == false) { return; }

	size_t stepIndex = 0;
	if (step_ == Step::Open) { stepIndex = 1; }

	for (size_t i = 0; i < blocks_.size(); i++)
	{
		Transform::Status anime;
		
		blocks_[i]->actTim_.Update();
		if (0.5f <= blocks_[i]->actTim_.Ratio())
		{
			PropagateBlock(i + 1, blocks_[i]->isActColorPow_);
		}

		anime.pos_.x = posXEas_[stepIndex].Out(blocks_[i]->actTim_.Ratio());
		blocks_[i]->obj_->Update(anime);

		blocks_[i]->colorPow_.Update(blocks_[i]->isActColorPow_);
		blocks_[i]->cbColor_->data_.baseColor = colorEas_.InOut(blocks_[i]->colorPow_.Ratio());
	}
}

void WindBlocks::Update()
{
	UpdateChange();
	UpdateBlock();
}

void WindBlocks::Draw()
{
	for (size_t i = 0; i < blocks_.size(); i++)
	{
		blocks_[i]->obj_->Draw("Sprite2DDefault", 0);
	}
}
