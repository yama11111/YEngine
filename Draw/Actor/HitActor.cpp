#include "HitActor.h"
#include "CharaConfig.h"

using YGame::HitActor;
using YMath::Vector3;
using YMath::Vector4;
using namespace CharaConfig::HitAct;

const float ShakeRange = 100.0f;

void HitActor::Initialize()
{
	isAct_ = false;
	shake_.Initialize();
	color_ = {};
	isFliclering_ = false;
}

void HitActor::Activate(const float shakeValue, const unsigned int frame)
{
	Initialize();

	isAct_ = true;

	int s = static_cast<int>(shakeValue * ShakeRange);
	int d = s / frame;

	shake_.Activate(s, d);
}

void HitActor::Update()
{
	if (isAct_ == false) { return; }

	shake_.Update();
	isFliclering_ = !isFliclering_;

	if (shake_.IsAct() == false) 
	{
		Initialize();
	}
}

Vector3 HitActor::ShakeValue()
{
	Vector3 result = shake_.Value();

	result /= ShakeRange;

	return result;
}

Vector4 HitActor::ColorValue()
{
	Vector4 result = Color;

	result.a_ = isFliclering_ ? Color.a_ : AlphaValue;

	return result;
}
