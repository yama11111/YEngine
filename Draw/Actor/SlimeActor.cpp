#include "SlimeActor.h"
#include <cassert>

using YGame::SlimeActor;

void SlimeActor::Initialize()
{
	isAct_ = false;
	action_ = Action::None;

	ease_.Initialize({}, {}, 0.0f);
	jiggles_.clear();
	currentIdx_ = 0;

	timer_.Initialize(0);

	value_ = {};
}

void SlimeActor::Activate(const std::vector<JiggleState>& jiggles)
{
	assert(jiggles.size() > 1);

	Initialize();

	isAct_ = true;
	action_ = Action::Elasticity;

	jiggles_ = jiggles;
	ease_.Initialize(jiggles_[0].value_, jiggles_[1].value_, jiggles_[1].exponent_);
	currentIdx_ = 1;

	timer_.Initialize(jiggles_[1].frame_);
	timer_.SetActive(true);
}

void SlimeActor::Update()
{
	if (isAct_ == false) { return; }

	timer_.Update();
	UpdateValue();
	
	if (timer_.IsEnd())
	{
		timer_.Reset(true);
		ChangeAction();
	}
}

void SlimeActor::ChangeAction()
{
	// êLèkà»äOÇ»ÇÁ
	if (action_ != Action::Elasticity)
	{
		Initialize();
		return;
	}

	size_t elderIdx = currentIdx_;
	currentIdx_++;

	// èIí[Ç»ÇÁ
	if (currentIdx_ == (jiggles_.size() - 1))
	{
		action_ = Action::Normal;
	}

	ease_.Initialize(jiggles_[elderIdx].value_, jiggles_[currentIdx_].value_, jiggles_[currentIdx_].exponent_);
	timer_.Initialize(jiggles_[currentIdx_].frame_);
	timer_.SetActive(true);
}

void SlimeActor::UpdateValue()
{
	value_ = ease_.In(timer_.Ratio());
}

YMath::Vector3 SlimeActor::JiggleValue()
{
	return value_;
}
