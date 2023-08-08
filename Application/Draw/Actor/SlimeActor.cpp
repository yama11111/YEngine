#include "SlimeActor.h"
#include <cassert>

using YGame::SlimeActor;
using YMath::Vector3;

void SlimeActor::Initialize(
	const uint32_t frame, 
	const std::vector<YMath::Vector3>& wobbleScaleValues, 
	const float exponent)
{
	assert(wobbleScaleValues.empty() == false);
	
	isAct_ = false;

	ease_.Initialize(wobbleScaleValues, exponent);

	timer_.Initialize(frame);
	power_.Initialize(frame);
}

void SlimeActor::Wobble()
{
	isAct_ = true;
	
	timer_.Reset();
	timer_.SetActive(true);
}

void SlimeActor::Update(const bool isSquash)
{
	power_.Update(isSquash);

	if (isAct_ == false) { return; }

	timer_.Update();
	
	if (timer_.IsEnd())
	{
		isAct_ = false;
	}
}

Vector3 SlimeActor::WobbleScaleValue(const EaseType easeType) const
{
	float ratio = 0.0f;

	if (isAct_) { ratio = timer_.Ratio(); }
	else		{ ratio = power_.Ratio(); }

	if (easeType == EaseType::eIn)
	{
		return ease_.In(ratio);
	}
	if (easeType == EaseType::eOut)
	{
		return ease_.Out(ratio);
	}

	return Vector3();
}