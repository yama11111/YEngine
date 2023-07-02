#include "HitActor.h"
#include <cassert>

using YGame::HitActor;
using YMath::Vector3;
using YMath::Vector4;

void HitActor::Initialize(const Vector4& hitColor)
{
	shake_.Initialize();

	hitColor_ = hitColor;
}

void HitActor::Update()
{
	if (isAct_ == false) { return; }

	shake_.Update();
}

void HitActor::Hit(const float swing, const float dekey, const float place)
{
	shake_.Activate(swing, dekey, place);
}

