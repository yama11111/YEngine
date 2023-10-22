#include "UILetterBox.h"
#include <cassert>

using YGame::UILetterBox;

YGame::Sprite2D* UILetterBox::spSpr_ = nullptr;

namespace
{
	const size_t kTopIndex = 0; // 上
	const size_t kBottomIndex = 1; // 下 
}

void UILetterBox::Initialize(const YMath::Vector2& winSize, const float topHeight, const float bottomHeight)
{
	if (cbColor_ == nullptr)
	{
		cbColor_.reset(ConstBufferObject<CBColor>::Create());
	}

	// 黒色
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,1.0f };

	for (size_t i = 0; i < objs_.size(); i++)
	{
		if (objs_[i] == nullptr)
		{
			objs_[i].reset(DrawObjectForSprite2D::Create({}, spSpr_));
			objs_[i]->InsertConstBuffer(cbColor_.get());
		}

		heightEas_[i].Initialize({}, {}, 0.0f);
	}

	// ウィンドウの横幅と指定された高さに
	objs_[kTopIndex]	->transform_.scale_ = { winSize.x_, topHeight, 0.0f };
	objs_[kBottomIndex]	->transform_.scale_ = { winSize.x_, bottomHeight, 0.0f };

	// ウィンドウの上と下に隣接するように
	objs_[kTopIndex]	->transform_.pos_ = { winSize.x_ / 2.0f, +topHeight / 2.0f, 0.0f };
	objs_[kBottomIndex]	->transform_.pos_ = { winSize.x_ / 2.0f, winSize.y_ - bottomHeight / 2.0f, 0.0f };

	heightEasTimer_.Initialize(0);

	state = State::None;

	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i]->Update();
	}
}

void UILetterBox::UpdatePos()
{
	if (state == State::None) { return; }

	for (size_t i = 0; i < objs_.size(); i++)
	{
		Transform::Status status = {};

		// 上下で符号変える
		float sign = 0.0f;

		if (i == kTopIndex)
		{
			sign = -1.0f;
		}
		else if (i == kBottomIndex)
		{
			sign = +1.0f;
		}

		if (state == State::Drop)
		{
			status.pos_ = heightEas_[i].In(heightEasTimer_.Ratio()) * sign;
		}
		else if (state == State::Close)
		{
			status.pos_ = heightEas_[i].Out(heightEasTimer_.Ratio()) * sign;
		}

		objs_[i]->Update(status);
	}
}

void UILetterBox::Update()
{
	heightEasTimer_.Update();

	UpdatePos();

	// 終了後初期化
	if (heightEasTimer_.IsEnd())
	{
		heightEasTimer_.Reset(false);

		state = State::None;
	}
}

void UILetterBox::Drop(const uint32_t frame, const float exponent)
{
	if (state == State::Drop) { return; }

	state = State::Drop;

	heightEasTimer_.Initialize(frame, true);

	for (size_t i = 0; i < objs_.size(); i++)
	{
		heightEas_[i].Initialize(objs_[i]->transform_.scale_, {}, exponent);
	}
}

void UILetterBox::Close(const uint32_t frame, const float exponent)
{
	if (state == State::Close) { return; }
	
	state = State::Close;
	
	heightEasTimer_.Initialize(frame, true);

	for (size_t i = 0; i < objs_.size(); i++)
	{
		heightEas_[i].Initialize({}, objs_[i]->transform_.scale_, exponent);
	}
}

void UILetterBox::Draw(const std::string& shaderTag, const uint16_t priority)
{
	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i]->Draw(shaderTag, priority);
	}
}

void UILetterBox::SetColor(const YMath::Vector4& color)
{
	cbColor_->data_.baseColor = color;
}

void UILetterBox::LoadResource()
{
	spSpr_ = Sprite2D::Create({ {"Texture0", Texture::Load("white1x1.png") } });
}
