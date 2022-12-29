#include "HitActor.h"
#include "CharaConfig.h"

using YActor::HitActor;
using YMath::Vec3;
using YMath::Vec4;
using namespace CharaConfig::HitAct;

const float ShakeRange = 100.0f;

void HitActor::InitializeHitAction()
{
	isAct_ = false;
	shake_.Initialize();
	color_ = {};
	isFliclering_ = false;
}

void HitActor::ActivateHitAction(const float shakeValue, const unsigned int frame)
{
	InitializeHitAction();

	isAct_ = true;

	int s = static_cast<int>(shakeValue * ShakeRange);
	int d = s / frame;

	shake_.Activate(s, d);
}

void HitActor::UpdateHitAction()
{
	if (isAct_ == false) { return; }

	shake_.Update();
	isFliclering_ = !isFliclering_;

	if (shake_.IsAct() == false) 
	{
		InitializeHitAction();
	}
}

Vec3 HitActor::HitActionShakeValue()
{
	Vec3 result = shake_.Value();

	result /= ShakeRange;

	return result;
}

Vec4 HitActor::HitActionColor()
{
	Vec4 result = Color;

	result.a_ = isFliclering_ ? Color.a_ : AlphaValue;

	return result;
}
