#include "SceneChanger.h"
#include "SceneChangeFrame.h"

void SceneChanger::Initialize(const InitStatus& state)
{
	curtenS_ = state.curtenS_;
	plainT_ = state.plainTex_;
	Reset();
}

void SceneChanger::Reset()
{
	curten_.Initialize({});
	curten_.color_ = { 0.0f,0.0f,0.0f, 0.0f };
	step_ = Step::BlackOut;
	isAct_ = false;
	isChangeMoment_ = false;
	count = 0;

	blendE_.Initialize(0.0f, 1.0f, 2.0f);
	blendP_.Initialize(0);
}

void SceneChanger::Activate()
{
	Reset();
	isAct_ = true;
	blendP_.Initialize(Light::ChangeFrame);
}

void SceneChanger::ChangeUpdate()
{
	if (isAct_ == false) { return; }

	isChangeMoment_ = false;
	bool act = false;

	if (step_ == Step::BlackOut)
	{
		act = true;
		if (blendP_.IsMax()) 
		{
			step_ = Step::Load; 
			isChangeMoment_ = true;
		}
	}
	else if (step_ == Step::Load)
	{
		act = true;
		if (++count >= Light::LoadFrame) { step_ = Step::BrightTurn; }
	}
	else if (step_ == Step::BrightTurn)
	{
		act = false;
		if (blendP_.IsZero()) { Reset(); }
	}

	blendP_.Update(act);
}

void SceneChanger::BlendUpdate()
{
	if (isAct_ == false) { return; }

	float a = 0.0f;
	if (step_ == Step::BlackOut || step_ == Step::Load)
	{
		a = blendE_.In(blendP_.Ratio());
	}
	else if (step_ == Step::BrightTurn)
	{
		a = blendE_.Out(blendP_.Ratio());
	}
	curten_.color_ = { 0.0f,0.0f,0.0f, a };
}

void SceneChanger::Update()
{
	ChangeUpdate();
	BlendUpdate();

	curten_.Update();
}

void SceneChanger::Draw()
{
	curtenS_->Draw(curten_, plainT_);
}
