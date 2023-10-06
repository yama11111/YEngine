#include "DamageEmitter.h"
#include "MathVector.h"
#include "ColorConfig.h"

using YGame::DamageEmitter;

std::array<DamageEmitter::Damage, 10> DamageEmitter::damage_;
YGame::ViewProjection* DamageEmitter::spVP_;

void DamageEmitter::Initialize(ViewProjection* pVP)
{
	for (size_t i = 0; i < damage_.size(); i++)
	{
		damage_[i].Initialize(pVP);
	}

	spVP_ = pVP;
}

void DamageEmitter::Emit(const YMath::Vector3& pos, const uint32_t damageVal)
{
	for (size_t i = 0; i < damage_.size(); i++)
	{
		if(damage_[i].IsAct() == false)
		{
			damage_[i].Pop(pos, damageVal);
			break;
		}
	}
}

void DamageEmitter::Update()
{
	for (size_t i = 0; i < damage_.size(); i++)
	{
		damage_[i].Update();
	}
}

void DamageEmitter::Draw()
{
	for (size_t i = 0; i < damage_.size(); i++)
	{
		damage_[i].Draw();
	}
}

namespace
{
	const size_t kMaxDigitNum = 4;
	const float kInterval = 0.75f;
	const float kScaleValue = 3.0f;
}

void DamageEmitter::Damage::Initialize(ViewProjection* pVP)
{
	trfm_.Initialize();
	trfm_.scale_ = { kScaleValue, kScaleValue, kScaleValue };

	if (uiNum_ == nullptr)
	{
		uiNum_.reset(UINumber::Create3D(0, kMaxDigitNum, kInterval, false, &trfm_.m_, false, false, pVP));
	}
	else
	{
		uiNum_->Initialize3D(0, kMaxDigitNum, kInterval, false, &trfm_.m_, false, false, pVP);
	}

	if (cbColor_ == nullptr)
	{
		cbColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	uiNum_->InsertConstBuffer(cbColor_.get());

	popTim_.Initialize(30);
	upEas_.Initialize(0.0f, 5.0f, 3.0f);
	popScaEas_.Initialize(-kScaleValue, 0.0f, 3.0f);

	remainTim_.Initialize(30);

	vanishTim_.Initialize(10);
	vanishAlphaEas_.Initialize(1.0f, 0.0f, 2.0f);

	Reset();
}

void DamageEmitter::Damage::Reset()
{
	trfm_.Initialize();
	trfm_.scale_ = { kScaleValue, kScaleValue, kScaleValue };

	isXBillboard_ = true;
	isYBillboard_ = true;

	uiNum_->SetNumber(0);
	cbColor_->data_.baseColor = YGame::ColorConfig::skYellow;
	cbColor_->data_.baseColor.a_ = 0.0f;

	isAct_ = false;

	popTim_.Reset();
	remainTim_.Reset();
	vanishTim_.Reset();
}

void DamageEmitter::Damage::Update()
{
	if (isAct_ == false) { return; }

	popTim_.Update();
	remainTim_.Update();
	vanishTim_.Update();

	//          c  
	if (popTim_.IsEnd())
	{
		remainTim_.SetActive(true);
	}
	//  c          
	if (remainTim_.IsEnd())
	{
		vanishTim_.SetActive(true);
	}
	//          I  
	if (vanishTim_.IsEnd())
	{
		Reset();
	}

	Transform::Status animeStatus;

	animeStatus.pos_.y_ += upEas_.Out(popTim_.Ratio());

	float sca = popScaEas_.Out(popTim_.Ratio());
	animeStatus.scale_ += { sca, sca, sca };

	YMath::Matrix4 billMat = YMath::MatBillboard(isXBillboard_, isYBillboard_, spVP_->eye_, spVP_->target_, spVP_->up_);
	trfm_.UpdateMatrix(animeStatus, billMat);

	uiNum_->Update();

	cbColor_->data_.baseColor.a_ = vanishAlphaEas_.In(vanishTim_.Ratio());
}

void DamageEmitter::Damage::Draw()
{
	if (isAct_ == false) { return; }

	uiNum_->Draw("Sprite3DDefault", 1);
}

void DamageEmitter::Damage::Pop(const YMath::Vector3& pos, const uint32_t damageValue)
{
	Reset();

	trfm_.pos_ = pos;

	//  A j   [ V     J n
	isAct_ = true;
	uiNum_->SetNumber(damageValue);
	popTim_.SetActive(true);
}
