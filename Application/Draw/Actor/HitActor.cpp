#include "HitActor.h"
#include <cassert>

using YGame::HitActor;
using YMath::Vector3;
using YMath::Vector4;

const YMath::Vector4 kDefColor = YMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const YMath::Vector4 kHitColor = YMath::Vector4(0.6f, 0.0f, 0.0f, 1.0f);

void HitActor::Initialize()
{
	isAct_ = false;

	shake_.Initialize();

	colorValue_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

void HitActor::Update()
{
	if (isAct_ == false) { return; }

	shake_.Update();

	colorValue_ = kHitColor;

	if (shake_.IsAct() == false)
	{
		isAct_ = false;

		colorValue_ = kDefColor;
	}
}

void HitActor::Hit(const float swing, const float dekey, const float place)
{
	isAct_ = true;

	shake_.Activate(swing, dekey, place);
}

