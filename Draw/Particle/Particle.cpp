#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::ObjectModel;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;

YGame::Model* YGame::FireSpark::pModel_ = nullptr;

void YGame::FireSpark::StaticInitialize(YGame::Model* pModel)
{
	assert(pModel);
	pModel_ = pModel;
}

void YGame::FireSpark::Emit(
	const uint32_t aliveTime,
	const uint32_t swayingTime,
	const YMath::Vector3& speed,
	const YMath::Vector3& pos, const float scale,
	const YMath::Vector4& color)
{
	isAlive_ = true;

	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);

	isSwitching_ = false;
	swayingPow_.Initialize(swayingTime);
	spd_ = speed;

	obj_.reset(ObjectModel::Create({ pos, {}, {scale, scale, scale} }));
	scaleEas_.Initialize(scale, 0.0f, 2.0f);

	color_.reset(Color::Create(color));
	alphaEas_.Initialize(color.a_, 0.0f, 3.0f);
}

void YGame::FireSpark::Update()
{
	if (isAlive_ == false) { return; }

	aliveTim_.Update();
	if (aliveTim_.IsEnd()) { isAlive_ = false; }

	swayingPow_.Update(isSwitching_);
	if (swayingPow_.IsMax()) { isSwitching_ = false; }
	if (swayingPow_.IsZero()) { isSwitching_ = true; }

	obj_->pos_.x_ += spd_.x_ * YMath::Lerp(-1.0f, +1.0f, swayingPow_.Ratio());
	obj_->pos_.z_ += spd_.z_ * YMath::Lerp(-1.0f, +1.0f, swayingPow_.Ratio());
	obj_->pos_.y_ += spd_.y_;

	float sca = scaleEas_.In(aliveTim_.Ratio());
	obj_->scale_ = { sca,sca,sca };
	obj_->UpdateMatrix();

	Vector4 c = color_->GetRGBA();
	c.a_ = alphaEas_.In(aliveTim_.Ratio());
	color_->SetRGBA(c);
}

void YGame::FireSpark::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* pLightGroup)
{
	assert(pModel_);

	pModel_->Draw(obj_.get(), vp, pLightGroup, color_.get());
}