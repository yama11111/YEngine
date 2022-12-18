#include "Blackout.h"
#include "SceneChangeFrame.h"

using Transition::Blackout;

Game::Sprite* Blackout::curtenS_ = nullptr;

void Blackout::StaticInitialize(const StaticInitStatus& state)
{
	curtenS_ = state.curtenSprite_;
}

void Blackout::Initialize()
{
	curten_.Initialize({});
	curten_.color_ = { 0.0f,0.0f,0.0f, 0.0f };
	boStep_ = Step::Dark;
	count_ = 0;
	blendE_.Initialize(0.0f, 1.0f, 2.0f);
	blendP_.Initialize(0);

	isChangeMoment_ = false;
}

void Blackout::Activate()
{
	Initialize();
	isAct_ = true;
	blendP_.Initialize(BlackoutFlame::Change);
}

void Blackout::ChangeUpdate()
{
	if (isAct_ == false) { return; }

	isChangeMoment_ = false;
	bool act = false;

	if (boStep_ == Step::Dark)
	{
		act = true;
		if (blendP_.IsMax()) 
		{
			boStep_ = Step::Load; 
			isChangeMoment_ = true;
		}
	}
	else if (boStep_ == Step::Load)
	{
		act = true;
		if (++count_ >= BlackoutFlame::Load) 
		{
			boStep_ = Step::Bright; 
		}
	}
	else if (boStep_ == Step::Bright)
	{
		act = false;
		if (blendP_.IsZero()) 
		{
			Initialize(); 
		}
	}

	blendP_.Update(act);
}

void Blackout::BlendUpdate()
{
	if (isAct_ == false) { return; }

	float a = 0.0f;
	if (boStep_ == Step::Dark || boStep_ == Step::Load)
	{
		a = blendE_.In(blendP_.Ratio());
	}
	else if (boStep_ == Step::Bright)
	{
		a = blendE_.Out(blendP_.Ratio());
	}
	curten_.color_ = { 0.0f,0.0f,0.0f, a };
}

void Blackout::Update()
{
	ChangeUpdate();
	BlendUpdate();

	curten_.Update();
}

void Blackout::Draw()
{
	curtenS_->Draw(curten_);
}
