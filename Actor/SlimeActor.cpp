#include "SlimeActor.h"

using YActor::SlimeActor;

void SlimeActor::InitializeSlimeAct()
{
	isAct_ = false;
	action_ = Action::None;

	ease_.Initialize({}, {}, 2.0f);
	ends_.clear();
	currentIdx_ = 0;

	timer_.Initialize(0);

	value_ = {};
}

void SlimeActor::ActivateSlimeAct(const std::vector<YMath::Vec3> ends, const unsigned int frame)
{
	InitializeSlimeAct();

	isAct_ = true;
	action_ = Action::Elasticity;

	ends_ = ends;
	ease_.Initialize({}, ends_[0], 2.0f);

	timer_.Initialize(frame);
	timer_.SetActive(true);
}

void SlimeActor::UpdateSlimeAct()
{
	if (isAct_ == false) { return; }

	timer_.Update();
	if (timer_.IsEnd())
	{
		timer_.Reset(true);
		ChangeAction();
	}

	UpdateValue();
}

void SlimeActor::ChangeAction()
{
	bool isElasticity = action_ == Action::Elasticity;

	// êLèkà»äOÇ»ÇÁ
	if (isElasticity == false) 
	{
		InitializeSlimeAct();
		return; 
	}

	size_t elderIdx = currentIdx_;
	currentIdx_++;

	// èIí[Ç∂Ç·Ç»Ç¢Ç»ÇÁ
	if (currentIdx_ < ends_.size())
	{
		ease_.Initialize(ends_[elderIdx], ends_[currentIdx_], 2.0f);
		action_ = Action::Elasticity;
	}
	else
	{
		ease_.Initialize(ends_[elderIdx], {}, 2.0f);
		action_ = Action::Normal;
	}
}

void SlimeActor::UpdateValue()
{
	if (timer_.Current() == 0) { return; }

	value_ = ease_.In(timer_.Ratio());
}

YMath::Vec3 SlimeActor::SlimeActValue()
{
	return value_;
}
