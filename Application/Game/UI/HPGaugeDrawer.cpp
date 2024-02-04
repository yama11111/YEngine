#include "HPGaugeDrawer.h"
#include "DrawObjectForSprite3D.h"
#include "MathUtil.h"

using YGame::HPGaugeDrawer;
using YGame::Sprite3D;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Sprite3D* pSpr = nullptr;

	const Vector3 kGaugePos = {+60.0f, +32.0f, 0.0f};
	const Vector3 kGaugeScale = { 360.0f,64.0f,0.0f };

	const Vector4 kGaugeColor =			YMath::GetColor( 62, 230,  90, 255);
	const Vector4 kGaugePlusColor =		YMath::GetColor(249,  86,  75, 255);
	const Vector4 kGaugeMinusColor =	YMath::GetColor(226, 255, 108, 255);

	const  uint32_t kChangeFastFrame = 40;
	const  uint32_t kChangeLateFrame = 80;
	const  float kChangeExponent = 2.0f;

	const std::string kShaderTag = "Sprite3DUI";
}

void HPGaugeDrawer::LoadResource()
{
	pSpr = Sprite3D::Create({ {"Texture0", Texture::Load("UI/play/hp_gauge.png")} });
}

HPGaugeDrawer* HPGaugeDrawer::Create(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	HPGaugeDrawer* newObj = new HPGaugeDrawer();

	newObj->Initialize(pParent, pVP);

	return newObj;
}

void HPGaugeDrawer::Initialize(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	transform_.Initialize();
	transform_.parent_ = pParent;

	// ゲージ
	if (gauge_ == nullptr)
	{
		Transform::Status status;
		status.pos_ = kGaugePos;
		status.scale_ = kGaugeScale;

		DrawObjectForSprite3D* newGauge = 
			DrawObjectForSprite3D::Create(
				status, false, false, pVP, pSpr);
		newGauge->transform_.parent_ = &transform_.m;

		gaugeColor_.reset(ConstBufferObject<CBColor>::Create());
		gaugeColor_->data_.baseColor = kGaugeColor;
		newGauge->InsertConstBuffer(gaugeColor_.get());

		gauge_.reset(UIGauge::Create(newGauge));
	}

	// -ゲージ
	if (gaugeMinus_ == nullptr)
	{
		Transform::Status status;
		status.pos_ = kGaugePos;
		status.scale_ = kGaugeScale;

		DrawObjectForSprite3D* newGauge = 
			DrawObjectForSprite3D::Create(
				status, false, false, pVP, pSpr);
		newGauge->transform_.parent_ = &transform_.m;

		gaugeMinusColor_.reset(ConstBufferObject<CBColor>::Create());
		gaugeMinusColor_->data_.baseColor = kGaugePlusColor;
		newGauge->InsertConstBuffer(gaugeMinusColor_.get());

		gaugeMinus_.reset(UIGauge::Create(newGauge));
	}

	// +ゲージ
	if (gaugePlus_ == nullptr)
	{
		Transform::Status status;
		status.pos_ = kGaugePos;
		status.scale_ = kGaugeScale;

		DrawObjectForSprite3D* newGauge = 
			DrawObjectForSprite3D::Create(
				status, false, false, pVP, pSpr);
		newGauge->transform_.parent_ = &transform_.m;

		gaugePlusColor_.reset(ConstBufferObject<CBColor>::Create());
		gaugePlusColor_->data_.baseColor = kGaugeMinusColor;
		newGauge->InsertConstBuffer(gaugePlusColor_.get());

		gaugePlus_.reset(UIGauge::Create(newGauge));
	}
}

void HPGaugeDrawer::Update()
{
	transform_.UpdateMatrix();

	gauge_->Update();
	gaugeMinus_->Update();
	gaugePlus_->Update();
}

void HPGaugeDrawer::Draw()
{
	gaugePlus_->Draw(kShaderTag, 0);
	gaugeMinus_->Draw(kShaderTag, 0);
	gauge_->Draw(kShaderTag, 0);
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
		gauge_->		Change(ratio, kChangeFastFrame, kChangeExponent);
		gaugeMinus_->	Change(ratio, kChangeLateFrame, kChangeExponent);
		gaugePlus_->	Change(ratio, kChangeFastFrame, kChangeExponent);
	}
	else
	{
		gauge_->		Change(ratio, kChangeLateFrame, kChangeExponent);
		gaugeMinus_->	Change(ratio, kChangeLateFrame, kChangeExponent);
		gaugePlus_->	Change(ratio, kChangeFastFrame, kChangeExponent);
	}
}

void HPGaugeDrawer::ChangeMaxValueAnimation(const uint32_t maxValue, const bool isDecrease)
{
	maxValue_ = maxValue;

	float ratio = ValueRatio();

	if (isDecrease)
	{
		gauge_->		Change(ratio, kChangeFastFrame, kChangeExponent);
		gaugeMinus_->	Change(ratio, kChangeLateFrame, kChangeExponent);
		gaugePlus_->	Change(ratio, kChangeFastFrame, kChangeExponent);
	}
	else
	{
		gauge_->		Change(ratio, kChangeLateFrame, kChangeExponent);
		gaugeMinus_->	Change(ratio, kChangeLateFrame, kChangeExponent);
		gaugePlus_->	Change(ratio, kChangeFastFrame, kChangeExponent);
	}
}

const float HPGaugeDrawer::ValueRatio() const
{
	if (maxValue_ <= 0) { return 0; }
	return static_cast<float>(value_) / static_cast<float>(maxValue_);
}
