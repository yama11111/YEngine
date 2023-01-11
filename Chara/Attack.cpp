#include "Attack.h"

void Attack::Initialize(const InitStatus& state)
{
	pos_ = state.pos_;
	SetRadius(state.rad_);
	SetAttribute(state.attribute_);
	SetMask(state.mask_);

	actTimer_.Initialize(state.actFrame_);
	actTimer_.SetActive(true);

	isAct_ = true;
}

void Attack::Update()
{
	if (isAct_ == false) { return; }

	actTimer_.Update();
	if (actTimer_.IsEnd())
	{
		isAct_ = false;
	}
}
