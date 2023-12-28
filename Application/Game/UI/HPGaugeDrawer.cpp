#include "HPGaugeDrawer.h"
#include "MathUtil.h"
#include <cassert>

using YGame::HPGaugeDrawer;
using YGame::Sprite2D;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Sprite2D* pSpr = nullptr;

	const Vector3 kGaugeSize = Vector3(128.0f, 24.0f, 0.0f);
	const Vector3 kFrameSize = kGaugeSize + Vector3(4.0f, 4.0f, 0.0f);

	const Vector4 kGaugeColor =			YMath::GetColor( 11, 238, 168, 255);
	const Vector4 kGaugePlusColor =		YMath::GetColor(249,  86,  75, 255);
	const Vector4 kGaugeMinusColor =	YMath::GetColor(226, 255, 108, 255);
}

HPGaugeDrawer* HPGaugeDrawer::Create(
	YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority)
{
	HPGaugeDrawer* newObj = new HPGaugeDrawer();

	newObj->Initialize(pParent);

	newObj->shaderTag_ = shaderTag;
	newObj->drawPriority_ = drawPriority;

	return newObj;
}

void HPGaugeDrawer::LoadResource()
{
	pSpr = Sprite2D::Create({ {"Texture0", Texture::Load("white1x1.png")} });
}

void HPGaugeDrawer::Initialize(YMath::Matrix4* pParent)
{
	assert(pParent);
	pParent_ = pParent;

	// ゲージ
	{
		Transform::Status status = Transform::Status::Default();
		status.scale_ = kGaugeSize;
		DrawObjectForSprite2D* newGauge = DrawObjectForSprite2D::Create(status, pSpr);
		newGauge->transform_.parent_ = pParent_;

		gaugeColor_.reset(ConstBufferObject<CBColor>::Create());
		gaugeColor_->data_.baseColor = kGaugeColor;
		newGauge->InsertConstBuffer(gaugeColor_.get());

		gauge_.reset(UIGauge::Create(newGauge));
	}

	// -ゲージ
	{
		Transform::Status status = Transform::Status::Default();
		status.scale_ = kGaugeSize;
		DrawObjectForSprite2D* newGauge = DrawObjectForSprite2D::Create(status, pSpr);
		newGauge->transform_.parent_ = pParent_;

		gaugeMinusColor_.reset(ConstBufferObject<CBColor>::Create());
		gaugeMinusColor_->data_.baseColor = kGaugePlusColor;
		newGauge->InsertConstBuffer(gaugeMinusColor_.get());

		gaugeMinus_.reset(UIGauge::Create(newGauge));
	}

	// +ゲージ
	{
		Transform::Status status = Transform::Status::Default();
		status.scale_ = kGaugeSize;
		DrawObjectForSprite2D* newGauge = DrawObjectForSprite2D::Create(status, pSpr);
		newGauge->transform_.parent_ = pParent_;

		gaugePlusColor_.reset(ConstBufferObject<CBColor>::Create());
		gaugePlusColor_->data_.baseColor = kGaugeMinusColor;
		newGauge->InsertConstBuffer(gaugePlusColor_.get());

		gaugePlus_.reset(UIGauge::Create(newGauge));
	}

	// 背景
	{
		Transform::Status status = Transform::Status::Default();
		status.scale_ = kGaugeSize;
		DrawObjectForSprite2D* newBack = DrawObjectForSprite2D::Create(status, pSpr);
		newBack->transform_.parent_ = pParent_;

		backColor_.reset(ConstBufferObject<CBColor>::Create());
		backColor_->data_.baseColor = YMath::Vector4(0.0f, 0.0f, 0.0f, 0.75f);
		newBack->InsertConstBuffer(backColor_.get());

		back_.reset(newBack);
	}

	// 枠
	{
		Transform::Status status = Transform::Status::Default();
		status.scale_ = kFrameSize;
		DrawObjectForSprite2D* newFrame = DrawObjectForSprite2D::Create(status, pSpr);
		newFrame->transform_.parent_ = pParent_;

		frameColor_.reset(ConstBufferObject<CBColor>::Create());
		frameColor_->data_.baseColor = YMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		newFrame->InsertConstBuffer(frameColor_.get());

		frame_.reset(newFrame);
	}
}

void HPGaugeDrawer::Update()
{
	gauge_->Update();
	gaugeMinus_->Update();
	gaugePlus_->Update();
	back_->Update();
	frame_->Update();
}

void HPGaugeDrawer::Draw()
{
	frame_->Draw(shaderTag_, drawPriority_);
	back_->Draw(shaderTag_, drawPriority_);
	gaugePlus_->Draw(shaderTag_, drawPriority_);
	gaugeMinus_->Draw(shaderTag_, drawPriority_);
	gauge_->Draw(shaderTag_, drawPriority_);
}

void HPGaugeDrawer::ChangeHPAnimation(const uint32_t value, const uint32_t maxValue)
{
	if (value_ != value) { ChangeValueAnimation(value, (value < value_)); }
	if (maxValue_ != maxValue) { ChangeMaxValueAnimation(maxValue, (maxValue < maxValue_)); }
}

void HPGaugeDrawer::ChangeValueAnimation(const uint32_t value, const bool isDecrease)
{
	value_ = value;

	float ratio = ValueRatio();

	if (isDecrease)
	{
		gauge_->		Change(ratio, 40, 2.0f);
		gaugeMinus_->	Change(ratio, 80, 2.0f);
		gaugePlus_->	Change(ratio, 40, 2.0f);
	}
	else
	{
		gauge_->		Change(ratio, 80, 2.0f);
		gaugeMinus_->	Change(ratio, 80, 2.0f);
		gaugePlus_->	Change(ratio, 40, 2.0f);
	}
}

void HPGaugeDrawer::ChangeMaxValueAnimation(const uint32_t maxValue, const bool isDecrease)
{
	maxValue_ = maxValue;

	float ratio = ValueRatio();

	if (isDecrease)
	{
		gauge_->		Change(ratio, 40, 2.0f);
		gaugeMinus_->	Change(ratio, 80, 2.0f);
		gaugePlus_->	Change(ratio, 40, 2.0f);
	}
	else
	{
		gauge_->		Change(ratio, 80, 2.0f);
		gaugeMinus_->	Change(ratio, 80, 2.0f);
		gaugePlus_->	Change(ratio, 40, 2.0f);
	}
}

const float HPGaugeDrawer::ValueRatio() const
{
	if (maxValue_ <= 0) { return 0; }
	return static_cast<float>(value_) / static_cast<float>(maxValue_);
}
