#include "SlimeActor.h"
#include <cassert>

using YGame::SlimeActor;

void SlimeActor::Initialize()
{
	isAct_ = false;
	action_ = Action::None;

	ease_.Initialize({}, {}, 0.0f);
	wobbleScaleValues_.clear();
	currentIdx_ = 0;

	timer_.Initialize(0);

	value_ = {};
}

void SlimeActor::Wobble(const std::vector<YMath::Vector3>& wobbleScaleValues, const uint32_t frame, const float exponent)
{
	assert(wobbleScaleValues.size() >= 1);

	Initialize();

	isAct_ = true;
	action_ = Action::Elasticity;

	wobbleScaleValues_ = wobbleScaleValues;
	exponent_ = exponent;

	ease_.Initialize(wobbleScaleValues_[0], wobbleScaleValues_[1], exponent_);
	currentIdx_ = 1;

	timer_.Initialize(frame);
	timer_.SetActive(true);
}

void SlimeActor::Update()
{
	if (isAct_ == false) { return; }

	timer_.Update();
	UpdateValue();
	
	if (timer_.IsEnd())
	{
		ChangeAction();
		timer_.Reset(true);
	}
}

void SlimeActor::ChangeAction()
{
	// LkˆÈŠO‚È‚ç
	if (action_ != Action::Elasticity)
	{
		Initialize();
		return;
	}

	size_t elderIdx = currentIdx_;
	currentIdx_++;

	// I’[‚È‚ç
	if (currentIdx_ >= (wobbleScaleValues_.size() - 1))
	{
		action_ = Action::Normal;
	}

	ease_.Initialize(wobbleScaleValues_[elderIdx], wobbleScaleValues_[currentIdx_], exponent_);
}

void SlimeActor::UpdateValue()
{
	value_ = ease_.In(timer_.Ratio());
}